#ifndef MAX_M10S_H
#define MAX_M10S_H

#include <stdint.h>

bool maxM10SInit();
void maxM10SUpdate();
double maxM10SGetLatitude();
double maxM10SGetLongitude();
double maxM10SGetAltitude();
uint8_t maxM10SGetSatellites();

#endif 
