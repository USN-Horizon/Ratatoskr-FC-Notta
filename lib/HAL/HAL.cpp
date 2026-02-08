#include "HAL.h"

#include <Arduino.h>
#include "FreeRTOS.h"

HAL::HAL() = default;

HAL::~HAL() {
    delete imu;
    delete baro;
    delete gnss;
}

bool HAL::Begin() {
#ifdef USE_MOCK_IMPLEMENTATIONS
    imu = new IMU_Mock();
    baro = new Barometer_Mock();
    gnss = new GNSS_Mock();
#else
    Wire.begin(); // We could maybe create a mock I2C-interface later?

    imu = new IMU_ICM20948(Wire, LOW);
    baro = new Barometer_MS5611(Wire);
    gnss = new GNSS_MAXM10S(Wire);
#endif // USE_MOCK_IMPLEMENTATIONS

    // Check that all sensors initialised successfully
    if (!CheckAllSensorInit()) {
        return false;
    }

    good = true;

    return true;
}

bool HAL::Good() const {
    return good;
}

const Sensor* HAL::IMU() const {
    return imu;
}

const Sensor* HAL::Barometer() const {
    return baro;
}
const Sensor* HAL::GNSS() const {
    return gnss;
}

bool HAL::CheckAllSensorInit() const {
    int error_count = 0;

    CheckSensor(imu, error_count);
    CheckSensor(baro, error_count);
    CheckSensor(gnss, error_count);

    if (error_count > 0) {
        Serial.print("[HAL]: One or more sensor failed to initialise");
        return false;
    }
    return true;
}

void HAL::CheckSensor(const Sensor * const sensor, int &error_count) const {
    if (sensor->Good()) {
        Serial.print("[HAL]: Sensor \"");
        Serial.print(sensor->Name());
        Serial.println("\" initialised successfully.");
    }
    else {
        error_count++;

        Serial.print("[HAL]: Sensor \"");
        Serial.print(sensor->Name());
        Serial.println("\" failed to initialise.");
    }
}
