#ifndef BAROMETER_TRUE_H
#define BAROMETER_TRUE

#include "barometer.h"
// INCLUDE SENSOR LIBRARIES

// True Barometer implementation
class Barometer_True : public Barometer {
public:
    Barometer_True()
        :
        Barometer::Barometer()
    {
        // INITIALIZE
    }

    ~Barometer_True() override = default;

    void Read(FC_Data &data) override {
        // ACTUAL IMPLEMENTATION HERE
    }
private:
    // LIBRARY OBJECTS / OTHER MEMBER DATA
};

#endif // BAROMETER_TRUE_H