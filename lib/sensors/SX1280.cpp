//For LoRa - SX1280
#include "Sensor.h"
#include <RadioLib.h>

#define LORA_CS    10  //chip select
#define LORA_DIO1   2  //interrupthaandtering
#define LORA_RST    9  //reset
#define LORA_BUSY   7  //opptatt/ledig-signal

class LoRaSensor : public Sensor {
private:
    SX1280 radio;

public:
    LoRaSensor() : Sensor("LoRa"), radio(new Module(LORA_CS, LORA_DIO1, LORA_RST, LORA_BUSY)) {}

    bool setup() override {
        // Start radio
        Serial.println(F("[LoRa] Initialiserer …"));
        int state = radio.begin();
        if (state == RADIOLIB_ERR_NONE) {
            radio.setOutputPower(10);    // 0–13 dBm
            radio.setBandwidth(203000);  // Hz (200 kHz LoRa-båndbredde)
            radio.setSpreadingFactor(7); // SF5 til SF12
            radio.setCodingRate(5);      // CR 5:4 til 8:4
            setReady(true);
            return true;
        }
        Serial.print(F("[LoRa] Feil: ")); Serial.println(state);
        setReady(false);
        return false;
    }

    void update() override {
        if (!isReady()) return;
        int state = radio.transmit("Hei fra SX1280!");
        if (state == RADIOLIB_ERR_NONE) {
            Serial.println(F("[LoRa] Sendt OK!"));
        } else {
            Serial.print(F("[LoRa] Feil ved sending: "));
            Serial.println(state);
        }
    }

    void info() override {
        Serial.println(F("[LoRa] SX1280 radio aktiv"));
    }
};
