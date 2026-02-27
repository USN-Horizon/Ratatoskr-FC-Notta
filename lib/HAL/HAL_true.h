#ifndef HAL_TRUE_H
#define HAL_TRUE_H

#include "HAL.h"

#include <Arduino.h>
#include <Wire.h>
#include "../sensors/IMU/imu_ICM20948.h"
#include "../sensors/Barometer/barometer_MS5611.h"
#include "../sensors/GNSS/gnss_MAXM10S.h"

class HAL_true final : public HAL {
public:
    HAL_true();
    bool Begin() override;

private:
    TwoWire& wire;

    bool CheckAllSensorInit() const override;
    bool CheckSensor(const Sensor* const sensor, int& error_count) const override;
};

#endif
