#include "Tasks.h"

#include "Sensor.h"
#include "Storage.h"
#include "Display.h"
#include "Buttons.h"
#include "Modes.h"
#include "BluetoothComm.h"

// =====================================================
// Handles das Tasks
// =====================================================

static TaskHandle_t sensorTaskHandle    = NULL;
static TaskHandle_t buttonsTaskHandle   = NULL;
static TaskHandle_t modesTaskHandle     = NULL;
static TaskHandle_t displayTaskHandle   = NULL;
static TaskHandle_t bluetoothTaskHandle = NULL;

// =====================================================
// Flag interna para o Display
// =====================================================
//
// A TaskSensor armazena todos os dados, mas só libera atualização
// do LCD a cada LCD_DISPLAY_SAMPLE_DIVIDER amostras.
//

static volatile bool collectionDisplayUpdatePending = false;

// =====================================================
// Inicialização das Tasks
// =====================================================

void initTasks() {
  Serial.println("[Tasks] Criando tasks...");

  BaseType_t result;

  // -----------------------------------------------------
  // Core 1: aquisição do sensor
  // -----------------------------------------------------

  result = xTaskCreatePinnedToCore(
    taskSensor,
    "TaskSensor",
    4096,
    NULL,
    3,
    &sensorTaskHandle,
    1
  );

  if (result == pdPASS) {
    Serial.println("[Tasks] TaskSensor criada no Core 1.");
  } else {
    Serial.println("[Tasks] ERRO ao criar TaskSensor.");
  }

  // -----------------------------------------------------
  // Core 0: botões
  // -----------------------------------------------------

  result = xTaskCreatePinnedToCore(
    taskButtons,
    "TaskButtons",
    2048,
    NULL,
    2,
    &buttonsTaskHandle,
    0
  );

  if (result == pdPASS) {
    Serial.println("[Tasks] TaskButtons criada no Core 0.");
  } else {
    Serial.println("[Tasks] ERRO ao criar TaskButtons.");
  }

  // -----------------------------------------------------
  // Core 0: máquina de estados
  // -----------------------------------------------------

  result = xTaskCreatePinnedToCore(
    taskModes,
    "TaskModes",
    4096,
    NULL,
    2,
    &modesTaskHandle,
    0
  );

  if (result == pdPASS) {
    Serial.println("[Tasks] TaskModes criada no Core 0.");
  } else {
    Serial.println("[Tasks] ERRO ao criar TaskModes.");
  }

  // -----------------------------------------------------
  // Core 0: display LCD
  // -----------------------------------------------------

  result = xTaskCreatePinnedToCore(
    taskDisplay,
    "TaskDisplay",
    4096,
    NULL,
    1,
    &displayTaskHandle,
    0
  );

  if (result == pdPASS) {
    Serial.println("[Tasks] TaskDisplay criada no Core 0.");
  } else {
    Serial.println("[Tasks] ERRO ao criar TaskDisplay.");
  }

  // -----------------------------------------------------
  // Core 0: Bluetooth
  // -----------------------------------------------------

  result = xTaskCreatePinnedToCore(
    taskBluetooth,
    "TaskBluetooth",
    6144,
    NULL,
    1,
    &bluetoothTaskHandle,
    0
  );

  if (result == pdPASS) {
    Serial.println("[Tasks] TaskBluetooth criada no Core 0.");
  } else {
    Serial.println("[Tasks] ERRO ao criar TaskBluetooth.");
  }

  Serial.println("[Tasks] Inicializacao concluida.");
}

// =====================================================
// TaskSensor - Core 1
// =====================================================
//
// Essa task é responsável pela aquisição de dados.
// Ela não atualiza LCD.
// Ela não envia Bluetooth.
// Ela não imprime continuamente no Serial.
//
// Isso mantém a coleta mais regular.
//

void taskSensor(void *pvParameters) {
  TickType_t lastWakeTime = xTaskGetTickCount();
  const TickType_t samplePeriodTicks = pdMS_TO_TICKS(SAMPLE_INTERVAL_MS);

  while (true) {
    bool shouldCollect = false;
    uint32_t startCopy = 0;
    float initialCopy = 0.0f;

    // ---------------------------------------------------
    // Copia estado atual
    // ---------------------------------------------------

    if (stateMutex != NULL) {
      xSemaphoreTake(stateMutex, portMAX_DELAY);

      shouldCollect =
        (currentMode == MODE_COLLECTION) &&
        collectionActive &&
        !collectionPaused;

      startCopy = collectionStartMs;
      initialCopy = initialPositionCm;

      xSemaphoreGive(stateMutex);
    } else {
      shouldCollect =
        (currentMode == MODE_COLLECTION) &&
        collectionActive &&
        !collectionPaused;

      startCopy = collectionStartMs;
      initialCopy = initialPositionCm;
    }

    // ---------------------------------------------------
    // Aquisição
    // ---------------------------------------------------

    if (shouldCollect && !isDataBufferFull()) {
      SensorData data = readSensor();

      float relativePosition = data.distance_cm - initialCopy;
      uint32_t t = millis() - startCopy;

      // Atualiza últimas leituras globais.
      if (stateMutex != NULL) {
        xSemaphoreTake(stateMutex, portMAX_DELAY);

        latestVoltage = data.voltage;
        latestDistanceCm = data.distance_cm;
        latestRelativePositionCm = relativePosition;

        // Conta amostras apenas para o LCD.
        // Todos os dados continuam sendo armazenados no vetor.
        lcdSampleDividerCounter++;

        if (lcdSampleDividerCounter >= LCD_DISPLAY_SAMPLE_DIVIDER) {
          lcdSampleDividerCounter = 0;
          collectionDisplayUpdatePending = true;
        }

        xSemaphoreGive(stateMutex);
      } else {
        latestVoltage = data.voltage;
        latestDistanceCm = data.distance_cm;
        latestRelativePositionCm = relativePosition;

        lcdSampleDividerCounter++;

        if (lcdSampleDividerCounter >= LCD_DISPLAY_SAMPLE_DIVIDER) {
          lcdSampleDividerCounter = 0;
          collectionDisplayUpdatePending = true;
        }
      }

      // Armazena todos os pontos.
      addDataPoint(t, relativePosition);
    }

    vTaskDelayUntil(&lastWakeTime, samplePeriodTicks);
  }
}

// =====================================================
// TaskButtons - Core 0
// =====================================================

void taskButtons(void *pvParameters) {
  while (true) {
    updateButtons();

    vTaskDelay(pdMS_TO_TICKS(TASK_BUTTON_DELAY_MS));
  }
}

// =====================================================
// TaskModes - Core 0
// =====================================================

void taskModes(void *pvParameters) {
  while (true) {
    updateModeMachine();

    vTaskDelay(pdMS_TO_TICKS(TASK_MODE_DELAY_MS));
  }
}

// =====================================================
// TaskDisplay - Core 0
// =====================================================
//
// O display é atualizado com baixa frequência.
// No modo coleta, ele só atualiza quando a TaskSensor libera
// uma amostra para exibição.
//

void taskDisplay(void *pvParameters) {
  uint32_t lastDisplayMs = 0;

  while (true) {
    uint32_t now = millis();

    SystemMode modeCopy = MODE_DEFAULT;
    bool forceCopy = false;

    if (stateMutex != NULL) {
      xSemaphoreTake(stateMutex, portMAX_DELAY);

      modeCopy = currentMode;
      forceCopy = forceDisplayRefresh;

      xSemaphoreGive(stateMutex);
    } else {
      modeCopy = currentMode;
      forceCopy = forceDisplayRefresh;
    }

    bool timeToUpdate = (now - lastDisplayMs) >= LCD_INTERVAL_MS;
    bool shouldUpdate = false;

    if (forceCopy) {
      shouldUpdate = true;
    } else if (modeCopy == MODE_COLLECTION) {
      if (timeToUpdate && collectionDisplayUpdatePending) {
        shouldUpdate = true;
        collectionDisplayUpdatePending = false;
      }
    } else {
      if (timeToUpdate) {
        shouldUpdate = true;
      }
    }

    if (shouldUpdate) {
      lastDisplayMs = now;
      updateDisplay();
    }

    vTaskDelay(pdMS_TO_TICKS(TASK_LCD_DELAY_MS));
  }
}

// =====================================================
// TaskBluetooth - Core 0
// =====================================================

void taskBluetooth(void *pvParameters) {
  while (true) {
    updateBluetoothComm();

    vTaskDelay(pdMS_TO_TICKS(TASK_BLUETOOTH_DELAY_MS));
  }
}