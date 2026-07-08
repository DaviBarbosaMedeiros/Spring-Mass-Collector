#ifndef MODES_H
#define MODES_H

#include "Globals.h"

// =====================================================
// Inicialização da máquina de estados
// =====================================================

void initModes();

// =====================================================
// Atualização da máquina de estados
// =====================================================
//
// Deve ser chamada continuamente.
// Futuramente será chamada por uma Task própria.
//

void updateModeMachine();

// =====================================================
// Funções de entrada nos modos
// =====================================================

void enterDefaultMode();
void enterCalibrationMode();
void enterCollectionMode();
void enterTransferMode();

// =====================================================
// Funções auxiliares de estado
// =====================================================

SystemMode getCurrentMode();
void setCurrentMode(SystemMode newMode);

#endif