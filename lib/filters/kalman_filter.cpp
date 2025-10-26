#include "kalman_filter.h"


/**
 * Update the filter state to the next discrete time iteration. Transforms the system state to the next
 * iteration based on measurements.
 * @param acc_x The acceleration in the x-axis measured in this discrete time iteration
 * @param acc_y The acceleration in the y-axis measured in this discrete time iteration
 * @param acc_z The acceleration in the z-axis measured in this discrete time iteration
 * @param barometric_height The height extrapolated from barometric measurement in this discrete time iteration
 */
void kalman_filter::filter_update(float acc_x, float acc_y,float acc_z, float barometric_height) {

    // === CALCULATION CONTEXT ===

    // the model used for the whole system is:
    // a_(t+delta_t) = a_t
    // v_(t+delta_t) = v_t + a_t * delta_t
    // s_(t+delta_t) = s_t + v_t * delta_t + a_t * ((delta_t^2)/2)

    // note: prev = (k-1)
    //system model: phi_k_prev transforms the system state at time k-1 to k
    // x_k = phi_prev * x_prev + sNoise_prev
    //measurement model: H_k transforms the system state into the measurement
    // z_k = H_k * x_k + mNoise

    // There are two steps to this process: predicting and correcting
    // - The prediction stage takes the previous state and nothing more, and tries
    // to predict the next state.
    // - The correction stage takes the prediction and corrects it using the new measurements
    // and their known standard deviation



    // === ACTUAL MATH ===

    // PREDICTION: finding a prediction of x based on previously known system state
    // xHat_(k_pred) = phi_prev * xHat_(prev_corr)
    // CORRECTION: tuning/correcting the predicted value using new measurements
    // xHat_(k_corr) = xHat_(k_pred) + KGain_k * (z_k - H_k * xHat_(k_pred))

    // these are the main functions, which is pretty OK to calculate... SIKE
    // the silly ass KGain_k is pretty complex. Luckily, the values converge, so they can
    // be calculated beforehand, making the real-time computation pretty light.

    // --- One iteration of k ---
    // First we need to establish the prediction of the error covariance, using previous corrected error covariance
    // P_(k_pred) = phi_prev * P_(prev_corr) * (phi_prev)^T + Q_prev

    // Then we correct the predicted value using the Kalman gain
    // P_(k_corr) = (I - KGain_k * H_k) * P_(k_pred)

    // The Kalman gain used above
    // KGain_k = P_(k_pred) * (H_k)^T * (H_k * P_(k_pred) * (H_k)^T + R_k)^-1

    // *WARNING HORN* you might notice that these are undefined by default, cause we need an
    // initial P_(k_pred), a.k.a P_(0_pred)
    // The initial Error covariance is a diagonal matrix, consisting of the variances for each state.
    // P_(0_pred) = σ² * I
    // In this case, we have one measurement leading to s (position: barometric measurement),
    // and another leading to a (accelerometer).

}


float kalman_filter::get_x() {
    return q_x; 
}

float kalman_filter::get_y() {
    return q_y; 
}

float kalman_filter::get_z() {
    return q_z; 
}
