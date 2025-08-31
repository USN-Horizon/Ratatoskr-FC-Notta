// Sensor.h
#pragma once
#include <Arduino.h>

class Sensor {
protected:
    String name;          // navn (for logging/debug)
    bool initialized;     // status (init OK eller ikke)

public:
    Sensor(String n = "Sensor") : name(n), initialized(false) {}
    virtual ~Sensor() {}

    // Må implementeres av alle
    virtual bool setup() = 0;    // start/initialiser 
    virtual void update() = 0;   // les data / send data

    // Felles
    virtual void info() {
        Serial.print(F("[Sensor] ")); 
        Serial.print(name);
        Serial.println(initialized ? F(" OK") : F(" ikke initialisert"));
    }

    // Nyttige fellesmetoder
    bool isReady() const { return initialized; }
    String getName() const { return name; }

protected:
    // For avledede klasser → kan kalles inni setup()
    void setReady(bool ok) { initialized = ok; }
};
