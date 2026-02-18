#ifndef ACTUATION_TASK_H
#define ACTUATION_TASK_H

#define ACTUATION_TASK_STACK_SIZE 256
#define ACTUATION_TASK_PRIORITY 5
#define ACTUATION_TASK_PERIOD_MS 50
#define Servo_Angle 180 //angle variable for reference, will be changed once we get more information
#define Servo_Pin 10  // pin number is unknown as of right now, given an arbitrary value

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "../fc_data.h"
#include <Servo.h>

extern FC_Data fc_data;
extern SemaphoreHandle_t fc_data_mutex;

extern TaskHandle_t actuationTaskHandle;

extern Servo Servo;

void task_Actuation(void *pvParameters);
void init_task_Actuation(void);

#endif