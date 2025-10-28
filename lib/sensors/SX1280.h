#pragma once
#include "sensorClass.h"
#include <RadioLib.h>

// Pins for SX1280 LoRa
#define LORA_CS    10  // Chip select
#define LORA_DIO1   2  // Interrupt handling
#define LORA_RST    9  // Reset
#define LORA_BUSY   7  // Busy/idle signal

class LoRaSensor : public Sensor {
private:
    SX1280 radio;

public:
    // constructor
    LoRaSensor();

    bool setup() override;
    void update() override;
    void info() override;
};

