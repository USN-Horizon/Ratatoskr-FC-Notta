#ifndef IMU_MOCK_H
#define IMU_MOCK_H

#include "sensor.h"

class IMU_Mock : public Sensor {
public:
    IMU_Mock();
    ~IMU_Mock() override;

    void Read(FC_Data& data) override;
};

#endif // IMU_MOCK_H