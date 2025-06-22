#ifndef RADIO_TASK_H
#define RADIO_TASK_H

#define RADIO_TASK_STACK_SIZE 512
#define RADIO_TASK_PRIORITY 2
#define RADIO_TASK_PERIOD_MS 500
#include "FreeRTOS.h"
#include "task.h"

extern TaskHandle_t radioTaskHandle;

void task_Radio(void *pvParameters);
void init_task_Radio(void);

#endif