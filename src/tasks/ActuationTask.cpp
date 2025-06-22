#include "ActuationTask.h"

TaskHandle_t actuationTaskHandle = NULL;

#include <cstddef>

void task_Actuation(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(ACTUATION_TASK_PERIOD_MS);
    
    while (1) {
        // Check flight state and control requirements
        
        // Calculate servo/motor commands
        
        // Execute deployment sequences (drougue, and main)
        
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