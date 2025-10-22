#pragma once
#include <Arduino.h>
#include <Wire.h>
#include "sensorClass.h"

// MS5611 I2C-adresse 
#define MS5611_ADDR 0x77

class MS5611 : public Sensor {
public:
    MS5611(String n = "MS5611");

    bool setup() override;
    void update() override;
    void info() override;

    float getPressure() const { return pressure; }  // i hPa
    float getTemperature() const { return temperature; } // i °C

private:
    uint16_t C[7];      // Kalibreringsdata fra PROM
    float pressure;
    float temperature;

    bool readPROM();
    bool readADC(uint32_t &result, uint8_t cmd);
    bool startConversion(uint8_t cmd);
};
