#ifndef ACTUATION_TASK_H
#define ACTUATION_TASK_H

#define ACTUATION_TASK_STACK_SIZE 256
#define ACTUATION_TASK_PRIORITY 5
#define ACTUATION_TASK_PERIOD_MS 50
#include "FreeRTOS.h"
#include "task.h"

extern TaskHandle_t actuationTaskHandle;

void task_Actuation(void *pvParameters);
void init_task_Actuation(void);

#endif