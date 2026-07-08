#include "Storage.h"

// =====================================================
// Inicialização
// =====================================================

void initStorage() {
  resetDataBuffer();

  Serial.println("[Storage] Inicializado.");
}

// =====================================================
// Reset do buffer
// =====================================================

void resetDataBuffer() {
  if (dataMutex != NULL) {
    xSemaphoreTake(dataMutex, portMAX_DELAY);

    dataCount = 0;
    dataBufferFull = false;

    xSemaphoreGive(dataMutex);
  } else {
    dataCount = 0;
    dataBufferFull = false;
  }

  Serial.println("[Storage] Buffer limpo.");
}

// =====================================================
// Adiciona ponto ao buffer
// =====================================================

bool addDataPoint(uint32_t timeMs, float positionCm) {
  bool stored = false;

  if (dataMutex != NULL) {
    xSemaphoreTake(dataMutex, portMAX_DELAY);

    if (dataCount < maxDataPoints) {
      dataBuffer[dataCount].time_ms = timeMs;
      dataBuffer[dataCount].position_cm = positionCm;

      dataCount++;
      stored = true;

      if (dataCount >= maxDataPoints) {
        dataBufferFull = true;
      }
    } else {
      dataBufferFull = true;
      stored = false;
    }

    xSemaphoreGive(dataMutex);
  } else {
    if (dataCount < maxDataPoints) {
      dataBuffer[dataCount].time_ms = timeMs;
      dataBuffer[dataCount].position_cm = positionCm;

      dataCount++;
      stored = true;

      if (dataCount >= maxDataPoints) {
        dataBufferFull = true;
      }
    } else {
      dataBufferFull = true;
      stored = false;
    }
  }

  return stored;
}

// =====================================================
// Recupera um ponto específico
// =====================================================

bool getDataPoint(uint16_t index, DataPoint *point) {
  if (point == NULL) {
    return false;
  }

  bool success = false;

  if (dataMutex != NULL) {
    xSemaphoreTake(dataMutex, portMAX_DELAY);

    if (index < dataCount) {
      point->time_ms = dataBuffer[index].time_ms;
      point->position_cm = dataBuffer[index].position_cm;
      success = true;
    }

    xSemaphoreGive(dataMutex);
  } else {
    if (index < dataCount) {
      point->time_ms = dataBuffer[index].time_ms;
      point->position_cm = dataBuffer[index].position_cm;
      success = true;
    }
  }

  return success;
}

// =====================================================
// Recupera o último ponto armazenado
// =====================================================

bool getLatestDataPoint(DataPoint *point) {
  if (point == NULL) {
    return false;
  }

  bool success = false;

  if (dataMutex != NULL) {
    xSemaphoreTake(dataMutex, portMAX_DELAY);

    if (dataCount > 0) {
      uint16_t lastIndex = dataCount - 1;

      point->time_ms = dataBuffer[lastIndex].time_ms;
      point->position_cm = dataBuffer[lastIndex].position_cm;

      success = true;
    }

    xSemaphoreGive(dataMutex);
  } else {
    if (dataCount > 0) {
      uint16_t lastIndex = dataCount - 1;

      point->time_ms = dataBuffer[lastIndex].time_ms;
      point->position_cm = dataBuffer[lastIndex].position_cm;

      success = true;
    }
  }

  return success;
}

// =====================================================
// Retorna quantidade de pontos
// =====================================================

uint16_t getDataCount() {
  uint16_t countCopy = 0;

  if (dataMutex != NULL) {
    xSemaphoreTake(dataMutex, portMAX_DELAY);
    countCopy = dataCount;
    xSemaphoreGive(dataMutex);
  } else {
    countCopy = dataCount;
  }

  return countCopy;
}

// =====================================================
// Verifica se buffer está cheio
// =====================================================

bool isDataBufferFull() {
  bool fullCopy = false;

  if (dataMutex != NULL) {
    xSemaphoreTake(dataMutex, portMAX_DELAY);
    fullCopy = dataBufferFull;
    xSemaphoreGive(dataMutex);
  } else {
    fullCopy = dataBufferFull;
  }

  return fullCopy;
}

// =====================================================
// Exportação CSV
// =====================================================

void printDataCSV(Stream &output) {
  uint16_t countCopy = getDataCount();

  output.println("t_ms,pos_cm");

  for (uint16_t i = 0; i < countCopy; i++) {
    DataPoint point;

    if (getDataPoint(i, &point)) {
      output.print(point.time_ms);
      output.print(",");
      output.println(point.position_cm, 4);
    }

    // Pequeno respiro para não travar a ESP32 em transferências grandes.
    if ((i % 50) == 0) {
      vTaskDelay(pdMS_TO_TICKS(1));
    }
  }

  output.println("END");
}

// =====================================================
// Status do armazenamento
// =====================================================

void printStorageStatus(Stream &output) {
  output.print("[Storage] Pontos armazenados: ");
  output.print(getDataCount());
  output.print(" / ");
  output.println(getMaxDataPoints());

  output.print("[Storage] Capacidade fisica: ");
  output.println(DATA_BUFFER_CAPACITY);

  output.print("[Storage] Buffer cheio: ");

  if (isDataBufferFull()) {
    output.println("SIM");
  } else {
    output.println("NAO");
  }
}

// =====================================================
// Define o limite máximo de dados
// =====================================================

void setMaxDataPoints(uint16_t newMax) {
  if (newMax < 1) {
    newMax = 1;
  }

  if (newMax > DATA_BUFFER_CAPACITY) {
    newMax = DATA_BUFFER_CAPACITY;
  }

  if (dataMutex != NULL) {
    xSemaphoreTake(dataMutex, portMAX_DELAY);

    maxDataPoints = newMax;

    if (dataCount >= maxDataPoints) {
      dataBufferFull = true;
    } else {
      dataBufferFull = false;
    }

    xSemaphoreGive(dataMutex);
  } else {
    maxDataPoints = newMax;

    if (dataCount >= maxDataPoints) {
      dataBufferFull = true;
    } else {
      dataBufferFull = false;
    }
  }

  Serial.print("[Storage] Novo limite maximo de dados: ");
  Serial.println(newMax);
}

// =====================================================
// Retorna limite máximo de dados
// =====================================================

uint16_t getMaxDataPoints() {
  uint16_t maxCopy = DEFAULT_MAX_DATA_POINTS;

  if (dataMutex != NULL) {
    xSemaphoreTake(dataMutex, portMAX_DELAY);
    maxCopy = maxDataPoints;
    xSemaphoreGive(dataMutex);
  } else {
    maxCopy = maxDataPoints;
  }

  return maxCopy;
}

// =====================================================
// Alterna entre opções de limite máximo
// =====================================================

uint16_t cycleMaxDataPoints() {
  uint16_t currentMax = getMaxDataPoints();
  uint16_t nextMax = maxDataOptions[0];

  for (uint8_t i = 0; i < maxDataOptionsCount; i++) {
    if (maxDataOptions[i] > currentMax) {
      nextMax = maxDataOptions[i];
      break;
    }
  }

  setMaxDataPoints(nextMax);

  return nextMax;
}