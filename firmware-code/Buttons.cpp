#include "Buttons.h"

// =====================================================
// Variáveis internas dos botões
// =====================================================

static bool lastRawState[BUTTON_QTD] = {HIGH, HIGH, HIGH};
static bool stableState[BUTTON_QTD]  = {HIGH, HIGH, HIGH};

static bool pressedEvent[BUTTON_QTD] = {false, false, false};

static uint32_t lastDebounceTime[BUTTON_QTD] = {0, 0, 0};

// Mutex interno apenas para os botões.
// Ele protege os eventos quando tivermos Tasks diferentes.
static SemaphoreHandle_t buttonMutex = NULL;

// =====================================================
// Inicialização
// =====================================================

void initButtons() {
  buttonMutex = xSemaphoreCreateMutex();

  for (uint8_t i = 0; i < BUTTON_QTD; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);

    bool reading = digitalRead(buttonPins[i]);

    lastRawState[i] = reading;
    stableState[i] = reading;
    pressedEvent[i] = false;
    lastDebounceTime[i] = millis();
  }

  Serial.println("[Buttons] Inicializados.");
}

// =====================================================
// Atualização dos botões com debounce
// =====================================================

void updateButtons() {
  uint32_t now = millis();

  for (uint8_t i = 0; i < BUTTON_QTD; i++) {
    bool reading = digitalRead(buttonPins[i]);

    // Se a leitura bruta mudou, reinicia o temporizador de debounce.
    if (reading != lastRawState[i]) {
      lastDebounceTime[i] = now;
      lastRawState[i] = reading;
    }

    // Se a leitura ficou estável por tempo suficiente, aceita o novo estado.
    if ((now - lastDebounceTime[i]) >= BUTTON_DEBOUNCE_MS) {
      if (reading != stableState[i]) {
        stableState[i] = reading;

        // Evento de clique: acontece apenas na transição para pressionado.
        if (stableState[i] == BUTTON_ACTIVE_STATE) {
          if (buttonMutex != NULL) {
            xSemaphoreTake(buttonMutex, portMAX_DELAY);
            pressedEvent[i] = true;
            xSemaphoreGive(buttonMutex);
          } else {
            pressedEvent[i] = true;
          }

          Serial.print("[Buttons] Pressionado: ");
          Serial.println(buttonName(i));
        }
      }
    }
  }
}

// =====================================================
// Consome evento de clique
// =====================================================

bool consumeButtonPress(uint8_t buttonIndex) {
  if (buttonIndex >= BUTTON_QTD) {
    return false;
  }

  bool eventCopy = false;

  if (buttonMutex != NULL) {
    xSemaphoreTake(buttonMutex, portMAX_DELAY);

    eventCopy = pressedEvent[buttonIndex];

    if (pressedEvent[buttonIndex]) {
      pressedEvent[buttonIndex] = false;
    }

    xSemaphoreGive(buttonMutex);
  } else {
    eventCopy = pressedEvent[buttonIndex];

    if (pressedEvent[buttonIndex]) {
      pressedEvent[buttonIndex] = false;
    }
  }

  return eventCopy;
}

// =====================================================
// Verifica se botão está segurado
// =====================================================

bool isButtonHeld(uint8_t buttonIndex) {
  if (buttonIndex >= BUTTON_QTD) {
    return false;
  }

  return stableState[buttonIndex] == BUTTON_ACTIVE_STATE;
}

// =====================================================
// Limpa eventos pendentes
// =====================================================

void clearButtonEvents() {
  if (buttonMutex != NULL) {
    xSemaphoreTake(buttonMutex, portMAX_DELAY);

    for (uint8_t i = 0; i < BUTTON_QTD; i++) {
      pressedEvent[i] = false;
    }

    xSemaphoreGive(buttonMutex);
  } else {
    for (uint8_t i = 0; i < BUTTON_QTD; i++) {
      pressedEvent[i] = false;
    }
  }
}

// =====================================================
// Nome dos botões
// =====================================================

const char* buttonName(uint8_t buttonIndex) {
  switch (buttonIndex) {
    case BUTTON_1:
      return "B1";

    case BUTTON_2:
      return "B2";

    case BUTTON_3:
      return "B3";

    default:
      return "UNKNOWN";
  }
}