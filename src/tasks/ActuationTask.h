#ifndef ACTUATION_TASK_H
#define ACTUATION_TASK_H

#define ACTUATION_TASK_STACK_SIZE 256
#define ACTUATION_TASK_PRIORITY 5
#define ACTUATION_TASK_PERIOD_MS 50
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "../fc_data.h"

extern FC_Data fc_data;
extern SemaphoreHandle_t fc_data_mutex;

extern TaskHandle_t actuationTaskHandle;

extern FlightState flight_state;

void task_Actuation(void *pvParameters);
void init_task_Actuation(void);

#endif