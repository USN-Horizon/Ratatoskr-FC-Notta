#ifndef SENSOR_BAROMETER_H
#define SENSOR_BAROMETER_H

#define BAROMETER_I2C_ADR 0x77

#include "sensor.h"

#include "Adafruit_Sensor.h"
#include "Adafruit_BME280.h"

class Barometer : public Sensor_Base {
public:
    Barometer();

    bool Init() override;
    void ReadTo(FC_Data& fc_data) override;
    bool Available() override;
private:
    Adafruit_BME280 bme;
};

#endif