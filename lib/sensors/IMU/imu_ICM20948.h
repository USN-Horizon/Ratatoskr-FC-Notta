#ifndef IMU_ICM20948_H
#define IMU_ICM20948_H

#include "sensor.h"

#include <Wire.h>
#include <ICM20948_WE.h>

#define ICM20948_ADDR 0x68

class IMU_ICM20948 : public Sensor {
public:
    IMU_ICM20948(TwoWire& wire, int i2c_addr = ICM20948_ADDR, String& name = "IMU (ICM20948)");
    ~IMU_ICM20948() override;

    void Read(FC_Data &data) override;
private:
    ICM20948_WE imu;
};

#endif //IMU_ICM20948_H
