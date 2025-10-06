#include "arduino_freertos.h"
#include "semphr.h"
#include "tasks/SensorTask.h"
#include "tasks/FilterTask.h"
#include "tasks/LogTask.h"
#include "tasks/ActuationTask.h"
#include "tasks/RadioTask.h"
#include "tasks/StateTask.h"

// Extern definition in task.h will allow the task to use these values
FC_Data fc_data;
// This mutex will lock all values in fc_data, even values that are not correlated.
// If this becomes a problem, we could create multiple mutexes that lock each value seperatelly instead.
SemaphoreHandle_t fc_data_mutex; 

void setup() {
  Serial.begin(9600);

  fc_data_mutex = xSemaphoreCreateMutex();
  if (fc_data_mutex == NULL) {
    Serial.println("fc_data_mutex could not be created.");
    while (true);
  }

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
