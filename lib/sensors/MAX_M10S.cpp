#include "MAX_M10S.h"

MAXM10SSensor::MAXM10SSensor(unsigned long interval)
    : Sensor("MAX-M10S", interval) {}

bool MAXM10SSensor::setup() {
    Wire.begin();

    if (!myGNSS.begin()) {
        Serial.println(F("[MAX-M10S] Ikke funnet. Sjekk tilkoblingene."));
        setReady(false);
        return false;
    }

    Serial.println(F("[MAX-M10S] Startet via I2C!"));

    myGNSS.setI2COutput(COM_TYPE_UBX | COM_TYPE_NMEA); // UBX + NMEA meldinger
    myGNSS.setNavigationFrequency(1); // 1 Hz

    setReady(true);
    return true;
}

void MAXM10SSensor::update() {
    if (!isReady()) return;
    if (!shouldUpdate()) return;

    myGNSS.checkUblox(); // Henter ny data hvis tilgjengelig

    Serial.print(F("[MAX-M10S] Lat: ")); Serial.print(getLatitude(), 6);
    Serial.print(F(", Lon: "));          Serial.print(getLongitude(), 6);
    Serial.print(F(", Alt: "));          Serial.print(getAltitude());
    Serial.print(F(" m, Sats: "));       Serial.println(getSatellites());
}

void MAXM10SSensor::info() {
    Serial.println(F("[MAX-M10S] GNSS-modul aktiv (1 Hz)"));
}

double MAXM10SSensor::getLatitude() {
    return myGNSS.getLatitude() / 10000000.0;
}

double MAXM10SSensor::getLongitude() {
    return myGNSS.getLongitude() / 10000000.0;
}

double MAXM10SSensor::getAltitude() {
    return myGNSS.getAltitude() / 1000.0;
}

uint8_t MAXM10SSensor::getSatellites() {
    return myGNSS.getSIV();
}

