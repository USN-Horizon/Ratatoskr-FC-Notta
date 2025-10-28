#pragma once
#include <Arduino.h>

class Sensor {
protected:
    String name;          
    bool initialized;     
    unsigned long intervalMs;
    unsigned long _lastUpdate;

public:
    Sensor(const String &n = "Sensor", unsigned long interval = 1000) 
        : name(n), initialized(false), intervalMs(interval), _lastUpdate(0) {}
    virtual ~Sensor() {}

    virtual bool setup() = 0;    // start/initialiser 
    virtual void update() = 0;   // les data / send data

    // Felles
    virtual void info() {
        Serial.print(F("[Sensor] ")); 
        Serial.print(name);
        Serial.println(initialized ? F(" OK") : F(" ikke initialisert"));
    }

    bool isReady() const { return initialized; }
    String getName() const { return name; }
    unsigned long getInterval() const { return intervalMs; }
    void setInterval(unsigned long ms) { intervalMs = ms; }

    bool shouldUpdate() {
        unsigned long now = millis();
        if (now - _lastUpdate >= intervalMs) {
            _lastUpdate = now;
            return true;
        }
        return false;
    }

protected:
    // For avledede klasser → kan kalles inni setup()
    void setReady(bool ok) { initialized = ok; }
};
