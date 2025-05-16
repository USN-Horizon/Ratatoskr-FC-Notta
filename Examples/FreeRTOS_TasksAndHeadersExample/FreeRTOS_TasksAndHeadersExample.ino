/*  -- Setup --
There's a potentiometer, a button and a LED wired to the Arduino.
When the button is pressed, the value from the potmeter gets written to a global variable. (Task_ReadValue)
The LED blinks constantly, the delay is read from the global value. (Task_BlinkLED)
Also, the global value gets printed to Serial Monitor in a set interval. (Task_LogValue)
*/

// Library includes
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// Other includes
#include "src/input.h"
#include "src/LED.h"
#include "src/log.h"
#include "include/pins.h"

// Global variable read/written to by tasks
int global_value;
// Mutex protects global_value and syncronizes tasks
SemaphoreHandle_t mutexValue;

void setup() {
  // Intitialization of Serial Monitior and pins (regular old Arduino-business)
  Serial.begin(9600);

  pinMode(PIN_POT, INPUT);
  pinMode(PIN_BUT, INPUT_PULLUP);
  pinMode(PIN_LED_R, OUTPUT);

  // Create the mutex and check if it was successfull
  mutexValue = xSemaphoreCreateMutex();
  if (mutexValue == NULL) {
    // Might fail due to lack of memory, shouldn't be a problem here though
    Serial.println("Mutex could not be created!");
    while (true)
      ;
  }

  // Create tasks
  Init_Task_ReadValue();
  Init_Task_LogValue();
  Init_Task_BlinkLED();

  // Finally, start the scheduler
  vTaskStartScheduler();
}

void loop() {
  // Not used
}
