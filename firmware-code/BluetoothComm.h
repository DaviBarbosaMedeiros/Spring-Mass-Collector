#ifndef BLUETOOTH_COMM_H
#define BLUETOOTH_COMM_H

#include "Globals.h"

// =====================================================
// Inicialização do Bluetooth
// =====================================================

void initBluetoothComm();

// =====================================================
// Atualização da comunicação Bluetooth
// =====================================================
//
// Deve ser chamada continuamente.
// Futuramente será chamada por uma task própria.
//

void updateBluetoothComm();

// =====================================================
// Solicitação de transferência
// =====================================================

void requestBluetoothTransfer();

// =====================================================
// Transferência dos dados
// =====================================================

void sendDataToBluetooth();
void sendDataToSerialAndBluetooth();

// =====================================================
// Status
// =====================================================

bool isBluetoothBusy();

#endif