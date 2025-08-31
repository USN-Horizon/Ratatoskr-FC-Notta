#ifndef KX134_H
#define KX134_H

#include <Arduino.h>
#include <SPI.h>
#include "Sensor.h"  

class KX134Sensor : public Sensor {
public:
    KX134Sensor(unsigned long interval = 100);

    bool setup() override;
    void update() override;
    void info() override;

private:
    uint8_t readRegister(uint8_t reg);
    void writeRegister(uint8_t reg, uint8_t val);
    void readRaw(int16_t &x, int16_t &y, int16_t &z);
};

#endif
