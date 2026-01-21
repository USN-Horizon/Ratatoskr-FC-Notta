#ifndef HAL_H
#define HAL_H

#include "sensor.h"

class HAL {
public:
    HAL();
    ~HAL();

    bool Good() const;

    const Sensor* IMU() const;
    const Sensor* Barometer() const;
    const Sensor* GNSS() const;
private:
    bool good = false;

    // Sensors
    Sensor *imu = nullptr, *baro = nullptr, *gnss = nullptr;

private:
    bool CheckAllSensorInit() const;
    void CheckSensor(const Sensor* const sensor, int& error_count) const;
};

#endif // HAL_H