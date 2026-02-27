#include <Arduino.h>
#include "imu_mock.h"  // Eller imu_ICM20948.h for ekte IMU
#include "fc_data.h"  

IMU_Mock imu;        // Opprett mock-objekt

void printVector3D(const Vector3D &vec, const char* name) {
    Serial.print(name);
    Serial.print(": ");
    Serial.print(vec.x); Serial.print(", ");
    Serial.print(vec.y); Serial.print(", ");
    Serial.println(vec.z);
}

void setup() {
    Serial.begin(115200);
    while(!Serial);
    Serial.println("Initalizing IMU Mock test...");
}

void loop() {
    FC_Data data;
    imu.Read(data);

    // Print raw IMU-data
    printVector3D(data.imu_acc_raw, "Acc");
    printVector3D(data.imu_ang_vel_raw, "Gyro");
    printVector3D(data.imu_mag_raw, "Mag");

    Serial.println("---------------------");
}


