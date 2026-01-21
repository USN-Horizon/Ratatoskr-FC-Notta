#ifndef GNSS_MAXM10S_H
#define GNSS_MAXM10S_H

#include "sensor.h"
#include <Wire.h>
#include <SparkFun_u-blox_GNSS_v3.h>

class GNSS_MAXM10S : public Sensor {
public:
    GNSS_MAXM10S(TwoWire& wire);
    ~GNSS_MAXM10S() override;

    void Read(FC_Data& data) override;

private:
    SFE_UBLOX_GNSS gnss;
};

#endif // GNSS_MAXM10S_H