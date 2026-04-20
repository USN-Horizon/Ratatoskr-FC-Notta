#ifndef ACTUATION_TASK_H
#define ACTUATION_TASK_H

#define ACTUATION_TASK_STACK_SIZE 256
#define ACTUATION_TASK_PRIORITY 5
#define ACTUATION_TASK_PERIOD_MS 50

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "../fc_data.h"
#include <PWMServo.h>

extern FC_Data fc_data;
extern SemaphoreHandle_t fc_data_mutex;

extern TaskHandle_t actuationTaskHandle;

// Servos are continuous (not positional).
constexpr int servo_idle_speed = 90;

constexpr int HPRS_Servo_speed = 180;
constexpr int HPRS_Servo_time_ms = 2000;
constexpr int HPRS_Servo_pin = 10; // TODO: Determine value
extern PWMServo HPRS_Servo;

constexpr int MCRS_Servo_speed = 180; // TODO: Determine value
constexpr int MCRS_Servo_time_ms = 2000; // TODO: Determine value
constexpr int MCRS_Servo_pin = 10; // TODO: Determine value
extern PWMServo MCRS_Servo;

void task_Actuation(void *pvParameters);
void init_task_Actuation(void);

#endif