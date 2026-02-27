#include "barometer_MS5611.h"

Barometer_MS5611::Barometer_MS5611(TwoWire& wire, int i2c_addr, const std::string& name)
    :
    Sensor(name),
    baro(i2c_addr, &wire)
{
    // I2C object was passed in constructor
    if (!baro.begin()) return;

    good = true;
}

Barometer_MS5611::~Barometer_MS5611() = default;

void Barometer_MS5611::Read(FC_Data &data) {
    baro.read();

    // Note: Library has built-in reading of altitude: baro.getAltitude();
    // Consider using this instead?
    data.baro_pres_raw = baro.getPressure();
}