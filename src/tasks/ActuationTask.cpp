#include "ActuationTask.h"


TaskHandle_t actuationTaskHandle = NULL;
FlightState flight_state = NOT_READY;
FC_Data fc_data;
SemaphoreHandle_t fc_data_mutex;

#include <cstddef>

template <typename T>
void analogWrite(int pin, T value) {

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
        analogWrite

        // Execute deployment sequences (drougue, and main)
        switch (flight_state) {
			case DROUGE:

			break;
			case MAIN:

			break;
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