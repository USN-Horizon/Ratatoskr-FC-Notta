#ifndef SENSOR_BASE_H
#define SENSOR_BASE_H

#include "../../src/fc_data.h"

// Base class for all sensors
class Sensor_Base {
public:
    Sensor_Base();
    virtual bool Init() = 0;                   // Initialize sensor, returns true if succesful
    virtual void ReadTo(FC_Data& fc_data) = 0; // Read sensor(s) and store values in shared memory
    virtual bool Available() = 0;              // Returns true if sensor is ready to be read
};

#endif