#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include <math.h>

#include <DIYables_LCD_I2C.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#include <BluetoothSerial.h>
#pragma GCC diagnostic pop

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

// =====================================================
// IDENTIFICAÇÃO DO DISPOSITIVO
// =====================================================

#define DEVICE_NAME "MassaMolaESP32"

// =====================================================
// DISPLAY LCD 16x2 I2C
// =====================================================

#define LCD_I2C_ADDRESS 0x27
#define LCD_COLUMNS     16
#define LCD_ROWS        2

extern DIYables_LCD_I2C lcd;

// =====================================================
// BLUETOOTH
// =====================================================

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
extern BluetoothSerial SerialBT;
#pragma GCC diagnostic pop

// =====================================================
// PINOS
// =====================================================

const uint8_t BUTTON_QTD = 3;

extern const uint8_t buttonPins[BUTTON_QTD];

const uint8_t SENSOR_PIN = 39;

// =====================================================
// BOTÕES
// =====================================================
//
// Assumindo ligação:
//
// GPIO ---- botão ---- GND
//
// Usaremos INPUT_PULLUP.
// Portanto:
//
// botão solto       -> HIGH
// botão pressionado -> LOW
//

const uint8_t BUTTON_ACTIVE_STATE = LOW;

const uint8_t BUTTON_1 = 0;
const uint8_t BUTTON_2 = 1;
const uint8_t BUTTON_3 = 2;

const uint32_t BUTTON_DEBOUNCE_MS = 50;

// =====================================================
// SENSOR SHARP
// =====================================================

const uint8_t SENSOR_FILTER_SAMPLES = 25;

const float SHARP_COEFF_A = 10.1502f;
const float SHARP_COEFF_B = -0.958329f;

const float ADC_REF_VOLTAGE = 3.3f;
const float ADC_MAX_VALUE   = 4095.0f;

// =====================================================
// TEMPORIZAÇÃO
// =====================================================
//
// SAMPLE_INTERVAL_MS controla a taxa de coleta.
// 25 ms -> 40 Hz
// 10 ms -> 100 Hz
//

const uint32_t SAMPLE_INTERVAL_MS = 25;

// O LCD será atualizado mais lentamente que o sensor.
// Isso reduz flickering e travamentos de interface.

const uint32_t LCD_INTERVAL_MS = 100;

// Mostra no LCD apenas uma fração dos dados.
// 4 significa: armazena todas as amostras, mas mostra 1 em cada 4.

const uint8_t LCD_DISPLAY_SAMPLE_DIVIDER = 4;

// Pequenos intervalos das tarefas FreeRTOS

const uint32_t TASK_BUTTON_DELAY_MS    = 10;
const uint32_t TASK_LCD_DELAY_MS       = 20;
const uint32_t TASK_BLUETOOTH_DELAY_MS = 50;
const uint32_t TASK_MODE_DELAY_MS      = 20;

// =====================================================
// ARMAZENAMENTO
// =====================================================
//
// Cada ponto:
// uint32_t time_ms    -> 4 bytes
// float position_cm   -> 4 bytes
//
// Total: aproximadamente 8 bytes por ponto.
//
// 5000 pontos -> aproximadamente 40 kB.
//

// Capacidade física máxima do vetor na memória.
// Esse valor define o tamanho real do array.
const uint16_t DATA_BUFFER_CAPACITY = 5000;

// Valor padrão usado ao iniciar o sistema.
const uint16_t DEFAULT_MAX_DATA_POINTS = 5000;

// Opções disponíveis para o usuário configurar no modo transferência.
extern const uint16_t maxDataOptions[];
extern const uint8_t maxDataOptionsCount;

// Quantidade máxima atualmente configurada.
// Pode ser alterada pelo botão 3 no modo transferência.
extern volatile uint16_t maxDataPoints;

// =====================================================
// MODOS DO SISTEMA
// =====================================================

enum SystemMode {
  MODE_DEFAULT = 0,
  MODE_CALIBRATION,
  MODE_COLLECTION,
  MODE_TRANSFER
};

// =====================================================
// ESTRUTURAS
// =====================================================

struct SensorData {
  float voltage;
  float distance_cm;
};

struct DataPoint {
  uint32_t time_ms;
  float position_cm;
};

// =====================================================
// BUFFER DE DADOS
// =====================================================

extern DataPoint dataBuffer[DATA_BUFFER_CAPACITY];

extern volatile uint16_t dataCount;
extern volatile bool dataBufferFull;

// =====================================================
// VARIÁVEIS GLOBAIS COMPARTILHADAS
// =====================================================

extern volatile SystemMode currentMode;

extern volatile bool collectionActive;
extern volatile bool collectionPaused;

extern volatile bool calibrated;

extern volatile float initialPositionCm;
extern volatile float latestDistanceCm;
extern volatile float latestRelativePositionCm;
extern volatile float latestVoltage;

extern volatile uint32_t collectionStartMs;

extern volatile uint8_t lcdSampleDividerCounter;

extern volatile bool transferRequested;
extern volatile bool transferInProgress;

extern volatile bool forceDisplayRefresh;

// =====================================================
// MUTEXES
// =====================================================
//
// dataMutex  -> protege o vetor de dados
// stateMutex -> protege modo, flags e posições
// lcdMutex   -> protege acesso ao LCD
//

extern SemaphoreHandle_t dataMutex;
extern SemaphoreHandle_t stateMutex;
extern SemaphoreHandle_t lcdMutex;

// =====================================================
// FUNÇÕES AUXILIARES GLOBAIS
// =====================================================

const char* modeToString(SystemMode mode);

#endif