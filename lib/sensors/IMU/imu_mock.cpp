#include "imu_mock.h"

IMU_Mock::IMU_Mock()
    :
    Sensor(F("IMU (Mock)"))
{
    good = true;
}

IMU_Mock::~IMU_Mock() = default;

void IMU_Mock::Read(FC_Data &data) {
    // Mock implementation
    return;
}


