#include "Globals.h"

// =====================================================
// OBJETOS GLOBAIS
// =====================================================

DIYables_LCD_I2C lcd(LCD_I2C_ADDRESS, LCD_COLUMNS, LCD_ROWS);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
BluetoothSerial SerialBT;
#pragma GCC diagnostic pop

// =====================================================
// PINOS DOS BOTÕES
// =====================================================

const uint8_t buttonPins[BUTTON_QTD] = {
  25,  // Botão 1
  33,  // Botão 2
  32   // Botão 3
};

// =====================================================
// BUFFER DE DADOS
// =====================================================

const uint16_t maxDataOptions[] = {
  500,
  1000,
  2000,
  3000,
  5000
};

const uint8_t maxDataOptionsCount =
  sizeof(maxDataOptions) / sizeof(maxDataOptions[0]);

volatile uint16_t maxDataPoints = DEFAULT_MAX_DATA_POINTS;

DataPoint dataBuffer[DATA_BUFFER_CAPACITY];

volatile uint16_t dataCount = 0;
volatile bool dataBufferFull = false;

// =====================================================
// VARIÁVEIS COMPARTILHADAS
// =====================================================

volatile SystemMode currentMode = MODE_DEFAULT;

volatile bool collectionActive = false;
volatile bool collectionPaused = false;

volatile bool calibrated = false;

volatile float initialPositionCm = 0.0f;
volatile float latestDistanceCm = 0.0f;
volatile float latestRelativePositionCm = 0.0f;
volatile float latestVoltage = 0.0f;

volatile uint32_t collectionStartMs = 0;

volatile uint8_t lcdSampleDividerCounter = 0;

volatile bool transferRequested = false;
volatile bool transferInProgress = false;

volatile bool forceDisplayRefresh = true;

// =====================================================
// MUTEXES
// =====================================================

SemaphoreHandle_t dataMutex  = NULL;
SemaphoreHandle_t stateMutex = NULL;
SemaphoreHandle_t lcdMutex   = NULL;

// =====================================================
// FUNÇÃO AUXILIAR
// =====================================================

const char* modeToString(SystemMode mode) {
  switch (mode) {
    case MODE_DEFAULT:
      return "DEFAULT";

    case MODE_CALIBRATION:
      return "CALIBRATION";

    case MODE_COLLECTION:
      return "COLLECTION";

    case MODE_TRANSFER:
      return "TRANSFER";

    default:
      return "UNKNOWN";
  }
}