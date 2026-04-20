#include "ActuationTask.h"
#include <cstddef>
#include <iostream>
TaskHandle_t actuationTaskHandle = NULL;

// TODO: Task syncronization

void task_Actuation(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    constexpr TickType_t xFrequency = pdMS_TO_TICKS(ACTUATION_TASK_PERIOD_MS);

    // Attach servos
    HPRS_Servo.attach(HPRS_Servo_pin);
    if (!HPRS_Servo.attached()) {
        #ifdef DEBUG_MODE
        Serial.println("HPRS Servo could not attach!");
        #endif

        // TODO: Error handling
    }

    MCRS_Servo.attach(HPRS_Servo_pin);
    if (!MCRS_Servo.attached()) {
        #ifdef DEBUG_MODE
        Serial.println("MCRS Servo could not attach!");
        #endif

        // TODO: Error handling
    }

    while (1) {
        // Execute deployment sequences when necessary (drougue, and main)
        switch (fc_data.flightstate) {
        case FlightState::APOGEE:
            // Actuate HPRS servoes to deploy drouge chute
            #ifdef DEBUG_MODE
            Serial.println("HPRS Servo actuation begin");
            #endif

			HPRS_Servo.write(HPRS_Servo_speed);
            vTaskDelay(pdMS_TO_TICKS(HPRS_Servo_time_ms));
            HPRS_Servo.write(servo_idle_speed);

            #ifdef DEBUG_MODE
            Serial.println("HPRS Servo actuation finished");
            #endif
            
            // Update flight state
            fc_data.flightstate = FlightState::DROUGE;

			break;
        case FlightState::MAIN:
            // Actuate MCRS servos to release main chute
            #ifdef DEBUG_MODE
            Serial.println("MCRS Servo actuation begin");
            #endif

			MCRS_Servo.write(MCRS_Servo_speed);
            vTaskDelay(pdMS_TO_TICKS(MCRS_Servo_time_ms));
            MCRS_Servo.write(servo_idle_speed);

            #ifdef DEBUG_MODE
            Serial.println("MCRS Servo actuation finished");
            #endif
            
            // Update flight state
            fc_data.flightstate = FlightState::POST_MAIN;

			break;
        default:
            // Do nothing
            break;
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