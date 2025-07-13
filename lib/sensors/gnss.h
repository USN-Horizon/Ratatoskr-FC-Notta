#ifndef SENSOR_GNSS_H
#define SENSOR_GNSS_H

#include "sensor.h"

class GNSS : public Sensor_Base {
public:
    GNSS();

    bool Init() override;
    void ReadTo(FC_Data& fc_data) override;
    bool Available() override;
private:
};

#endif