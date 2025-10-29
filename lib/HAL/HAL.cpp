#include "HAL.h"

#include "../../include/config.h"

// Based on defines in config.h, include relevant headers
#ifdef USE_MOCK_IMPLEMENTATIONS
#include "../sensors/Barometer/barometer_mock.h"
#include "../sensors/IMU/imu_mock.h"
#else
#include "../sensors/Barometer/barometer_true.h"
#include "../sensors/IMU/imu_true.h"
#endif // USE_MOCK_IMPLEMENTATIONS

HAL::HAL() {
#ifdef USE_MOCK_IMPLEMENTATIONS
    baro = new Barometer_Mock();
    imu = new IMU_Mock();
#else
    baro = new Barometer_True();
    imu = new IMU_True();
#endif // USE_MOCK_IMPLEMENTATIONS
}

HAL::~HAL() {
    delete baro;
    delete imu;
}

Barometer* HAL::GetBarometer() {
    return baro;
}

IMU *HAL::GetIMU() {
    return imu;
}

