#ifndef IMU_LSM6DSO32_H
#define IMU_LSM6DSO32_H

#include "sensor.h"
#include <Adafruit_LSM6DSO32.h>

#include "Adafruit_Sensor.h"

class IMU_LSM6DSO32 : public Sensor {
public:
    IMU_LSM6DSO32(const String& name = "IMU (LSM6DSO32)");
    ~IMU_LSM6DSO32() override;

    void Read(FC_Data &data) override;

private:
    // LIBRARY OBJECTS / MEMBERS
    Adafruit_LSM6DSO32 imu;
};

#endif // IMU_LSM6DSO32_H


