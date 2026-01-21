#include "ActuationTask.h"
#include <cstddef>

TaskHandle_t actuationTaskHandle = NULL;




void task_Actuation(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(ACTUATION_TASK_PERIOD_MS);
    
    while (1) {
        // Check flight state and control requirements
        if (fc_data.flightstate == FlightState::NOT_READY) {
			//not ready yet....

		}

        // Calculate servo/motor commands

        // Execute deployment sequences (drougue, and main)
        switch (fc_data.flightstate) {
        case FlightState::DROUGE:
            // first deployment sequence:

			break;
        case FlightState::MAIN:
            // second deployment sequence:

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