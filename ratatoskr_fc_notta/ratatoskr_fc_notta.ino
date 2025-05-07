#include "src/FC.h"

void setup() {
  Serial.begin(9600);
  
  FlightComputer fc;

  delay(2000);

  fc.LiftOff();
}

void loop() {
}
