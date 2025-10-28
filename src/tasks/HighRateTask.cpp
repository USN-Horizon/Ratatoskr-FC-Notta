#include "HighRateTask.h"

TaskHandle_t HighRateTaskHandle = NULL;

void task_HighRate(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(HIGH_RATE_TASK_PERIOD_MS);
    
    while (1) {
        // Read IMU data
        
        // Read MS5611 data

        // Read accelerometer-module
        
        // Store readings in shared data structure
        
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void init_task_HighRate() {
    xTaskCreate(
        task_HighRate,
        "HighRateTask",
        HIGH_RATE_TASK_STACK_SIZE,
        NULL,
        HIGH_RATE_TASK_PRIORITY,
        &HighRateTaskHandle
    );
}
