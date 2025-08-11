#include "madgwick_filter.h"



void madgwick_filter::filter_update(float acc_x, float acc_y,float acc_z,float gyro_x, float gyro_y, float gyro_z)
{
    //local vars
    float norm; //for vector normalization

    float q_dot_omega_w;
    float q_dot_omega_x; 
    float q_dot_omega_y; 
    float q_dot_omega_z;

    float f_1; 
    float f_2; 
    float f_3; 

    float J_11or24; 
    float J_12_23; 
    float J_13_22; 
    float J_14or21;
    float J_32; 
    float J_33; 

    float q_hat_dot_w;
    float q_hat_dot_x;
    float q_hat_dot_y;
    float q_hat_dot_z;


    float half_q_w = 0.5 * q_w; 
    float half_q_x = 0.5 * q_x; 
    float half_q_y = 0.5 * q_y; 
    float half_q_z = 0.5 * q_z; 

    float two_q_w  = 2.0* q_w;
    float two_q_x  = 2.0* q_w;
    float two_q_y  = 2.0* q_w;

    //normalize  the accelometer

    norm = sqrt(acc_x*acc_x + acc_y*acc_y + acc_z*acc_z); 
    acc_x /= norm; 
    acc_y /= norm; 
    acc_z /= norm; 
    //compute the objective function and Jacobian
    f_1 = two_q_x * q_z - two_q_w * q_y - acc_x;
    f_2 = two_q_w * q_x + two_q_y * q_z - acc_y; 
    f_3 = 1.0 - two_q_x * q_x - two_q_y * q_y - acc_z; 

    J_11or24 = two_q_y; 
    J_12_23 = 2.0*q_z; 
    J_13_22 = two_q_w;
    J_14or21 = two_q_x; 
    J_32 = 2.0 * J_14or21;
    J_33 = 2.0 * J_11or24; 

    //compute the gradient(matrix multiplication)

    q_hat_dot_w = J_14or21 * f_2 - J_11or24 * f_1; 
    q_hat_dot_x = J_12_23 * f_1 + J_13_22 * f_2 - J_32 * f_3; 
    q_hat_dot_y = J_12_23 * f_2 - J_33 * f_3 - J_13_22 * f_1;
    q_hat_dot_z = J_14or21 * f_1 + J_14or21 * f_2;  


    norm = sqrt(q_hat_dot_w*q_hat_dot_w + q_hat_dot_x*q_hat_dot_x + q_hat_dot_y*q_hat_dot_y + q_hat_dot_z*q_hat_dot_z );
    q_hat_dot_w /= norm; 
    q_hat_dot_x /= norm; 
    q_hat_dot_y /= norm; 
    q_hat_dot_z /= norm; 

    q_dot_omega_w = -half_q_x * gyro_x - half_q_y * gyro_y - half_q_z * gyro_z; 
    q_dot_omega_x = half_q_w * gyro_x + half_q_y * gyro_z - half_q_z * gyro_y; 
    q_dot_omega_y = half_q_w * gyro_y - half_q_x * gyro_z + half_q_z * gyro_x; 
    q_dot_omega_z = half_q_w * gyro_z + half_q_x * gyro_y - half_q_y * gyro_x;

    q_w += (q_dot_omega_w -(beta*q_hat_dot_w)) * delta_t; 
    q_x += (q_dot_omega_x -(beta*q_hat_dot_x)) * delta_t; 
    q_y += (q_dot_omega_y -(beta*q_hat_dot_y)) * delta_t; 
    q_z += (q_dot_omega_z -(beta*q_hat_dot_z)) * delta_t; 

    norm = sqrt(q_w*q_w + q_x*q_x + q_y*q_y + q_z*q_z);
    q_w /= norm; 
    q_x /= norm; 
    q_y /= norm; 
    q_z /= norm;   
}



float madgwick_filter::get_w()
{
    return q_w; 
}

float madgwick_filter::get_x()
{
    return q_x; 
}

float madgwick_filter::get_y()
{
    return q_y; 
}

float madgwick_filter::get_z()
{
    return q_z; 
}
