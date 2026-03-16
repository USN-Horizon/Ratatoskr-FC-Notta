#ifndef MOCKI2C_H
#define MOCKI2C_H

#include "I2Cinterface.h"

class MockI2C : public I2CInterface {
public:
    bool write(uint8_t addr, const uint8_t* data, size_t len) override {
        // pretend it always works
        return true;
    }

    bool read(uint8_t addr, uint8_t* data, size_t len) override {
        // fill with predictable dummy values
        for (size_t i = 0; i < len; i++) {
            data[i] = 0x10 + i;  // deterministic pattern
        }
        return true;
    }
};

#endif
