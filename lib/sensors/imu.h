#ifndef SENSOR_IMU_H
#define SENSOR_IMU_H

#include "sensor.h"

class IMU : public Sensor_Base {
public:
    IMU();

    bool Init() override;
    void ReadTo(FC_Data& fc_data) override;
    bool Available() override;
private:
};

#endif