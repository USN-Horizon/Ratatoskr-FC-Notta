#include "HAL.h"

HAL::HAL() = default;

HAL::~HAL() {
    delete imu;
    delete baro;
    delete gnss;
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

    return error_count == 0;
}

bool HAL::CheckSensor(const Sensor * const sensor, int &error_count) const {
    if (!sensor->Good()) {
        error_count++;
        return false;
    }

    return true;
}