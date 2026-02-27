#include "HAL_true.h"

HAL_true::HAL_true()
    :
    wire(Wire)
{}

bool HAL_true::Begin() {
    Wire.begin();

    imu = new IMU_ICM20948(wire);
    baro = new Barometer_MS5611(wire);
    gnss = new GNSS_MAXM10S(wire);

    if (!CheckAllSensorInit()) {
        return false;
    }

    good = true;

    return true;
}

bool HAL_true::CheckAllSensorInit() const {
    if (!HAL::CheckAllSensorInit()) {
        Serial.print("[HAL]: One or more sensor failed to initialise");
        return false;
    }

    return true;
}

bool HAL_true::CheckSensor(const Sensor * const sensor, int &error_count) const {
    if (sensor->Good()) {
        Serial.print("[HAL]: Sensor \"");
        Serial.print(sensor->Name().c_str());
        Serial.println("\" initialised successfully.");

        return true;
    }
    else {
        Serial.print("[HAL]: Sensor \"");
        Serial.print(sensor->Name().c_str());
        Serial.println("\" failed to initialise.");

        return false;
    }
}
