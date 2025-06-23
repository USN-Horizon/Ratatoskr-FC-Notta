#ifndef LOG_TASK_H
#define LOG_TASK_H


#define LOG_TASK_STACK_SIZE 512
#define LOG_TASK_PRIORITY 1
#define LOG_TASK_PERIOD_MS 100
#include "FreeRTOS.h"
#include "task.h"

extern TaskHandle_t logTaskHandle;

void task_Log(void *pvParameters);
void init_task_Log(void);

#endif