#ifndef MOCKSPI_H
#define MOCKSPI_H

#include "SPIInterface.h"

class MockSPI : public SPIInterface {
public:
    bool transfer(const uint8_t* tx, uint8_t* rx, size_t len) override {
        // simple fake: invert bits of tx into rx
        for (size_t i = 0; i < len; i++) {
            rx[i] = tx[i] ^ 0xFF;
        }
        return true;
    }
};

#endif
