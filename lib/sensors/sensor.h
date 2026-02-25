#ifndef SENSOR_BASE_H
#define SENSOR_BASE_H

#include <Arduino.h>
#include "../../src/fc_data.h"

class Sensor {
public:
    explicit Sensor(const String& name);
    virtual ~Sensor() = default;

    // Read from the sensor, implementation specific
    virtual void Read(FC_Data& data) = 0;

    // Current state of the sensor
    bool Good() const;

    void PrintStatus() const;

    // Name of this sensor instance
    const String& Name() const;

protected:
    String name;
    bool good = false;
};

#endif // SENSOR_BASE_H
