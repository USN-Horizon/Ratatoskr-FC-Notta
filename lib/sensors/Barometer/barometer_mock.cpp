#include "barometer_mock.h"

Barometer_Mock::Barometer_Mock()
    :
    Sensor(F("Barometer (Mock)"))
{
    good = true;
}

Barometer_Mock::~Barometer_Mock() = default;

void Barometer_Mock::Read(FC_Data &data) {
    // Mock implementation
    return;
}


