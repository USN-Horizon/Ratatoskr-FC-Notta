#include "LSM6DSO32Sensor.h"

LSM6DSO32Sensor::LSM6DSO32Sensor(String n) 
    : Sensor(n) 
{}

bool LSM6DSO32Sensor::setup() {
    if (!imu.begin_I2C()) {
        Serial.print(F("["));
        Serial.print(name);
        Serial.println(F("] kunne ikke finne LSM6DSO32 på I2C!"));
        setReady(false);
        return false;
    }

    // Konfigurer måleområder og sample rate
    imu.setAccelRange(LSM6DSO32_ACCEL_RANGE_8_G);  // 4/8/16/32 G
    imu.setGyroRange(LSM6DS_GYRO_RANGE_2000_DPS);  // 125-2000 dps
    imu.setAccelDataRate(LSM6DS_RATE_104_HZ);      // typisk 104 Hz
    imu.setGyroDataRate(LSM6DS_RATE_104_HZ);

    setReady(true);
    return true;
}

void LSM6DSO32Sensor::update() {
    if (!isReady()) return;

    imu.getEvent(&accel, &gyro, &temp);
}

void LSM6DSO32Sensor::info() {
    Sensor::info();
    if (isReady()) {
        Serial.print(F("  Accel (m/s^2): X="));
        Serial.print(accel.acceleration.x);
        Serial.print(F(" Y="));
        Serial.print(accel.acceleration.y);
        Serial.print(F(" Z="));
        Serial.println(accel.acceleration.z);

        Serial.print(F("  Gyro (rad/s): X="));
        Serial.print(gyro.gyro.x);
        Serial.print(F(" Y="));
        Serial.print(gyro.gyro.y);
        Serial.print(F(" Z="));
        Serial.println(gyro.gyro.z);

        Serial.print(F("  Temp (°C): "));
        Serial.println(temp.temperature);
    }
}

