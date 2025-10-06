#ifndef IMU_H
#define IMU_H

#include "../../src/fc_data.h"

// Base IMU class
class IMU {
public:
    IMU() = default;
    virtual ~IMU() = 0;
    virtual void Read(FC_Data& data) = 0;
private:
};

#endif // IMU_H