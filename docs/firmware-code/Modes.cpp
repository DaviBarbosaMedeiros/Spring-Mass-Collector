#include "Modes.h"

#include "Buttons.h"
#include "Sensor.h"
#include "Storage.h"
#include "Display.h"
#include "BluetoothComm.h"

// =====================================================
// Funções auxiliares internas
// =====================================================

static void handleDefaultMode();
static void handleCalibrationMode();
static void handleCollectionMode();
static void handleTransferMode();

// =====================================================
// Inicialização
// =====================================================

void initModes() {
  enterDefaultMode();

  Serial.println("[Modes] Maquina de estados inicializada.");
}

// =====================================================
// Leitura segura do modo atual
// =====================================================

SystemMode getCurrentMode() {
  SystemMode modeCopy = MODE_DEFAULT;

  if (stateMutex != NULL) {
    xSemaphoreTake(stateMutex, portMAX_DELAY);
    modeCopy = currentMode;
    xSemaphoreGive(stateMutex);
  } else {
    modeCopy = currentMode;
  }

  return modeCopy;
}

// =====================================================
// Escrita segura do modo atual
// =====================================================

void setCurrentMode(SystemMode newMode) {
  if (stateMutex != NULL) {
    xSemaphoreTake(stateMutex, portMAX_DELAY);

    currentMode = newMode;
    forceDisplayRefresh = true;

    xSemaphoreGive(stateMutex);
  } else {
    currentMode = newMode;
    forceDisplayRefresh = true;
  }

  Serial.print("[Modes] Modo atual: ");
  Serial.println(modeToString(newMode));
}

// =====================================================
// Entrar no modo Default
// =====================================================

void enterDefaultMode() {
  if (stateMutex != NULL) {
    xSemaphoreTake(stateMutex, portMAX_DELAY);

    currentMode = MODE_DEFAULT;
    collectionActive = false;
    collectionPaused = false;
    transferRequested = false;
    transferInProgress = false;
    forceDisplayRefresh = true;

    xSemaphoreGive(stateMutex);
  } else {
    currentMode = MODE_DEFAULT;
    collectionActive = false;
    collectionPaused = false;
    transferRequested = false;
    transferInProgress = false;
    forceDisplayRefresh = true;
  }

  clearButtonEvents();

  Serial.println("[Modes] Entrou em DEFAULT.");
}

// =====================================================
// Entrar no modo Calibração
// =====================================================

void enterCalibrationMode() {
  setCurrentMode(MODE_CALIBRATION);

  // Ao entrar no modo calibração, mede imediatamente a posição inicial.
  calibrateInitialPosition();

  requestDisplayRefresh();
  clearButtonEvents();

  Serial.println("[Modes] Entrou em CALIBRACAO.");
}

// =====================================================
// Entrar no modo Coleta
// =====================================================

void enterCollectionMode() {
  resetDataBuffer();

  if (stateMutex != NULL) {
    xSemaphoreTake(stateMutex, portMAX_DELAY);

    currentMode = MODE_COLLECTION;

    collectionActive = true;
    collectionPaused = false;

    collectionStartMs = millis();

    lcdSampleDividerCounter = 0;

    transferRequested = false;
    transferInProgress = false;

    forceDisplayRefresh = true;

    xSemaphoreGive(stateMutex);
  } else {
    currentMode = MODE_COLLECTION;

    collectionActive = true;
    collectionPaused = false;

    collectionStartMs = millis();

    lcdSampleDividerCounter = 0;

    transferRequested = false;
    transferInProgress = false;

    forceDisplayRefresh = true;
  }

  clearButtonEvents();

  Serial.println("[Modes] Entrou em COLETA.");
}

// =====================================================
// Entrar no modo Transferência
// =====================================================

void enterTransferMode() {
  if (stateMutex != NULL) {
    xSemaphoreTake(stateMutex, portMAX_DELAY);

    currentMode = MODE_TRANSFER;

    collectionActive = false;
    collectionPaused = false;

    transferRequested = false;
    transferInProgress = false;

    forceDisplayRefresh = true;

    xSemaphoreGive(stateMutex);
  } else {
    currentMode = MODE_TRANSFER;

    collectionActive = false;
    collectionPaused = false;

    transferRequested = false;
    transferInProgress = false;

    forceDisplayRefresh = true;
  }

  clearButtonEvents();

  Serial.println("[Modes] Entrou em TRANSFERENCIA.");
}

// =====================================================
// Atualização geral da máquina de estados
// =====================================================

void updateModeMachine() {
  SystemMode mode = getCurrentMode();

  switch (mode) {
    case MODE_DEFAULT:
      handleDefaultMode();
      break;

    case MODE_CALIBRATION:
      handleCalibrationMode();
      break;

    case MODE_COLLECTION:
      handleCollectionMode();
      break;

    case MODE_TRANSFER:
      handleTransferMode();
      break;

    default:
      enterDefaultMode();
      break;
  }
}

// =====================================================
// DEFAULT
// =====================================================
//
// B1 -> Calibração
// B2 -> Coleta
// B3 -> Transferência
//

static void handleDefaultMode() {
  if (consumeButtonPress(BUTTON_1)) {
    enterCalibrationMode();
    return;
  }

  if (consumeButtonPress(BUTTON_2)) {
    enterCollectionMode();
    return;
  }

  if (consumeButtonPress(BUTTON_3)) {
    enterTransferMode();
    return;
  }
}

// =====================================================
// CALIBRAÇÃO
// =====================================================
//
// B1 -> Recalibrar
// B2 -> Confirmar e voltar ao Default
// B3 -> Zerar posição inicial e voltar ao Default
//

static void handleCalibrationMode() {
  if (consumeButtonPress(BUTTON_1)) {
    calibrateInitialPosition();
    requestDisplayRefresh();

    Serial.println("[Modes] Recalibrado.");
    return;
  }

  if (consumeButtonPress(BUTTON_2)) {
    Serial.println("[Modes] Calibracao confirmada.");
    enterDefaultMode();
    return;
  }

  if (consumeButtonPress(BUTTON_3)) {
  if (stateMutex != NULL) {
    xSemaphoreTake(stateMutex, portMAX_DELAY);

    initialPositionCm = 0.0f;
    latestDistanceCm = 0.0f;
    latestRelativePositionCm = 0.0f;
    latestVoltage = 0.0f;
    calibrated = false;
    forceDisplayRefresh = true;

    xSemaphoreGive(stateMutex);
  } else {
    initialPositionCm = 0.0f;
    latestDistanceCm = 0.0f;
    latestRelativePositionCm = 0.0f;
    latestVoltage = 0.0f;
    calibrated = false;
    forceDisplayRefresh = true;
  }

  Serial.println("[Modes] Posicao inicial zerada. Mantendo modo CALIBRACAO.");

  requestDisplayRefresh();

  return;
}
}

// =====================================================
// COLETA
// =====================================================
//
// B1 -> Pause / Resume
// B2 -> Reset dos dados
// B3 -> Voltar ao Default
//

static void handleCollectionMode() {
  if (consumeButtonPress(BUTTON_1)) {
    bool pausedCopy = false;

    if (stateMutex != NULL) {
      xSemaphoreTake(stateMutex, portMAX_DELAY);

      collectionPaused = !collectionPaused;
      pausedCopy = collectionPaused;
      forceDisplayRefresh = true;

      xSemaphoreGive(stateMutex);
    } else {
      collectionPaused = !collectionPaused;
      pausedCopy = collectionPaused;
      forceDisplayRefresh = true;
    }

    if (pausedCopy) {
      Serial.println("[Modes] Coleta pausada.");
    } else {
      Serial.println("[Modes] Coleta retomada.");
    }

    requestDisplayRefresh();
    return;
  }

  if (consumeButtonPress(BUTTON_2)) {
    resetDataBuffer();

    if (stateMutex != NULL) {
      xSemaphoreTake(stateMutex, portMAX_DELAY);

      collectionStartMs = millis();

      // Reativa a coleta após resetar a memória
      collectionActive = true;
      collectionPaused = false;

      lcdSampleDividerCounter = 0;

      latestRelativePositionCm = 0.0f;

      forceDisplayRefresh = true;

      xSemaphoreGive(stateMutex);
    } else {
      collectionStartMs = millis();

      collectionActive = true;
      collectionPaused = false;

      lcdSampleDividerCounter = 0;

      latestRelativePositionCm = 0.0f;

      forceDisplayRefresh = true;
    }

    Serial.println("[Modes] Dados resetados. Coleta reiniciada.");
    requestDisplayRefresh();
    return;
  }

  if (consumeButtonPress(BUTTON_3)) {
    Serial.println("[Modes] Saindo da coleta.");
    enterDefaultMode();
    return;
  }

 if (isDataBufferFull()) {
    bool shouldUpdateDisplay = false;

    if (stateMutex != NULL) {
      xSemaphoreTake(stateMutex, portMAX_DELAY);

      // Só executa uma vez, quando a coleta ainda estava ativa.
      if (collectionActive) {
        collectionPaused = true;
        collectionActive = false;
        forceDisplayRefresh = true;
        shouldUpdateDisplay = true;
      }

      xSemaphoreGive(stateMutex);
    } else {
      if (collectionActive) {
        collectionPaused = true;
        collectionActive = false;
        forceDisplayRefresh = true;
        shouldUpdateDisplay = true;
      }
    }

    if (shouldUpdateDisplay) {
      Serial.println("[Modes] Buffer cheio. Coleta interrompida.");
      requestDisplayRefresh();
    }
  }
}

// =====================================================
// TRANSFERÊNCIA
// =====================================================
//
// B1 -> Solicitar envio
// B2 -> Voltar ao Default
// B3 -> Sem função
//

static void handleTransferMode() {
  if (consumeButtonPress(BUTTON_1)) {
    requestBluetoothTransfer();
    requestDisplayRefresh();
    return;
  }

  if (consumeButtonPress(BUTTON_2)) {
    Serial.println("[Modes] Saindo da transferencia.");
    enterDefaultMode();
    return;
  }

  if (consumeButtonPress(BUTTON_3)) {
    uint16_t newMax = cycleMaxDataPoints();

    Serial.print("[Modes] Novo limite maximo de dados: ");
    Serial.println(newMax);

    requestDisplayRefresh();

    return;
  }
}