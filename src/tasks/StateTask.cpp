#include "StateTask.h"

TaskHandle_t stateTaskHandle = NULL;

#include <cstddef>

void task_State(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(STATE_TASK_PERIOD_MS);
    
    while (1) {
        // Check current state and flight data

        // Update state if necessary
        
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void init_task_State(void) {
    xTaskCreate(
        task_State,
        "StateTask",
        STATE_TASK_STACK_SIZE,
        NULL,
        STATE_TASK_PRIORITY,
        &stateTaskHandle
    );
}