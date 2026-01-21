#include "FilterTask.h"
#include "../../lib/filters/kalman_filter.h"

TaskHandle_t filterTaskHandle = NULL;

void task_Filter(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(FILTER_TASK_PERIOD_MS);
    
    while (1) {
        // Apply Kalman and Madgwick filter, and others and such
        
        // Compute attitude estimation
        
        // Calculate velocity and position estimates
        
        // Store processed data for other tasks
        
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void init_task_Filter(void) {
    xTaskCreate(
        task_Filter,
        "FilterTask",
        FILTER_TASK_STACK_SIZE,
        NULL,
        FILTER_TASK_PRIORITY,
        &filterTaskHandle
    );
}