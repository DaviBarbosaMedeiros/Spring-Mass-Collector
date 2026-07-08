#ifndef STORAGE_H
#define STORAGE_H

#include "Globals.h"

// =====================================================
// Inicialização do armazenamento
// =====================================================

void initStorage();

// =====================================================
// Controle do buffer
// =====================================================

// Limpa o buffer de dados.
// Não apaga fisicamente todos os valores antigos;
// apenas zera o contador, o que é muito mais rápido.
void resetDataBuffer();

// Adiciona um ponto no vetor.
// Retorna true se conseguiu armazenar.
// Retorna false se o buffer já estiver cheio.
bool addDataPoint(uint32_t timeMs, float positionCm);

// Retorna true se conseguiu copiar o ponto desejado.
bool getDataPoint(uint16_t index, DataPoint *point);

// Retorna o último ponto armazenado.
bool getLatestDataPoint(DataPoint *point);

// Retorna a quantidade atual de dados armazenados.
uint16_t getDataCount();

// Retorna true se o buffer estiver cheio.
bool isDataBufferFull();

// =====================================================
// Exportação dos dados
// =====================================================

// Imprime os dados em formato CSV em qualquer objeto Stream.
// Funciona com Serial e com BluetoothSerial.
void printDataCSV(Stream &output);

// Imprime um resumo do buffer.
void printStorageStatus(Stream &output);

// =====================================================
// Configuração do limite máximo de dados
// =====================================================

// Define a quantidade máxima de pontos que podem ser armazenados.
// O valor nunca pode passar da capacidade física do vetor.
void setMaxDataPoints(uint16_t newMax);

// Retorna o limite máximo atualmente configurado.
uint16_t getMaxDataPoints();

// Avança para a próxima opção de limite máximo.
// Exemplo: 500 -> 1000 -> 2000 -> 3000 -> 5000 -> 500
uint16_t cycleMaxDataPoints();

#endif