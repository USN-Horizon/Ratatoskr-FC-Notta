//For LoRa – SX 128


#include <RadioLib.h>
// SPI pin definitions for your board (ESP32/STM32/Arduino)
#define LORA_CS    10 //chip select
#define LORA_DIO1   2 //interrupthaandtering
#define LORA_RST    9 //reset
#define LORA_BUSY   7 //opptatt/ledig-signal

SX1280 radio = new Module(LORA_CS, LORA_DIO1, LORA_RST, LORA_BUSY);
void setup() {
  Serial.begin(115200);
  while (!Serial);
  // Start radio
  Serial.print(F("[SX1280] Initialiserer … "));
  int state = radio.begin();
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("Startet OK!"));
  } else {
    Serial.print(F("Feil start: "));
    Serial.println(state);
    while (true);
  }
  // Sett overføringsparametre
  radio.setOutputPower(10);            // 0–13 dBm
  radio.setBandwidth(203000);          // Hz (200 kHz LoRa-båndbredde)
  radio.setSpreadingFactor(7);         // SF5 til SF12
  radio.setCodingRate(5);              // CR 5:4 til 8:4
}
void loop() {
  Serial.print(F("[SX1280] Sender melding … "));
  int state = radio.transmit("Hei fra SX1280!");
  if (state == RADIOLIB_ERR_NONE) {
    Serial.println(F("Sendt OK!"));
  } else {
    Serial.print(F("Feil ved sending: "));
    Serial.println(state);
  }
  delay(5000);  // vent før neste sending
}
