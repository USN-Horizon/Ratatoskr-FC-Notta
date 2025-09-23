#ifndef IMU_TRUE_H
#define IMU_TRUE

#include "imu.h"
// INCLUDE SENSOR LIBRARIES

// True IMU implementation
class IMU_True : public IMU {
public:
    IMU_True()
        :
        IMU::IMU()
    {
        // INITIALIZE
    }
    
    void Read(FC_Data &data) override {
        // ACTUAL IMPLEMENTATION HERE
    }
private:
    // LIBRARY OBJECTS / OTHER MEMBER DATA
};

#endif // IMU_TRUE_H