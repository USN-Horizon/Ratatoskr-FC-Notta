#ifndef HAL_H
#define HAL_H

#include "../include/config.h"

#ifdef USE_MOCK_IMPLEMENTATIONS
#include "../sensors/IMU/imu_mock.h"
#include "../sensors/Barometer/barometer_mock.h"
#include "../sensors/GNSS/gnss_mock.h"
#else
#include "../sensors/IMU/imu_ICM20948.h"
#include "../sensors/Barometer/barometer_MS5611.h"
#include "../sensors/GNSS/gnss_MAXM10S.h"
#endif // USE_MOCK_IMPLEMENTATIONS

class HAL {
public:
    HAL();
    ~HAL();

    bool Begin();
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