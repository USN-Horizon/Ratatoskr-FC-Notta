#include "LowRateTask.h"

TaskHandle_t LowRateTaskHandle = NULL;

void task_Sensor(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(LOW_RATE_TASK_PERIOD_MS);

    while (1) {
        // Read GPS

        // Read battery voltage
        
        // Store readings in shared data structure
        
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void init_task_Sensor() {
    xTaskCreate(
        task_LowRate,
        "LowRateTask",
        LOW_RATE_TASK_STACK_SIZE,
        NULL,
        LOW_RATE_TASK_PRIORITY,
        &LowRateTaskHandle
    );
}
