#ifndef SENSOR_H
#define SENSOR_H

#include "Globals.h"

// =====================================================
// Inicialização do sensor
// =====================================================

void initSensor();

// =====================================================
// Leitura do sensor
// =====================================================

// Converte tensão em distância usando o ajuste experimental:
// d = A * V^B
float voltageToDistanceCm(float voltage);

// Lê o sensor, aplica filtragem e retorna tensão + distância.
SensorData readSensor();

// Atualiza as variáveis globais:
// latestVoltage
// latestDistanceCm
// latestRelativePositionCm
void updateLatestSensorData();

// =====================================================
// Calibração
// =====================================================

// Mede a posição atual e define como posição inicial.
// Retorna a posição inicial calibrada.
float calibrateInitialPosition();

// Calcula posição relativa a partir de uma distância absoluta.
float calculateRelativePosition(float distanceCm);

#endif