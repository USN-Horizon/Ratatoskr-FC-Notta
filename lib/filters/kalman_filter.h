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

        float delta_t = 0.001f;
        float gyro_mesurement_error = M_PI * (5.0f / 180.0f);
        float beta = sqrt(3.0f / 4.0f) * gyro_mesurement_error; 
    public:  
        KalmanFilter(
            float s, float v, float a
        )
        {
            // Initialize state vector with constructor arguments
            x << s, v, a;

            // Initialize state transition matrix phi based on kinematic equations:
            // s_(t+dt) = s_t + v_t*dt + a_t*(dt^2)/2
            // v_(t+dt) = v_t + a_t*dt
            // a_(t+dt) = a_t
            phi << 1, delta_t, (delta_t * delta_t) / 2.0f,
                   0, 1,       delta_t,
                   0, 0,       1;

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
            // Represents uncertainty in the process model
            // These values should be tuned based on system characteristics
            Q << 0.1f, 0,     0,
                 0,    0.1f,  0,
                 0,    0,     0.1f;

            // Initialize measurement noise covariance R
            // Diagonal: [position_variance, acceleration_variance]
            // These values should be tuned based on sensor characteristics
            R << 1.0f, 0,
                 0,    0.5f;
        }

        // we might need to use the output of the madgwick filter to orient the forces onto the rocket.
        // See f.eks. http://davesrocketworks.com/rockets/rnd/2004/KalmanApogeeII.pdf - Non Vertical Flight

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
        // The inputs are the accelerometer and barometer
        void filter_update(float s, float v, float a);

        /* Things to note!:
         * - GPS module might cut out at v>515m/s due to regulations to prevent it being used for military applications
         */


        // the goal is to get the estimate of the position (p_hat)
        //helper functions
        [[nodiscard]] float get_s() const;
        [[nodiscard]] float get_v() const;
        [[nodiscard]] float get_a() const;
};
