#ifndef IMU_MOCK_H
#define IMU_MOCK_H

#include "imu.h"

// Custom IMU implementation
class IMU_Mock : public IMU {
public:
    ~IMU_Mock() override = default;

    void Read(FC_Data &data) override {
        // Our own, custom implementation here...

        data.imu_acc_raw = {};
        data.imu_ang_vel_raw = {};
        data.imu_mag_raw = {};
    }
private:
};

#endif // IMU_MOCK_H