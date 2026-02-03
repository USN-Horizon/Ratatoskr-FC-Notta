#include "ActuationTask.h"
#include <cstddef>
#include <iostream>

TaskHandle_t actuationTaskHandle = NULL;


void task_Actuation(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(ACTUATION_TASK_PERIOD_MS);
    Servo.attach(Servo_Pin, 0, Servo_Angle);
    
    while (1) {

        // Check flight state and control requirements
        while (fc_data.flightstate == FlightState::NOT_READY || fc_data.flightstate == FlightState::ARMED)
        {
            if (!Servo.attached())
            {
                Serial.println("Servo attachment has failed");
                Servo.attach(Servo_Pin, 0, Servo_Angle);
            }
            delay(100);
        }

        // Calculate servo/motor commands
        constexpr auto min_angle = Servo_Angle / 2;

        // Execute deployment sequences (drougue, and main)
        switch (fc_data.flightstate) {
        case FlightState::DROUGE:
            // first deployment sequence:
			Servo.write(min_angle);
			break;
        case FlightState::MAIN:
            // second deployment sequence:
			Servo.write(Servo_Angle);
			break;
		}

        // Safety checks and failsafe operations

        if (Servo.read() > Servo_Angle || Servo.read() < 0)
        {
            //the servo could potentially get damaged beyond 180 degrees or below 0
            Servo.detach();
            Serial.println("Servo has been detached");
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