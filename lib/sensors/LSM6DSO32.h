#pragma once
#include <Arduino.h>
#include <Adafruit_LSM6DSO32.h>
#include "sensorClass.h"

// Driver for LSM6DSO32 (gyro + akselerometer)
class LSM6DSO32Sensor : public Sensor {
private:
    Adafruit_LSM6DSO32 imu;
    sensors_event_t accel;
    sensors_event_t gyro;
    sensors_event_t temp;

public:
    LSM6DSO32Sensor(String n = "LSM6DSO32");

    bool setup() override;   // init sensor
    void update() override;  // les data

    // Ekstra metoder for å hente siste målinger
    sensors_event_t getAccel() const { return accel; }
    sensors_event_t getGyro() const { return gyro; }
    sensors_event_t getTemp() const { return temp; }

    void info() override;    // print status + sensordata
};
