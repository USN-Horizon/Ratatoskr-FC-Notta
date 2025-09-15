//Explenation so we know what this ACTUALLY MEANS:
//ADC stands for analog to digital converter
// OSR stands for oversampling ratio, this is for more accurate results and less interference
//Highest OSR is 4096 but converting takes 9ms

#include "MS5611.h"

// MS5611 Commands
#define CMD_RESET       0x1E
#define CMD_ADC_READ    0x00
#define CMD_CONV_D1     0x40  // Pressure
#define CMD_CONV_D2     0x50  // Temperature
#define CMD_ADC_256     0x00
#define CMD_ADC_512     0x02
#define CMD_ADC_1024    0x04
#define CMD_ADC_2048    0x06
#define CMD_ADC_4096    0x08
#define CMD_PROM_READ   0xA0  

MS5611::MS5611(String n) : Sensor(n), pressure(0), temperature(0) {}

// This part initalice I2C, reset sensor and read calibreation data
bool MS5611::setup() {
    Wire.begin();
    Wire.beginTransmission(MS5611_ADDR);
    if (Wire.endTransmission() != 0) {
        setReady(false);
        return false;
    }

    // Reset sensor
    Wire.beginTransmission(MS5611_ADDR);
    Wire.write(CMD_RESET);
    Wire.endTransmission();
    delay(3); // reset-tid

    if (!readPROM()) {
        setReady(false);
        return false;
    }

    setReady(true);
    return true;
}

// At this part we read pressure and temperature 
// with high resolution(This is to get it more accurate)
void MS5611::update() {
    if (!initialized) return;

    uint32_t D1 = 0, D2 = 0;

    // Start D1 conversion (Pressure)
    if (!startConversion(CMD_CONV_D1 | CMD_ADC_4096)) return;
    delay(10); // max 9.04ms for OSR=4096
    if (!readADC(D1, CMD_ADC_READ)) return;

    // Start D2 conversion (Temperature)
    if (!startConversion(CMD_CONV_D2 | CMD_ADC_4096)) return;
    delay(10);
    if (!readADC(D2, CMD_ADC_READ)) return;

    // Beregning av temperatur og trykk (enkel versjon)
    int32_t dT = D2 - ((uint32_t)C[5] << 8);
    temperature = 20.0 + dT * C[6] / 8388608.0;

    int64_t OFF = ((int64_t)C[2] << 16) + ((int64_t)C[4] * dT) / 128;
    int64_t SENS = ((int64_t)C[1] << 15) + ((int64_t)C[3] * dT) / 256;

    pressure = ((D1 * SENS / 2097152 - OFF) / 32768.0) / 100.0; // hPa
}

// This part print status, pressure and temperature
void MS5611::info() {
    Serial.print(F("[MS5611] "));
    Serial.print(name);
    if (initialized) {
        Serial.print(F(" OK | T="));
        Serial.print(temperature, 2);
        Serial.print(F("°C P="));
        Serial.print(pressure, 2);
        Serial.println(F(" hPa"));
    } else {
        Serial.println(F(" ikke initialisert"));
    }
}

bool MS5611::readPROM() {
    for (uint8_t i = 0; i < 7; i++) {
        Wire.beginTransmission(MS5611_ADDR);
        Wire.write(CMD_PROM_READ + i * 2);
        if (Wire.endTransmission() != 0) return false;

        Wire.requestFrom(MS5611_ADDR, (uint8_t)2);
        if (Wire.available() < 2) return false;

        C[i] = (Wire.read() << 8) | Wire.read();
    }
    return true;
}

/*-------  below here is more for communication in I2C ------- */

bool MS5611::startConversion(uint8_t cmd) {
    Wire.beginTransmission(MS5611_ADDR);
    Wire.write(cmd);
    return Wire.endTransmission() == 0;
}

bool MS5611::readADC(uint32_t &result, uint8_t cmd) {
    Wire.beginTransmission(MS5611_ADDR);
    Wire.write(cmd);
    if (Wire.endTransmission() != 0) return false;

    Wire.requestFrom(MS5611_ADDR, (uint8_t)3);
    if (Wire.available() < 3) return false;

    result = ((uint32_t)Wire.read() << 16) | ((uint32_t)Wire.read() << 8) | Wire.read();
    return true;
}
