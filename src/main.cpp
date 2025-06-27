#include "arduino_freertos.h"
#include "tasks/SensorTask.h"
#include "tasks/FilterTask.h"
#include "tasks/LogTask.h"
#include "tasks/ActuationTask.h"
#include "tasks/RadioTask.h"
#include "tasks/StateTask.h"


void setup() {
  Serial.begin(9600);
  
  init_task_Sensor();
  init_task_Filter();
  init_task_Log();
  init_task_Actuation();
  init_task_Radio();
  init_task_State();
  
  vTaskStartScheduler();
}

void loop() {
  // Not used
}
