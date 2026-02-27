#include "sensor.h"

Sensor::Sensor(const std::string &name)
    :
    name(name)
{}

bool Sensor::Good() const {
    return good;
}

const std::string& Sensor::Name() const {
    return name;
}


