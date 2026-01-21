#ifndef BARO_MS5611_H
#define BARO_MS5611_H

#include "sensor.h"
#include <Wire.h>
#include "MS5611.h"

class Barometer_MS5611 : public Sensor {
public:
    Barometer_MS5611(TwoWire& wire, int i2c_addr = MS5611_DEFAULT_ADDRESS, const String& name = "Barometer (MS5611)");
    ~Barometer_MS5611() override;

    void Read(FC_Data &data) override;

private:
    MS5611 baro;
};

#endif BARO_MS5611_H
