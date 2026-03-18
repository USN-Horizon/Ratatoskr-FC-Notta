#ifndef SENSOR_BASE_H
#define SENSOR_BASE_H

#include <string>
#include "../../src/fc_data.h"

class Sensor {
public:
    explicit Sensor(const std::string& name);
    virtual ~Sensor() = default;

    // Read from the sensor, implementation specific
    virtual void Read(FC_Data& data) = 0;

    // Current state of the sensor
    bool Good() const;

    // Name of this sensor instance
    const std::string& Name() const;

protected:
    std::string name;
    bool good = false;
};

#endif // SENSOR_BASE_H
