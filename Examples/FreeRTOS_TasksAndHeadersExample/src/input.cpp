#include <Arduino.h>  // Defines standard Arduino functions
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "../include/pins.h"
#include "input.h"

// External global variables must be declared like this to avoid errors!
extern int global_value;
extern SemaphoreHandle_t mutexValue;

void Task_ReadValue(void* pvParameters) {
  while (true) {
    // When button is pressed:
    if (digitalRead(PIN_BUT) == LOW) {
      // Read potmeter if it's free
      int potVal = analogRead(PIN_POT);;

      // Update global_value when it's free
      if (xSemaphoreTake(mutexValue, 0) == pdPASS) {
        global_value = potVal;

        xSemaphoreGive(mutexValue);
      }

      // Wait until button is released
      while (digitalRead(PIN_BUT) == LOW)
        ;
    }
  }
}

void Init_Task_ReadValue() {
  // This could also be done in setup()

  xTaskCreate(
    Task_ReadValue, // The task itself (the function pointer)
    "Read Value",   // Human readable name for task
    128,            // Stack size (not that important for small tasks)
    NULL,           // Pointer to task paramters
    1,              // Task priority
    NULL            // Task handle (to communicate with other tasks)
  );
}