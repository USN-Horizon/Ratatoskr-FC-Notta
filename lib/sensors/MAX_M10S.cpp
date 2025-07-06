#include "MAX_M10S.h"
#include <Wire.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

// Lager et objekt av GNSS-klassen fra SparkFun-biblioteket
SFE_UBLOX_GNSS myGNSS;

bool maxM10SInit() {
  Wire.begin(); // Starter I2C-bussen

  if (!myGNSS.begin()) {
    Serial.println("MAX-M10S ikke funnet. Sjekk tilkoblingene.");
    return false;
  }

  Serial.println("MAX-M10S startet via I2C!");

  // Aktiver både UBX (binær) og NMEA (tekst) meldinger
  myGNSS.setI2COutput(COM_TYPE_UBX | COM_TYPE_NMEA);

  // Sett posisjonsoppdatering til 1 Hz (en gang i sekundet)
  myGNSS.setNavigationFrequency(1);

  return true;
}

void maxM10SUpdate() {
  myGNSS.checkUblox(); // Leser ny data hvis tilgjengelig
}

//Returnerer siste kjente breddegrad i desimalgrader.
double maxM10SGetLatitude() {
  return myGNSS.getLatitude() / 10000000.0;
}

//Returnerer siste kjente lengdegrad i desimalgrader.
double maxM10SGetLongitude() {
  return myGNSS.getLongitude() / 10000000.0;
}

//Returnerer høyde over havet i meter.
double maxM10SGetAltitude() {
  return myGNSS.getAltitude() / 1000.0;
}

//Returnerer antall satellitter i visning.
uint8_t maxM10SGetSatellites() {
  return myGNSS.getSIV();
}

