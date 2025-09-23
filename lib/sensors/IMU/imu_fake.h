#ifndef IMU_FAKE_H
#define IMU_FAKE_H

#include "imu.h"

// Custom IMU implementation
class IMU_Fake : public IMU {
public:
    void Read(FC_Data &data) override {
        // Our own, custom implementation here...

        data.imu_acc_raw = {};
        data.imu_ang_vel_raw = {};
        data.imu_mag_raw = {};
    }
private:
};

#endif // IMU_FAKE_H