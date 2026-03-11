#ifndef BARO_MOCK_H
#define BARO_MOCK_H

#include "sensor.h"

class Barometer_Mock : public Sensor {
public:
    Barometer_Mock();
    ~Barometer_Mock() override;

    void Read(FC_Data& data) override;
};

#endif // BARO_MOCK_H