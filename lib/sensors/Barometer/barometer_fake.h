#ifndef BAROMETER_FAKE_H
#define BAROMETER_FAKE_H

#include "barometer.h"

// Custom Barometer implementation
class Barometer_Fake : public Barometer {
public:
    ~Barometer_Fake() override = default;

    void Read(FC_Data &data) override {
        // Our own, custom implementation here...

        data.baro_pres_raw = 0.0f;
        data.baro_temp_raw = 0.0f;
    }
private:
};

#endif // BAROMETER_FAKE_H