#ifndef BUTTONS_H
#define BUTTONS_H

#include "Globals.h"

// =====================================================
// Inicialização dos botões
// =====================================================

void initButtons();

// =====================================================
// Atualização dos botões
// =====================================================
//
// Deve ser chamada repetidamente.
// Futuramente será chamada por uma Task própria no Core 0.
//

void updateButtons();

// =====================================================
// Leitura de eventos
// =====================================================
//
// Retorna true apenas uma vez por clique.
// Depois que o evento é lido, ele é apagado.
//

bool consumeButtonPress(uint8_t buttonIndex);

// Retorna true enquanto o botão estiver fisicamente pressionado.
bool isButtonHeld(uint8_t buttonIndex);

// Apaga todos os eventos pendentes.
void clearButtonEvents();

// =====================================================
// Funções auxiliares
// =====================================================

const char* buttonName(uint8_t buttonIndex);

#endif