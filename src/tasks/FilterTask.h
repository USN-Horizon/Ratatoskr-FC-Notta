#ifndef FILTER_TASK_H
#define FILTER_TASK_H

#define FILTER_TASK_STACK_SIZE 512
#define FILTER_TASK_PRIORITY 4
#define FILTER_TASK_PERIOD_MS 20
#include "FreeRTOS.h"
#include "task.h"

extern TaskHandle_t filterTaskHandle;

void task_Filter(void *pvParameters);
void init_task_Filter(void);

#endif