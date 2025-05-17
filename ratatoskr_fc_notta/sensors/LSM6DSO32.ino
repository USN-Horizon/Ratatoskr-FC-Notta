#include <Wire.h>
#include <Arduino_LSM6DSO32.h>

//får tak i dette fra karnugh-filter.ino filen
extern void karnaugh_filter(float ax, float ay, float az, float gx, float gy, float gz);

void setup() {
    Serial.begin(115200);
    while (!Serial);  // Vent til seriell monitor er klar

    if (!IMU.begin()) {
        Serial.println("Kunne ikke finne LSM6DSO32-sensor!");
        while (1);
    }

    Serial.println("LSM6DSO32 funnet!");
}

void loop() {
    float ax, ay, az; // Akselerometerverdier
    float gx, gy, gz; // Gyroskopverdier

    if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
        IMU.readAcceleration(ax, ay, az);
        IMU.readGyroscope(gx, gy, gz);

        Serial.print("Akselerasjon (g): ");
        Serial.print(ax); Serial.print(", ");
        Serial.print(ay); Serial.print(", ");
        Serial.println(az);

        Serial.print("Gyroskop (dps): "); // dps - degree per second
        Serial.print(gx); Serial.print(", ");
        Serial.print(gy); Serial.print(", ");
        Serial.println(gz);
   
        Serial.println("-----------------------");

        karnaugh_filter(ax, ay, az, gx, gy, gz); //Tenker at denne funksjonen er fra annen ino-fil
    }
    
    delay(500); // Vent 500ms før neste maaling
}
