#include "imu_ICM20948.h"

IMU_ICM20948::IMU_ICM20948(TwoWire& wire, bool ad0_pin, String& name = "IMU (ICM20948)")
    :
    Sensor(name)
{
    icm.begin(wire, ad0_pin);

    if (icm.status != ICM_20948_Stat_Ok) {
        Serial.print("Could not initialise sensor ");
        Serial.print(Name());
        Serial.println(" on I2C.");
        Serial.print("\tError: ");
        Serial.println(icm.statusString());
        return;
    }

    good = true;
}

IMU_ICM20948::~IMU_ICM20948() = default;

void IMU_ICM20948::Read(FC_Data &data) {
    icm.getAGMT();

    data.imu_acc_raw = { icm.accX(), icm.accY(), icm.accZ() };
    data.imu_ang_vel_raw = { icm.gyrX(), icm.gyrY(), icm.gyrZ() };
    data.imu_mag_raw = { icm.magX(), icm.magY(), icm.magZ() };
}