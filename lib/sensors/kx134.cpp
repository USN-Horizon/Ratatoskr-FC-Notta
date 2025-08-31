#pragma once
#include "Sensor.h"
#include <SPI.h>

// SPI pin for CS (bh_CS2)
#define CS_PIN 6  

// Registeradresser
#define WHO_AM_I 0x13
#define CNTL1    0x1B
#define ODCNTL   0x21
#define INC1     0x1F
#define XOUT_L   0x08

class KX134Sensor : public Sensor {
public:
    // arver navnet og intervallet fra baseklassen
    KX134Sensor(unsigned long interval = 100) 
        : Sensor("KX134", interval) {}

    bool setup() override {
        pinMode(CS_PIN, OUTPUT);
        digitalWrite(CS_PIN, HIGH);
        SPI.begin();

        // Sjekk WHO_AM_I
        uint8_t id = readRegister(WHO_AM_I);
        if (id != 0x46) {
            Serial.print(F("[KX134] WHO_AM_I feil: 0x"));
            Serial.println(id, HEX);
            setReady(false);
            return false;
        }

        // Init-sekvens
        writeRegister(CNTL1, 0x00);  // Standby
        writeRegister(ODCNTL, 0x02); // 50 Hz
        writeRegister(CNTL1, 0xC0);  // Operating mode, High-res, ±8g
        writeRegister(INC1, 0x10);   // Burst read

        Serial.println(F("[KX134] Init OK"));
        setReady(true);
        return true;
    }

    void update() override {
        if (!isReady()) return;      // hopp over hvis ikke startet
        if (!shouldUpdate()) return; // sjekk intervallet

        int16_t x, y, z;
        readRaw(x, y, z);

        Serial.print("[KX134] X: "); Serial.print(x * 0.000244);
        Serial.print(" g, Y: ");     Serial.print(y * 0.000244);
        Serial.print(" g, Z: ");     Serial.print(z * 0.000244);
        Serial.println(" g");
    }

    void info() override {
        Serial.println(F("[KX134] Akselerometer aktiv (±8g, 50 Hz)"));
    }

private:
    uint8_t readRegister(uint8_t reg) {
        digitalWrite(CS_PIN, LOW);
        SPI.transfer(reg | 0x80);
        uint8_t val = SPI.transfer(0x00);
        digitalWrite(CS_PIN, HIGH);
        return val;
    }

    void writeRegister(uint8_t reg, uint8_t val) {
        digitalWrite(CS_PIN, LOW);
        SPI.transfer(reg & 0x7F);
        SPI.transfer(val);
        digitalWrite(CS_PIN, HIGH);
    }


    //Burst read er at du leser flere registerer etter hverandre i en sammenhengende operasjon
    void readRaw(int16_t &x, int16_t &y, int16_t &z) {
        uint8_t data[6]; //6 raa-byte, 2 bytes for x, y og z(LSB + MSB)
        digitalWrite(CS_PIN, LOW);
        SPI.transfer(XOUT_L | 0x80); // Start burst-read
        for (int i = 0; i < 6; i++) {
            data[i] = SPI.transfer(0x00);
        }
        digitalWrite(CS_PIN, HIGH);

        x = (int16_t)(data[1] << 8 | data[0]);
        y = (int16_t)(data[3] << 8 | data[2]);
        z = (int16_t)(data[5] << 8 | data[4]);
    }
};

