#include "BluetoothComm.h"

#include "Storage.h"
#include "Display.h"

// =====================================================
// Inicialização do Bluetooth
// =====================================================

void initBluetoothComm() {
  Serial.println("[Bluetooth] Inicializando...");

  bool started = SerialBT.begin(DEVICE_NAME);

  if (started) {
    Serial.print("[Bluetooth] Iniciado como: ");
    Serial.println(DEVICE_NAME);
  } else {
    Serial.println("[Bluetooth] ERRO ao iniciar Bluetooth.");
  }
}

// =====================================================
// Solicita transferência
// =====================================================

void requestBluetoothTransfer() {
  if (stateMutex != NULL) {
    xSemaphoreTake(stateMutex, portMAX_DELAY);

    transferRequested = true;
    forceDisplayRefresh = true;

    xSemaphoreGive(stateMutex);
  } else {
    transferRequested = true;
    forceDisplayRefresh = true;
  }

  Serial.println("[Bluetooth] Transferencia solicitada.");
}

// =====================================================
// Verifica se Bluetooth está transferindo
// =====================================================

bool isBluetoothBusy() {
  bool busyCopy = false;

  if (stateMutex != NULL) {
    xSemaphoreTake(stateMutex, portMAX_DELAY);

    busyCopy = transferInProgress;

    xSemaphoreGive(stateMutex);
  } else {
    busyCopy = transferInProgress;
  }

  return busyCopy;
}

// =====================================================
// Envia dados somente pelo Bluetooth
// =====================================================

void sendDataToBluetooth() {
  uint16_t countCopy = getDataCount();

  if (countCopy == 0) {
    SerialBT.println("Sem dados para transferir.");
    Serial.println("[Bluetooth] Sem dados para transferir.");
    return;
  }

  SerialBT.println();
  SerialBT.println("===== MASSA-MOLA ESP32 =====");
  SerialBT.print("Dados armazenados: ");
  SerialBT.println(countCopy);
  SerialBT.println();

  printDataCSV(SerialBT);

  SerialBT.println();
  SerialBT.println("Transferencia concluida.");
}

// =====================================================
// Envia dados pelo Serial e Bluetooth
// =====================================================

void sendDataToSerialAndBluetooth() {
  uint16_t countCopy = getDataCount();

  if (countCopy == 0) {
    Serial.println("[Transfer] Sem dados para transferir.");
    SerialBT.println("Sem dados para transferir.");
    return;
  }

  Serial.println();
  Serial.println("===== MASSA-MOLA ESP32 =====");
  Serial.print("Dados armazenados: ");
  Serial.println(countCopy);
  Serial.println();

  SerialBT.println();
  SerialBT.println("===== MASSA-MOLA ESP32 =====");
  SerialBT.print("Dados armazenados: ");
  SerialBT.println(countCopy);
  SerialBT.println();

  Serial.println("===== CSV SERIAL =====");
  printDataCSV(Serial);

  SerialBT.println("===== CSV BLUETOOTH =====");
  printDataCSV(SerialBT);

  Serial.println("[Transfer] Transferencia concluida.");
  SerialBT.println("Transferencia concluida.");
}

// =====================================================
// Atualização da comunicação Bluetooth
// =====================================================

void updateBluetoothComm() {
  bool requestCopy = false;

  if (stateMutex != NULL) {
    xSemaphoreTake(stateMutex, portMAX_DELAY);

    requestCopy = transferRequested;

    xSemaphoreGive(stateMutex);
  } else {
    requestCopy = transferRequested;
  }

  if (!requestCopy) {
    return;
  }

  // Limpa a solicitação e marca transferência em andamento.
  if (stateMutex != NULL) {
    xSemaphoreTake(stateMutex, portMAX_DELAY);

    transferRequested = false;
    transferInProgress = true;
    forceDisplayRefresh = true;

    xSemaphoreGive(stateMutex);
  } else {
    transferRequested = false;
    transferInProgress = true;
    forceDisplayRefresh = true;
  }

  requestDisplayRefresh();
  updateDisplay();

  Serial.println("[Bluetooth] Iniciando transferencia...");

  sendDataToSerialAndBluetooth();

  // Finaliza transferência.
  if (stateMutex != NULL) {
    xSemaphoreTake(stateMutex, portMAX_DELAY);

    transferInProgress = false;
    forceDisplayRefresh = true;

    xSemaphoreGive(stateMutex);
  } else {
    transferInProgress = false;
    forceDisplayRefresh = true;
  }

  requestDisplayRefresh();
  updateDisplay();

  Serial.println("[Bluetooth] Transferencia finalizada.");
}