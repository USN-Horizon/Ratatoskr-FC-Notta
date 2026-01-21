#include "sensor.h"

Sensor::Sensor(const String &name)
    :
    name(name)
{}

bool Sensor::Good() const {
    return good;
}

const String& Sensor::Name() const {
    return name;
}

void Sensor::PrintStatus() const {
    Serial.print("Sensor: \"");
    Serial.print(Name());
    Serial.print("\", status: ");

    if (good) {
        Serial.print("Operational");
    }
    else {
        Serial.print("Inoperative");
    }

    Serial.println();
}


