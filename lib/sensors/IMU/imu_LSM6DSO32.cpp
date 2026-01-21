#include "imu_LSM6DSO32.h"

IMU_LSM6DSO32::IMU_LSM6DSO32(const String& name)
    :
    Sensor(name)
{
    if (!imu.begin_I2C()) {
        Serial.print("Could not find sensor ");
        Serial.print(Name());
        Serial.println(" on I2C");
        return;
    }

    imu.setAccelRange(LSM6DSO32_ACCEL_RANGE_8_G);  // 4/8/16/32 G
    imu.setGyroRange(LSM6DS_GYRO_RANGE_2000_DPS);  // 125-2000 dps
    imu.setAccelDataRate(LSM6DS_RATE_104_HZ);      // Typically 104 Hz
    imu.setGyroDataRate(LSM6DS_RATE_104_HZ);

    good = true;
}

IMU_LSM6DSO32::~IMU_LSM6DSO32() = default;

void IMU_LSM6DSO32::Read(FC_Data &data) {
    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temp;

    imu.getEvent(&accel, &gyro, &temp);

    data.imu_acc_raw = {accel.acceleration.x, accel.acceleration.y, accel.acceleration.z};
    data.imu_ang_vel_raw = {gyro.orientation.heading, gyro.orientation.pitch, gyro.orientation.roll };
}


