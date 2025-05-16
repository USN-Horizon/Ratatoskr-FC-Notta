#include <Arduino.h>  // Defines standard Arduino functions
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "../include/pins.h"
#include "log.h"

// External global variables must be declared like this to avoid errors!
extern int global_value;
extern SemaphoreHandle_t mutexValue;

void Task_LogValue(void* pvParameters) {
  while (true) {
    // Wait until global_value is free
    if (xSemaphoreTake(mutexValue, 0) == pdPASS) {
      // If other tasks would be using Serial aswell, it would be a good idea to protect it with its own mutex
      // In this example it's not necessary :)
      Serial.print("Value: ");
      Serial.println(global_value);

      xSemaphoreGive(mutexValue);
      vTaskDelay(200 / portTICK_PERIOD_MS);
    }
  }
}

void Init_Task_LogValue() {
  // This could also be done in setup()
  xTaskCreate(Task_LogValue, "Log Value", 128, NULL, 1, NULL);
}