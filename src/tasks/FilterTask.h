#ifndef FILTER_TASK_H
#define FILTER_TASK_H

#define FILTER_TASK_STACK_SIZE 512
#define FILTER_TASK_PRIORITY 4
#define FILTER_TASK_PERIOD_MS 20
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "../fc_data.h"

extern FC_Data fc_data;
extern SemaphoreHandle_t fc_data_mutex;

extern TaskHandle_t filterTaskHandle;

void task_Filter(void *pvParameters);
void init_task_Filter(void);

#endif