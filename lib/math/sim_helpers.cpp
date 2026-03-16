//
// Created by syvers on 02.11.2025.
//

#include "sim_helpers.h"

double air_density(const double altitude_m) {
    // Constants
    constexpr double T0 = 288.15;   // Sea level standard temperature (K)
    constexpr double P0 = 101325;   // Sea level standard pressure (Pa)
    constexpr double rho0 = 1.225;  // Sea level standard density (kg/m³)
    constexpr double L = -0.0065;   // Temperature lapse rate (K/m)
    constexpr double R = 287.05;    // Specific gas constant for air (J/(kg·K))
    constexpr double g = 9.80665;   // Gravitational acceleration (m/s²)

    // Convert altitude to meters
    const double h = altitude_m;

    // Calculate temperature at altitude
    const double T = T0 + L * h;

    // Calculate density using barometric formula
    const double rho = rho0 * std::pow(T / T0, -(g / (L * R) + 1));

    return rho;
}

double air_resistance(const double altitude, const double v, const double drag_coef, const double drag_area) {
    return 0.5 * air_density(altitude) * v * v * drag_coef * drag_area;
}