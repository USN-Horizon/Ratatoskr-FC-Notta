#include "gnss_MAXM10S.h"

GNSS_MAXM10S::GNSS_MAXM10S(TwoWire& wire)
    :
    Sensor("GNSS (MAXM10S)")
{
    if (!gnss.begin(wire)) return;

    gnss.setI2COutput(COM_TYPE_UBX | COM_TYPE_NMEA); // UBX + NMEA messages
    gnss.setNavigationFrequency(1); // 1 Hz

    good = true;
}

GNSS_MAXM10S::~GNSS_MAXM10S() = default;

void GNSS_MAXM10S::Read(FC_Data &data) {
    gnss.checkUblox();

    data.gnss.alt = gnss.getAltitude() / 1000.0;
    data.gnss.lat = gnss.getLatitude() / 10000000.0;
    data.gnss.lon = gnss.getLongitude() / 10000000.0;
}

