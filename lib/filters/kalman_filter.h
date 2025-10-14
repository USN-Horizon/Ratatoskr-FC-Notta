#pragma once
#include <cmath>
#define MADGWICK_FILTER_H

class kalman_filter
{
    private:
        float q_w{1.0};
        float q_x{0};
        float q_y{0}; 
        float q_z{0}; 

        float delta_t = 0.001f;
        float gyro_mesurement_error = 3.14159265358979f * (5.0f / 180.0f);
        float beta = sqrt(3.0f / 4.0f) * gyro_mesurement_error; 
    public:  
        kalman_filter(float quat_w,float quat_x, float quat_y, float quat_z)
        :q_w{quat_w},q_x{quat_x},q_y{quat_y},q_z{quat_z}
        {
        }

        // we might need to use the output of the madgwick filter to orient the forces onto the rocket.

        //this is the main function for the filter.
        // The inputs are the accelerometer, GPS, and barometer
        void filter_update(float acc_x, float acc_y,float acc_z,float gyro_x, float gyro_y, float gyro_z);

        /* Things to note!:
         * - GPS module might cut out at v>515m/s due to regulations to prevent it being used for military applications
         */


        // the goal is to get the estimate of the position (p_hat)
        //helper functions
        float get_x();
        float get_y();
        float get_z();
};
