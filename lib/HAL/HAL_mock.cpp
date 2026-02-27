#include "HAL_mock.h"

bool HAL_mock::Begin() {
    imu = new IMU_Mock();
    baro = new Barometer_Mock();
    gnss = new GNSS_Mock();

    if (!CheckAllSensorInit()) {
        return false;
    }

    good = true;

    return true;
}