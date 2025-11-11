#include "ActuationTask.h"
#include "../MAX_M10S.h" //GNSS

TaskHandle_t actuationTaskHandle = NULL;
FlightState flight_state = NOT_READY;
FC_Data fc_data;
SemaphoreHandle_t fc_data_mutex;

#include <cstddef>

MAX_M10S GNSS;

void analogWrite(int pin, int value) {

}

void task_Actuation(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(ACTUATION_TASK_PERIOD_MS);
    
    while (1) {
        // Check flight state and control requirements
        if (flight_state == NOT_READY) {
			//not ready yet....
		}
        // Calculate servo/motor commands
        
        // Execute deployment sequences (drougue, and main)
        switch (flight_state) {
			case NOT_READY:

		}
        // Safety checks and failsafe operations
        
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