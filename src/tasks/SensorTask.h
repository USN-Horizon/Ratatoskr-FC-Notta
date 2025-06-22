#ifndef SENSOR_TASK_H
#define SENSOR_TASK_H

#define SENSOR_TASK_STACK_SIZE 256
#define SENSOR_TASK_PRIORITY 3
#define SENSOR_TASK_PERIOD_MS 10
#include "FreeRTOS.h"
#include "task.h"

extern TaskHandle_t sensorTaskHandle;

void task_Sensor(void *pvParameters);
void init_task_Sensor(void);

#endif