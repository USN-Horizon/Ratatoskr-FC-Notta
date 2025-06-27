#ifndef STATE_TASK_H
#define STATE_TASK_H

#define STATE_TASK_STACK_SIZE 256
#define STATE_TASK_PRIORITY 6
#define STATE_TASK_PERIOD_MS 500
#include "FreeRTOS.h"
#include "task.h"

extern TaskHandle_t stateTaskHandle;

void task_State(void *pvParameters);
void init_task_State(void);

#endif