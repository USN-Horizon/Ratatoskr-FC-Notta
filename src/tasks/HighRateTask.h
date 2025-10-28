#ifndef HIGH_RATE_TASK_H
#define HIGH_RATE_TASK_H

// TODO: Calibrate values
#define HIGH_RATE_TASK_STACK_SIZE 256
#define HIGH_RATE_TASK_PRIORITY 3
#define HIGH_RATE_TASK_PERIOD_MS 10

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "../fc_data.h"

extern FC_Data fc_data;
extern SemaphoreHandle_t fc_data_mutex;

extern TaskHandle_t HighRateTaskHandle;

void task_HighRate(void *pvParameters);
void init_task_HighRate(void);

#endif