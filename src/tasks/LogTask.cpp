#include "LogTask.h"

TaskHandle_t logTaskHandle = NULL;

void task_Log(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(LOG_TASK_PERIOD_MS);
    
    while (1) {
        // Log raw sensor data
        
        // Log filtered/processed data
        
        // Log flight events and state changes
        
        // Write to SD card and/or flash memory
        
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void init_task_Log(void) {
    xTaskCreate(
        task_Log,
        "LogTask",
        LOG_TASK_STACK_SIZE,
        NULL,
        LOG_TASK_PRIORITY,
        &logTaskHandle
    );
}