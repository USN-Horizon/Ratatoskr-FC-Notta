#include "ActuationTask.h"
#include <cstddef>
#include <iostream>
TaskHandle_t actuationTaskHandle = NULL;


void task_Actuation(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    constexpr TickType_t xFrequency = pdMS_TO_TICKS(ACTUATION_TASK_PERIOD_MS);

    Servo.attach(Servo_Pin);
    constexpr auto min_angle = Servo_Angle / 2;

    while (1) {

        // Check flight state and control requirements
        while (fc_data.flightstate == FlightState::NOT_READY || fc_data.flightstate == FlightState::ARMED)
        {
            if (!Servo.attached())
            {
                #ifdef DEBUG_MODE
                Serial.println("Servo attachment has failed");
                #endif

                Servo.attach(Servo_Pin);
            }
            else
            {
                #ifdef DEBUG_MODE
                Serial.println("Servo is attached, waiting for takeoff");
                #endif
            }
            vTaskDelay(pdMS_TO_TICKS(30));
        }


        // Execute deployment sequences (drougue, and main)
        switch (fc_data.flightstate) {
        case FlightState::DROUGE:
			Servo.write(min_angle);
			break;
        case FlightState::MAIN:
			Servo.write(Servo_Angle);
			break;
		}

        // Safety checks and failsafe operations

        if (Servo.read() > Servo_Angle || Servo.read() < 0)
        {
            //the servo could potentially get damaged beyond 180 degrees or below 0
            //Servo.detach();

            #ifdef DEBUG_MODE
            Serial.println("Servo has been detached");
            #endif
        }
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void init_task_Actuation(void) {
    xTaskCreate(
        task_Actuation,
        "ActuationTask",
        ACTUATION_TASK_STACK_SIZE,
        NULL,
        ACTUATION_TASK_PRIORITY,
        &actuationTaskHandle
    );
}