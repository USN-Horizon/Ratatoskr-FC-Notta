#include "barometer.h"

Barometer::Barometer() 
{}

bool Barometer::Init()
{
    if (!bme.begin(BAROMETER_I2C_ADR)) {
        Serial.print("Sensor \"BME280\" not found at address ");
        Serial.print(BAROMETER_I2C_ADR, HEX);
        return false;
    }
    return true;
}

void Barometer::ReadTo(FC_Data &fc_data) {
    fc_data.baro_pres_raw = bme.readPressure();
    fc_data.baro_temp_raw = bme.readTemperature();
}

bool Barometer::Available()
{
    return true;
}
