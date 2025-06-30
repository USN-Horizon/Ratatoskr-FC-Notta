#ifndef STATE_TASK_H
#define STATE_TASK_H

#define STATE_TASK_STACK_SIZE 256
#define STATE_TASK_PRIORITY 6
#define STATE_TASK_PERIOD_MS 500
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "../fc_data.h"

extern FC_Data fc_data;
extern SemaphoreHandle_t fc_data_mutex;

extern TaskHandle_t stateTaskHandle;

void task_State(void *pvParameters);
void init_task_State(void);

#endif