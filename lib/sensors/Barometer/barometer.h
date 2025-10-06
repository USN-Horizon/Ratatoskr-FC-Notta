#ifndef BAROMETER_H
#define BAROMETER_H

#include "../../src/fc_data.h"

// Base Barometer class
class Barometer {
public:
    Barometer() = default;
    virtual ~Barometer() = 0;
    virtual void Read(FC_Data& data) = 0;
private:
};

#endif // BAROMETER_H