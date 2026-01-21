#ifndef IMU_ICM20948_H
#define IMU_ICM20948_H

#include "sensor.h"

#include <Wire.h>
#include <ICM_20948.h>

class IMU_ICM20948 : public Sensor {
public:
    IMU_ICM20948(TwoWire& wire, bool ad0_pin = LOW, String& name = "IMU (ICM20948)");
    ~IMU_ICM20948() override;

    void Read(FC_Data &data) override;
private:
    ICM_20948_I2C icm;
};

#endif //IMU_ICM20948_H
