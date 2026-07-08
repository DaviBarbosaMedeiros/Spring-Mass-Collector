#ifndef TASKS_H
#define TASKS_H

#include "Globals.h"

// =====================================================
// Inicialização das Tasks FreeRTOS
// =====================================================

void initTasks();

// =====================================================
// Tasks
// =====================================================

void taskSensor(void *pvParameters);
void taskButtons(void *pvParameters);
void taskModes(void *pvParameters);
void taskDisplay(void *pvParameters);
void taskBluetooth(void *pvParameters);

#endif