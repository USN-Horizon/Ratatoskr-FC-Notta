#ifndef GNSS_MOCK_H
#define GNSS_MOCK_H

#include "sensor.h"

class GNSS_Mock : public Sensor {
public:
    GNSS_Mock();
    ~GNSS_Mock() override;

    void Read(FC_Data& data) override;
};

#endif // GNSS_MOCK_H