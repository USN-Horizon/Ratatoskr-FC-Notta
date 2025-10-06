#ifndef FC_DATA_H
#define FC_DATA_H

// Simple 3D vector type (xyz, without operators and methods)
// Could be nice to improve functionality for this type later
struct Vector3D {
    double x = 0.0, y = 0.0, z = 0.0;
};

// Simple temporary struct containing latitude (deg), longitude (deg) and altitude (mm)
struct GNSS_Position {
    double lat = 0.0, lon = 0.0, alt = 0.0;
};

// The different states the rocket can be in during its operation
enum class FlightState {
    NOT_READY,  // FC is not yet initialized
    ARMED,      // Rocket is ready to take off
    ASCENDING,  // Rocket is ascending
    APOGEE,     // Apogee reached, waiting for drouge to deploy
    DROUGE,     // Drouge chute is deployed
    MAIN,       // Main altitude reached, waiting for main chute to deploy
    POST_MAIN,  // Main chute is deployed
    GROUND      // Rocket has landed (hopefully in one piece)
};

// Configs and values sent to FC from GS over radio
struct FlightConfig {
    bool do_testing = false;

    // And other values...
};

struct FC_Data {
    // Raw sensor data
    Vector3D imu_acc_raw;       // Raw acceleration (m/s^2 (xyz)) (Sensor: IMU - accelerometer)
    Vector3D imu_ang_vel_raw;   // Raw angular velocity (deg/s (xyz)) (Sensor: IMU - gyroscope)
    Vector3D imu_mag_raw;       // Raw magnetic field (μTesla (xyz)) (Sensor: IMU - magnetometer)
    double baro_pres_raw = 0.0; // Raw barometric pressure (Pascal) (Sensor: Barometer)
    double baro_temp_raw = 0.0; // Raw barometric temperature (Celcius) (Sensor: Barometer)

    Vector3D acc_module_1_raw;  // Raw acceleration (m/s^2 (xyz)) (Sensor: IMU - accelerometer)
    Vector3D acc_module_2_raw;  // Raw acceleration (m/s^2 (xyz)) (Sensor: IMU - accelerometer)

    GNSS_Position gnss;         // GNSS data (deg, deg, mm) (Sensor: GNSS)

    // Processed data
    Vector3D pos;               // Estimated position (m) (xyz)
    Vector3D vel;               // Estimated velocity (m/s) (xyz)
    Vector3D att;               // Estimated attitude (deg) (ypr)

    // Other data
    FlightState flightstate = FlightState::NOT_READY;    // Current flight state
    FlightConfig flightconfigs; // Configs for flightcomputer sent over radio (eg. manual component testing mode)
};

#endif