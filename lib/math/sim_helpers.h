//
// Created by syvers on 02.11.2025.
//

#ifndef RATATOSKR_FC_NOTTA_SIM_HELPERS_H
#define RATATOSKR_FC_NOTTA_SIM_HELPERS_H

#include <iostream>
#include <cmath>
#include <iomanip>

/**
 * Calculate air density at a given altitude (0-10 km).
 *
 * @param altitude_m Altitude in kilometers (0-10)
 * @return Air density in kg/m³
 *
 * Uses the International Standard Atmosphere model for the troposphere. Used in simulating the environments for
 * the Kalman filter.
 */
double air_density(double altitude_m);

/**
 * Calculate air resistance at a given altitude (0-10 km).
 *
 * @param altitude_m Altitude in kilometers (0-10)
 * @param v Speed in acceleration direction
 * @param drag_coef Drag coefficient of rocket
 * @param drag_area Cross section area of rocket
 * @return Air resistance in newtons
 *
 * Uses the International Standard Atmosphere model for the troposphere. Used in simulating the environments for
 * the Kalman filter.
 */
double air_resistance(const double altitude_m, const double v, const double drag_coef, const double drag_area);

#endif //RATATOSKR_FC_NOTTA_SIM_HELPERS_H
