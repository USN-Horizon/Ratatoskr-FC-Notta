// LoRaSensor.cpp
#include "SX1280.h"
#include <Arduino.h>

// constructor
LoRaSensor::LoRaSensor() 
    : Sensor("LoRa"), 
      radio(new Module(LORA_CS, LORA_DIO1, LORA_RST, LORA_BUSY)) 
{
}

bool LoRaSensor::setup() {
    Serial.println(F("[LoRa] Initialiserer …"));
    int state = radio.begin();
    if (state == RADIOLIB_ERR_NONE) {
        radio.setOutputPower(10);     // 0–13 dBm
        radio.setBandwidth(203000);   // Hz (200 kHz LoRa-båndbredde)
        radio.setSpreadingFactor(7);  // SF5 til SF12
        radio.setCodingRate(5);       // CR 5:4 til 8:4
        setReady(true);
        return true;
    } 
    Serial.print(F("[LoRa] Feil: "));
    Serial.println(state);
    setReady(false);
    return false;
}

// Update: Send data
void LoRaSensor::update() {
    if (!isReady()) return;

    int state = radio.transmit("Hei fra SX1280!");
    if (state == RADIOLIB_ERR_NONE) {
        Serial.println(F("[LoRa] Sendt OK!"));
    } else {
        Serial.print(F("[LoRa] Feil ved sending: "));
        Serial.println(state);
    }
}

// Info: Skriv status til Serial
void LoRaSensor::info() {
    Serial.println(F("[LoRa] SX1280 radio aktiv"));
}

