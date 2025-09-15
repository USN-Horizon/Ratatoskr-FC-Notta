#include "SensorTask.h"
#include "../../lib/sensors/BME280.cpp"
#include "../../lib/sensors/LSM6DSO32.cpp"
#include "../../lib/sensors/MAX_M10S.cpp"
#include "../../lib/sensors/kx134.cpp"

TaskHandle_t sensorTaskHandle = NULL;

KX134Sensor kx134(500);

void task_Sensor(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(SENSOR_TASK_PERIOD_MS);

    if(!kx134.setup()){
        Serial.println(F("[SensorTask] KX134 init failed!"));
    }
    else{
        kx134.info();
    }

    
    while (1) {
        kx134.update();
        
        // Read IMU data
        
        // Read BME280
        
        // Read other sensors (GPS,..)
        
        // Store readings in shared data structure (TODO)
        
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void init_task_Sensor() {
    xTaskCreate(
        task_Sensor,
        "SensorTask",
        SENSOR_TASK_STACK_SIZE,
        NULL,
        SENSOR_TASK_PRIORITY,
        &sensorTaskHandle
    );
}
