#ifndef KX134_H
#define KX134_H

#include <Arduino.h>

bool kx134Init();
void kx134ReadRaw(int16_t &x, int16_t &y, int16_t &z);
void kx134PrintXYZ();

#endif
