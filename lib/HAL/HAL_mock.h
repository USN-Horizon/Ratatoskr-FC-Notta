#ifndef HAL_MOCK_H
#define HAL_MOCK_H

#include "HAL.h"

#include "../sensors/IMU/imu_mock.h"
#include "../sensors/Barometer/barometer_mock.h"
#include "../sensors/GNSS/gnss_mock.h"

class HAL_mock final : public HAL {
public:
    bool Begin() override;
};

#endif //HAL_MOCK_H
