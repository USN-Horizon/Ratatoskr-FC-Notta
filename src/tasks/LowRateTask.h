#ifndef LOW_RATE_TASK_H
#define LOW_RATE_TASK_H

// TODO: Calibrate values
#define LOW_RATE_TASK_STACK_SIZE 256
#define LOW_RATE_TASK_PRIORITY 3
#define LOW_RATE_TASK_PERIOD_MS 10

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "../fc_data.h"

extern FC_Data fc_data;
extern SemaphoreHandle_t fc_data_mutex;

extern TaskHandle_t LowRateTaskHandle;

void task_LowRate(void *pvParameters);
void init_task_LowRate(void);

#endif