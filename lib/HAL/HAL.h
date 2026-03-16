#ifndef HAL_H
#define HAL_H

#include "../sensors/sensor.h"

class HAL {
public:
    HAL();
    virtual ~HAL();

    virtual bool Begin() = 0;
    bool Good() const;

    const Sensor* IMU() const;
    const Sensor* Barometer() const;
    const Sensor* GNSS() const;
protected:
    bool good = false;

    // Sensors
    Sensor *imu = nullptr, *baro = nullptr, *gnss = nullptr;

protected:
    virtual bool CheckAllSensorInit() const;
    virtual bool CheckSensor(const Sensor* const sensor, int& error_count) const;
};

#endif // HAL_H