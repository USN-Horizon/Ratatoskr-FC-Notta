#ifndef HAL_H
#define HAL_H

#include "../sensors/Barometer/barometer.h"
#include "../sensors/IMU/imu.h"

// Hardware Abstraction Layer
// Allows for custom and controlled implementation of hardware elements (mainly for testing)
class HAL {
public:
    HAL();
    ~HAL();

    Barometer* GetBarometer();
    IMU* GetIMU();
private:
    Barometer* baro;
    IMU* imu;
};

#endif // HAL_H