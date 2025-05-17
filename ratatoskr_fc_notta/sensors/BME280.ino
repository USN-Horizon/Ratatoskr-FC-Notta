//Simple code                                   
//Libary for BME280 (Barometer)         
#include "Adafruit_Sensor.h
#include "Adafruit_BME280.h"

Adafruit_BME280 bme; // create a BME280 sensor object

//If it is not the right adress then the code will stop, else it will execute the loop
void setup() {
    Serial.begin(9600);
    if (!bme.begin(0x77)) {  // Should be standard I2C-adresse for BME280
        Serial.println("Kunne ikke finne BME280-sensoren!");
        while (1);
    }
}

void loop() {
    Serial.print("Trykk: ");
    Serial.print(bme.readPressure() / 100.0F); // From Pascal to hPa
    Serial.println(" hPa");
    delay(1000);
}




