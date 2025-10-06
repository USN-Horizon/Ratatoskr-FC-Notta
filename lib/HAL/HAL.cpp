#include "HAL.h"

#include "../../include/config.h"

// Based on defines in config.h, include relevant headers
#ifdef USE_FAKE_IMPLEMENTATIONS
#include "../sensors/Barometer/barometer_fake.h"
#include "../sensors/IMU/imu_fake.h"
#else
#include "../sensors/Barometer/barometer_true.h"
#include "../sensors/IMU/imu_true.h"
#endif // USE_FAKE_IMPLEMENTATIONS

HAL::HAL() {
#ifdef USE_FAKE_IMPLEMENTATIONS
    baro = new Barometer_Fake();
    imu = new IMU_Fake();
#else
    baro = new Barometer_True();
    imu = new IMU_True();
#endif // USE_FAKE_IMPLEMENTATIONS
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

