#pragma once
#include <cmath>
#include <Dense.h>
#define KALMAN_FILTER_H

class KalmanFilter
{
    private:
        // State vector: [s, v, a] (position, velocity, acceleration)
        Eigen::Matrix<float, 3, 1> x;

        // State transition matrix (transforms state from time k-1 to k)
        Eigen::Matrix<float, 3, 3> phi;

        // Measurement matrix (transforms state to measurement space)
        // Measures position (barometer) and acceleration (accelerometer)
        Eigen::Matrix<float, 2, 3> H;

        // Error covariance matrix
        Eigen::Matrix<float, 3, 3> P;

        // Process noise covariance matrix
        Eigen::Matrix<float, 3, 3> Q;

        // Measurement noise covariance matrix
        Eigen::Matrix<float, 2, 2> R;

        // Identity matrix (for calculations)
        Eigen::Matrix<float, 3, 3> I = Eigen::Matrix<float, 3, 3>::Identity();

        float gyro_mesurement_error = M_PI * (5.0f / 180.0f);
        float beta = sqrt(3.0f / 4.0f) * gyro_mesurement_error; 
    public:  
        KalmanFilter(
            float s, float v, float a
        )
        {
            // Initialize state vector with constructor arguments
            x << s, v, a;

            // Initialize state transition matrix phi as identity
            // Will be updated dynamically in filter_update() based on actual dt (top right part needs changing)
            phi = Eigen::Matrix<float, 3, 3>::Identity();

            // Initialize measurement matrix H
            // Row 1: measures position (barometer)
            // Row 2: measures acceleration (accelerometer)
            H << 1, 0, 0,
                 0, 0, 1;

            // Initialize error covariance matrix P_0 (initial uncertainty)
            // Diagonal matrix with initial variances for [s, v, a]
            P << 10.0f, 0,     0,
                 0,     5.0f,  0,
                 0,     0,     2.0f;

            // Initialize process noise covariance Q
            // Represents uncertainty in the process model (changing thrust, air resistance, etc.)
            // Higher values = less trust in model, more trust in measurements
            Q << 0.5f, 0,     0,
                 0,    0.5f,  0,
                 0,    0,     1.0f;

            // Initialize measurement noise covariance R
            // Diagonal: [position_variance, acceleration_variance]
            // Based on sensor specs: MS5611 barometer (σ=0.1m), LSM6DSO32 accel (σ=0.053m/s² squared)
            R << 0.01f,   0,
                 0,       0.0028f;
        }

        // we might need to use the output of the madgwick filter to orient the forces onto the rocket.
        // See f.eks. http://davesrocketworks.com/rockets/rnd/2004/KalmanApogeeII.pdf - Non Vertical Flight
        // Update: we might not. the sensor fusion works well enough to counteract this

        // the paper does a great job at describing the math we need! I'll base my code upon that paper,
        // but will be using the math library Eigen, to make the code more readable for
        // future coders (and myself :) )
        // Performance impact of using Eigen should be minimal, and with the info below, we should well
        // within our speed requirements.

        // So we want a linear data set and a constant acceleration. Otherwise the maths are too hard.
        // Paper says he got it to run well at only 4MHz (!). We have 600MHz, meaning we use 0.66% of the
        // clock capacity (very rough estimation ofc, but beyond promising)

        //


        //this is the main function for the filter.
        // The inputs are the accelerometer and barometer, plus the time step
        // @param s: measured position (from barometer)
        // @param a: measured acceleration (from accelerometer)
        // @param delta_t: time step since last update (seconds)
        // Note: velocity v is not currently used as we don't have a direct measurement
        void filter_update(float s, float a, float delta_t);

        /* Things to note!:
         * - GPS module might cut out at v>515m/s due to regulations to prevent it being used for military applications
         */


        // the goal is to get the estimate of the position (p_hat)
        //helper functions
        [[nodiscard]] float get_s() const;
        [[nodiscard]] float get_v() const;
        [[nodiscard]] float get_a() const;
};
