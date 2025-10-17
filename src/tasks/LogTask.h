#ifndef LOG_TASK_H
#define LOG_TASK_H


#define LOG_TASK_STACK_SIZE 512
#define LOG_TASK_PRIORITY 1
#define LOG_TASK_PERIOD_MS 100
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "../fc_data.h"

extern FC_Data fc_data;
extern SemaphoreHandle_t fc_data_mutex;

extern TaskHandle_t logTaskHandle;

void task_Log(void *pvParameters);
void init_task_Log(void);

#endif