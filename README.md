# Nøtta Flight Computer Firmware

A flight controller firmware for Teensy 4.1 using FreeRTOS with modular task-based architecture.

Further documentation can be found on the [USN Horizon Wiki](https://wiki.usnhorizon.no/en/project-ratatoskr/avionics).

## File Structure Format
```
Ratatoskr-FC-Notta/
|- src/                      <- header/implementation files
|  |- main.cpp               <- main entry point
|  |- tasks/                 <- task implementations
|  |  |- SomethingTask.h
|  |  |- SomethingTask.cpp
|- lib/                      <- project libraries
|  |- sensors/               <- sensor implementations
|- include/                  <- project configuration headers / other useful headers
|  |- pins.h
|  |- config.h
|- platformio.ini            <- PlatformIO configuration
```

## Build & Setup

 The easiest way to build and run this project is through the PlatformIO extension installed in either VSCode or CLion.
 Alternatively, use the instructions below.

### Prerequisites
- [PlatformIO](https://platformio.org/) installed
- Teensy CLI tools for uploading

### Building
```bash
# Build the project
pio run

# Upload to board
pio run --target upload

# Open serial monitor
pio device monitor
```