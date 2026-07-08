#include "Display.h"
#include "Storage.h"

// =====================================================
// Variáveis internas do Display
// =====================================================

static SystemMode lastDisplayedMode = MODE_DEFAULT;

static float lastDisplayedPosition = 999999.0f;
static float lastDisplayedInitialPosition = 999999.0f;
static uint16_t lastDisplayedCount = 65535;
static bool lastDisplayedPaused = false;
static bool lastDisplayedFull = false;

// =====================================================
// Inicialização
// =====================================================

void initDisplay() {
  lcd.init();
  lcd.backlight();

  lcdSafeClear();

  showSplashScreen();

  Serial.println("[Display] Inicializado.");
}

// =====================================================
// Limpeza segura do LCD
// =====================================================

void lcdSafeClear() {
  if (lcdMutex != NULL) {
    xSemaphoreTake(lcdMutex, portMAX_DELAY);

    lcd.clear();

    xSemaphoreGive(lcdMutex);
  } else {
    lcd.clear();
  }
}

// =====================================================
// Imprime linha completa sem deixar caracteres antigos
// =====================================================

void lcdPrintLine(uint8_t row, const char *text) {
  char buffer[17];

  uint8_t i = 0;

  while (i < 16 && text[i] != '\0') {
    buffer[i] = text[i];
    i++;
  }

  while (i < 16) {
    buffer[i] = ' ';
    i++;
  }

  buffer[16] = '\0';

  if (lcdMutex != NULL) {
    xSemaphoreTake(lcdMutex, portMAX_DELAY);

    lcd.setCursor(0, row);
    lcd.print(buffer);

    xSemaphoreGive(lcdMutex);
  } else {
    lcd.setCursor(0, row);
    lcd.print(buffer);
  }
}

// =====================================================
// Solicita atualização completa
// =====================================================

void requestDisplayRefresh() {
  if (stateMutex != NULL) {
    xSemaphoreTake(stateMutex, portMAX_DELAY);
    forceDisplayRefresh = true;
    xSemaphoreGive(stateMutex);
  } else {
    forceDisplayRefresh = true;
  }
}

// =====================================================
// Tela inicial
// =====================================================

void showSplashScreen() {
  lcdSafeClear();

  lcdPrintLine(0, "Massa-Mola");
  lcdPrintLine(1, "Inicializando");
}

// =====================================================
// Tela Default
// =====================================================

void showDefaultScreen(bool force) {
  if (force) {
    lcdSafeClear();
  }

  lcdPrintLine(0, "1-Cal 2-Col");
  lcdPrintLine(1, "3-Transf");
}

// =====================================================
// Tela Calibração
// =====================================================

void showCalibrationScreen(bool force) {
  float initCopy = 0.0f;
  bool calibratedCopy = false;

  if (stateMutex != NULL) {
    xSemaphoreTake(stateMutex, portMAX_DELAY);

    initCopy = initialPositionCm;
    calibratedCopy = calibrated;

    xSemaphoreGive(stateMutex);
  } else {
    initCopy = initialPositionCm;
    calibratedCopy = calibrated;
  }

  if (!force && fabs(initCopy - lastDisplayedInitialPosition) < 0.01f) {
    return;
  }

  if (force) {
    lcdSafeClear();
  }

  char line1[17];
  char line2[17];

  if (calibratedCopy) {
    snprintf(line1, sizeof(line1), "Pos Inicial:");
    snprintf(line2, sizeof(line2), "%7.2f cm", initCopy);
  } else {
    snprintf(line1, sizeof(line1), "Nao calibrado");
    snprintf(line2, sizeof(line2), "B1 para medir");
  }

  lcdPrintLine(0, line1);
  lcdPrintLine(1, line2);

  lastDisplayedInitialPosition = initCopy;
}

// =====================================================
// Tela Coleta
// =====================================================

void showCollectionScreen(bool force) {
  float posCopy = 0.0f;
  bool pausedCopy = false;
  bool fullCopy = false;

  if (stateMutex != NULL) {
    xSemaphoreTake(stateMutex, portMAX_DELAY);

    posCopy = latestRelativePositionCm;
    pausedCopy = collectionPaused;

    xSemaphoreGive(stateMutex);
  } else {
    posCopy = latestRelativePositionCm;
    pausedCopy = collectionPaused;
  }

  uint16_t countCopy = getDataCount();
  fullCopy = isDataBufferFull();

  bool positionChanged = fabs(posCopy - lastDisplayedPosition) >= 0.01f;
  bool countChanged = countCopy != lastDisplayedCount;
  bool pausedChanged = pausedCopy != lastDisplayedPaused;
  bool fullChanged = fullCopy != lastDisplayedFull;

  if (!force && !positionChanged && !countChanged && !pausedChanged && !fullChanged) {
    return;
  }

  if (force) {
    lcdSafeClear();
  }

  char line1[17];
  char line2[17];

  snprintf(line1, sizeof(line1), "x:%8.2f cm", posCopy);

  if (fullCopy) {
    snprintf(line2, sizeof(line2), "MEMORIA CHEIA");
  } else if (pausedCopy) {
    snprintf(line2, sizeof(line2), "N:%5u PAUSE", countCopy);
  } else {
    snprintf(line2, sizeof(line2), "N:%5u RUN", countCopy);
  }

  lcdPrintLine(0, line1);
  lcdPrintLine(1, line2);

  lastDisplayedPosition = posCopy;
  lastDisplayedCount = countCopy;
  lastDisplayedPaused = pausedCopy;
  lastDisplayedFull = fullCopy;
}

// =====================================================
// Tela Transferência
// =====================================================

void showTransferScreen(bool force) {
  bool transferCopy = false;

  uint16_t countCopy = getDataCount();
  uint16_t maxCopy = getMaxDataPoints();

  if (stateMutex != NULL) {
    xSemaphoreTake(stateMutex, portMAX_DELAY);

    transferCopy = transferInProgress;

    xSemaphoreGive(stateMutex);
  } else {
    transferCopy = transferInProgress;
  }

  if (force) {
    lcdSafeClear();
  }

  char line1[17];
  char line2[17];

  if (transferCopy) {
    snprintf(line1, sizeof(line1), "Transferindo");
    snprintf(line2, sizeof(line2), "Aguarde...");
  } else {
    snprintf(line1, sizeof(line1), "Modo Transfer");
    snprintf(line2, sizeof(line2), "D:%4u M:%4u", countCopy, maxCopy);
  }

  lcdPrintLine(0, line1);
  lcdPrintLine(1, line2);
}

// =====================================================
// Atualização geral do display
// =====================================================

void updateDisplay() {
  SystemMode modeCopy = MODE_DEFAULT;
  bool forceCopy = false;

  if (stateMutex != NULL) {
    xSemaphoreTake(stateMutex, portMAX_DELAY);

    modeCopy = currentMode;
    forceCopy = forceDisplayRefresh;

    if (forceDisplayRefresh) {
      forceDisplayRefresh = false;
    }

    xSemaphoreGive(stateMutex);
  } else {
    modeCopy = currentMode;
    forceCopy = forceDisplayRefresh;
    forceDisplayRefresh = false;
  }

  if (modeCopy != lastDisplayedMode) {
    forceCopy = true;
    lastDisplayedMode = modeCopy;

    lastDisplayedPosition = 999999.0f;
    lastDisplayedInitialPosition = 999999.0f;
    lastDisplayedCount = 65535;
    lastDisplayedPaused = false;
    lastDisplayedFull = false;
  }

  switch (modeCopy) {
    case MODE_DEFAULT:
      showDefaultScreen(forceCopy);
      break;

    case MODE_CALIBRATION:
      showCalibrationScreen(forceCopy);
      break;

    case MODE_COLLECTION:
      showCollectionScreen(forceCopy);
      break;

    case MODE_TRANSFER:
      showTransferScreen(forceCopy);
      break;

    default:
      showDefaultScreen(true);
      break;
  }
}