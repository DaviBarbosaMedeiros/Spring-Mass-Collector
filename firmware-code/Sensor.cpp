#include "Sensor.h"

// =====================================================
// Função auxiliar: ordenação simples
// =====================================================
// Como o número de amostras é pequeno, uma ordenação simples
// é suficiente e mantém o código fácil de entender.
//
// Usamos uint16_t porque analogRead() na ESP32 retorna valores
// entre 0 e 4095.

static void sortSamples(uint16_t *values, uint8_t n) {
  for (uint8_t i = 1; i < n; i++) {
    uint16_t key = values[i];
    int8_t j = i - 1;

    while (j >= 0 && values[j] > key) {
      values[j + 1] = values[j];
      j--;
    }

    values[j + 1] = key;
  }
}

// =====================================================
// Inicialização do sensor
// =====================================================

void initSensor() {
  pinMode(SENSOR_PIN, INPUT);

  // ESP32: resolução padrão de 12 bits.
  // Faixa de leitura: 0 a 4095.
  analogReadResolution(12);

  // Atenuação de 11 dB permite ler tensões próximas de 3.3 V.
  // Importante para sensores analógicos alimentados em 3.3 V.
  analogSetPinAttenuation(SENSOR_PIN, ADC_11db);

  Serial.println("[Sensor] Inicializado.");
}

// =====================================================
// Conversão tensão -> distância
// =====================================================

float voltageToDistanceCm(float voltage) {
  // Proteção contra divisão por zero ou valores inválidos.
  if (voltage <= 0.001f) {
    return 0.0f;
  }

  return SHARP_COEFF_A * powf(voltage, SHARP_COEFF_B);
}

// =====================================================
// Leitura filtrada do sensor
// =====================================================

SensorData readSensor() {
  uint16_t samples[SENSOR_FILTER_SAMPLES];

  // -----------------------------
  // Coleta das amostras ADC
  // -----------------------------
  for (uint8_t i = 0; i < SENSOR_FILTER_SAMPLES; i++) {
    samples[i] = analogRead(SENSOR_PIN);

    // Pequeno intervalo entre leituras para reduzir ruído imediato.
    delayMicroseconds(200);
  }

  // -----------------------------
  // Ordenação das amostras
  // -----------------------------
  sortSamples(samples, SENSOR_FILTER_SAMPLES);

  // -----------------------------
  // Média aparada
  // -----------------------------
  // Remove aproximadamente 15% dos menores valores
  // e 15% dos maiores valores.
  //
  // Isso reduz picos e leituras espúrias do ADC.

  uint8_t startIndex = (uint8_t)(SENSOR_FILTER_SAMPLES * 0.15f);
  uint8_t endIndex   = (uint8_t)(SENSOR_FILTER_SAMPLES * 0.85f);

  if (endIndex <= startIndex) {
    startIndex = 0;
    endIndex = SENSOR_FILTER_SAMPLES;
  }

  uint32_t sum = 0;
  uint8_t count = 0;

  for (uint8_t i = startIndex; i < endIndex; i++) {
    sum += samples[i];
    count++;
  }

  float adcMean = 0.0f;

  if (count > 0) {
    adcMean = (float)sum / (float)count;
  }

  // -----------------------------
  // Conversão ADC -> tensão
  // -----------------------------

  float voltage = adcMean * ADC_REF_VOLTAGE / ADC_MAX_VALUE;

  // -----------------------------
  // Conversão tensão -> distância
  // -----------------------------

  float distanceCm = voltageToDistanceCm(voltage);

  SensorData data;
  data.voltage = voltage;
  data.distance_cm = distanceCm;

  return data;
}

// =====================================================
// Posição relativa
// =====================================================

float calculateRelativePosition(float distanceCm) {
  float initPosCopy = 0.0f;

  if (stateMutex != NULL) {
    xSemaphoreTake(stateMutex, portMAX_DELAY);
    initPosCopy = initialPositionCm;
    xSemaphoreGive(stateMutex);
  } else {
    initPosCopy = initialPositionCm;
  }

  return distanceCm - initPosCopy;
}

// =====================================================
// Atualização das variáveis globais do sensor
// =====================================================

void updateLatestSensorData() {
  SensorData data = readSensor();

  float relativePosition = 0.0f;

  if (stateMutex != NULL) {
    xSemaphoreTake(stateMutex, portMAX_DELAY);

    latestVoltage = data.voltage;
    latestDistanceCm = data.distance_cm;
    latestRelativePositionCm = latestDistanceCm - initialPositionCm;

    relativePosition = latestRelativePositionCm;

    xSemaphoreGive(stateMutex);
  } else {
    latestVoltage = data.voltage;
    latestDistanceCm = data.distance_cm;
    latestRelativePositionCm = latestDistanceCm - initialPositionCm;

    relativePosition = latestRelativePositionCm;
  }

  // Esse Serial.print é útil apenas para depuração.
  // Não usaremos isso durante a coleta final em alta frequência.
  //
  // Serial.print("[Sensor] x_rel = ");
  // Serial.println(relativePosition);
}

// =====================================================
// Calibração da posição inicial
// =====================================================

float calibrateInitialPosition() {
  SensorData data = readSensor();

  if (stateMutex != NULL) {
    xSemaphoreTake(stateMutex, portMAX_DELAY);

    initialPositionCm = data.distance_cm;
    latestVoltage = data.voltage;
    latestDistanceCm = data.distance_cm;
    latestRelativePositionCm = 0.0f;
    calibrated = true;

    xSemaphoreGive(stateMutex);
  } else {
    initialPositionCm = data.distance_cm;
    latestVoltage = data.voltage;
    latestDistanceCm = data.distance_cm;
    latestRelativePositionCm = 0.0f;
    calibrated = true;
  }

  Serial.print("[Sensor] Calibrado. Posicao inicial = ");
  Serial.print(data.distance_cm, 3);
  Serial.println(" cm");

  return data.distance_cm;
}