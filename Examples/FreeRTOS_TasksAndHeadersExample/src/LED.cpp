#include <Arduino.h>  // Defines standard Arduino functions
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#include "../include/pins.h"
#include "LED.h"

// External global variables must be declared like this to avoid errors!
extern int global_value;
extern SemaphoreHandle_t mutexValue;

void Task_BlinkLED(void* pvParameters) {
  bool state = false;
  int blink_delay = 0;

  while (true) {
    // Update delay when value is free
    if (xSemaphoreTake(mutexValue, 0) == pdPASS) {
      blink_delay = global_value * 2;
      xSemaphoreGive(mutexValue);
    }

    // Blink the LED
    state = !state;
    digitalWrite(PIN_LED_R, state);

    // Wait a bit
    vTaskDelay(blink_delay / portTICK_PERIOD_MS);
  }
}

void Init_Task_BlinkLED() {
  // This could also be done in setup()
  xTaskCreate(Task_BlinkLED, "Blink LED", 128, NULL, 1, NULL);
}
