#include "RadioTask.h"

TaskHandle_t radioTaskHandle = NULL;

void task_Radio(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(RADIO_TASK_PERIOD_MS);
    
    while (1) {
        // Transmit telemetry data
        
        // (Receive ground commands?) We need to be able to specify testing mode, where each actuation can be triggered manually for testing
        
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void init_task_Radio(void) {
    xTaskCreate(
        task_Radio,
        "RadioTask",
        RADIO_TASK_STACK_SIZE,
        NULL,
        RADIO_TASK_PRIORITY,
        &radioTaskHandle
    );
}