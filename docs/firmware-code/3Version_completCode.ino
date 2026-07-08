#include "Globals.h"

#include "Sensor.h"
#include "Storage.h"
#include "Display.h"
#include "Buttons.h"
#include "Modes.h"
#include "BluetoothComm.h"
#include "Tasks.h"

void setup() {
  Serial.begin(115200);

  delay(500);

  Serial.println();
  Serial.println("================================");
  Serial.println(" Projeto Massa-Mola ESP32");
  Serial.println(" Versao Multicore FreeRTOS");
  Serial.println("================================");

  // =====================================================
  // Criação dos mutexes
  // =====================================================

  dataMutex  = xSemaphoreCreateMutex();
  stateMutex = xSemaphoreCreateMutex();
  lcdMutex   = xSemaphoreCreateMutex();

  if (dataMutex == NULL || stateMutex == NULL || lcdMutex == NULL) {
    Serial.println("[Sistema] ERRO ao criar mutexes.");

    while (true) {
      delay(1000);
    }
  }

  Serial.println("[Sistema] Mutexes criados.");

  // =====================================================
  // Inicialização dos módulos
  // =====================================================

  initDisplay();
  initSensor();
  initStorage();
  initButtons();
  initBluetoothComm();
  initModes();

  // =====================================================
  // Inicialização das Tasks
  // =====================================================

  initTasks();

  requestDisplayRefresh();

  Serial.println("[Sistema] Inicializacao completa.");
  Serial.println("[Sistema] Sistema pronto.");
  Serial.println();

  Serial.println("Controles:");
  Serial.println("DEFAULT:");
  Serial.println("  B1 -> Calibracao");
  Serial.println("  B2 -> Coleta");
  Serial.println("  B3 -> Transferencia");
  Serial.println();
  Serial.println("CALIBRACAO:");
  Serial.println("  B1 -> Recalibrar");
  Serial.println("  B2 -> Confirmar e voltar");
  Serial.println("  B3 -> Zerar e permanecer");
  Serial.println();
  Serial.println("COLETA:");
  Serial.println("  B1 -> Pause/Resume");
  Serial.println("  B2 -> Reset dados");
  Serial.println("  B3 -> Voltar default");
  Serial.println();
  Serial.println("TRANSFERENCIA:");
  Serial.println("  B1 -> Enviar dados");
  Serial.println("  B2 -> Voltar default");
  Serial.println("  B3 -> Configurar maximo de dados");
  Serial.println();
}

void loop() {
  // O loop principal fica livre.
  // Todo o sistema é controlado pelas tasks FreeRTOS.

  vTaskDelay(pdMS_TO_TICKS(1000));
}