#include <Arduino.h>
#include "barometer_mock.h"  
#include "fc_data.h" 

Barometer_Mock baro;

void print(uint32_t value, const char* name){
    Serial.print(name);
    Serial.print(": ");
    Serial.print(value);
}

void setup(){
     Serial.begin(115200);
     while(!Serial);
     Serial.println("Initalizing Barometer Mock test...");
}

void loop(){
    FC_Data data;
    baro.Read(data);
    print(data.baro_pres_raw, "Psc");
}