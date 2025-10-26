#pragma once
#include <cmath>
#include <Dense.h>
#define KALMAN_FILTER_H

class KalmanFilter
{
    private:
        // State vector: [s_x, s_y, s_z, v_x, v_y, v_z, a_x, a_y, a_z]
        Eigen::Matrix<float, 3, 1> x;

        float delta_t = 0.001f;
        float gyro_mesurement_error = 3.14159265358979f * (5.0f / 180.0f);
        float beta = sqrt(3.0f / 4.0f) * gyro_mesurement_error; 
    public:  
        KalmanFilter(
            float s, float v, float a
        )
        {
            // Initialize state vector with constructor arguments
            x << s, v, a;
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
        float get_s();
        float get_v();
        float get_a();
};
