#include "imu_mock.h"

IMU_Mock::IMU_Mock()
    :
    Sensor("IMU (Mock)")
{

    good = true;
}

IMU_Mock::~IMU_Mock() = default;

void IMU_Mock::Read(FC_Data &data) {
    data.imu_acc_raw.x = 1.23;
    data.imu_acc_raw.y = 4.56;
    data.imu_acc_raw.z = 7.89;

    // Dummy gyro
    data.imu_ang_vel_raw.x = 0.01;
    data.imu_ang_vel_raw.y = 0.02;
    data.imu_ang_vel_raw.z = 0.03;

    // Dummy magnetometer
    data.imu_mag_raw.x = 10.0;
    data.imu_mag_raw.y = 20.0;
    data.imu_mag_raw.z = 30.0;
    
    return;
}


