#ifndef DISPLAY_H
#define DISPLAY_H

#include "Globals.h"

// =====================================================
// Inicialização do display
// =====================================================

void initDisplay();

// =====================================================
// Controle geral do display
// =====================================================

// Força redesenho completo na próxima atualização.
// Usado quando há mudança de modo.
void requestDisplayRefresh();

// Atualiza o display de acordo com o modo atual.
// Essa função será chamada pela TaskDisplay futuramente.
void updateDisplay();

// =====================================================
// Telas específicas
// =====================================================

void showSplashScreen();
void showDefaultScreen(bool force);
void showCalibrationScreen(bool force);
void showCollectionScreen(bool force);
void showTransferScreen(bool force);

// =====================================================
// Funções auxiliares
// =====================================================

// Imprime uma linha completa de 16 caracteres.
// Completa com espaços para apagar restos de textos anteriores.
void lcdPrintLine(uint8_t row, const char *text);

// Limpa o LCD apenas quando realmente necessário.
void lcdSafeClear();

#endif