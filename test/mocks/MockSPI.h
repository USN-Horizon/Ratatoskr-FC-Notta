#ifndef MOCKSPI_H
#define MOCKSPI_H

#include "SPIInterface.h"

class MockSPI : public SPIInterface {
public:
    bool transfer(const uint8_t* txData, uint8_t* rxData, size_t len) override {
        // Fyll buffer med et forutsigbart mønster
        for (size_t i = 0; i < len; i++) {
            if (rxData) rxData[i] = 0xA0 + i;
        }
        return true;
    }
};

#endif

