#include "ActuationTask.h"



TaskHandle_t actuationTaskHandle = NULL;
FC_Data fc_data;
SemaphoreHandle_t fc_data_mutex;

#include <cstddef>

const TickType_t delayTime = pdMS_TO_TICKS(50); //delay for 50ms


void task_Actuation(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(ACTUATION_TASK_PERIOD_MS);
    
    while (1) {
        // Check flight state and control requirements
        while (fc_data.flightstate == FlightState::NOT_READY) {
			//not ready yet....
			vTaskDelay(delayTime);
		}

        // Calculate servo/motor commands


        // Execute deployment sequences (drougue, and main)
        switch (fc_data.flightstate) {
        case FlightState::DROUGE:

			break;
        case FlightState::MAIN:

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