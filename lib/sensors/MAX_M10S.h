#ifndef MAX_M10S_H
#define MAX_M10S_H

#include <Arduino.h>
#include <Wire.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include "sensorClass.h"

class MAXM10SSensor : public Sensor {
public:
    MAXM10SSensor(unsigned long interval = 1000); // default 1 Hz oppdatering

    bool setup() override;
    void update() override;
    void info() override;

    double getLatitude();
    double getLongitude();
    double getAltitude();
    uint8_t getSatellites();

private:
    SFE_UBLOX_GNSS myGNSS;
};

#endif
