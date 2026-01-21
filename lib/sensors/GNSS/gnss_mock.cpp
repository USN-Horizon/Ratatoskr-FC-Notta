#include "gnss_mock.h"

GNSS_Mock::GNSS_Mock()
    :
    Sensor(F("GNSS (Mock)"))
{
    good = true;
}

GNSS_Mock::~GNSS_Mock() = default;

void GNSS_Mock::Read(FC_Data &data) {
    // Mock implementation
    return;
}