#include "kalman_filter.h"


/**
 * Update the filter state to the next discrete time iteration. Transforms the system state to the next
 * iteration based on measurements.
 */
void KalmanFilter::filter_update(float s, float v, float a) {

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


    // === STEP 1: PREDICTION ===

    // Predict the state based on the system model
    // x_pred = phi * x_prev
    Eigen::Matrix<float, 3, 1> x_pred = phi * x;

    // Predict the error covariance
    // P_pred = phi * P_prev * phi^T + Q
    Eigen::Matrix<float, 3, 3> P_pred = phi * P * phi.transpose() + Q;


    // === STEP 2: CORRECTION ===

    // Create measurement vector z from sensor inputs
    // z = [s, a] (position from barometer, acceleration from accelerometer)
    // Note: velocity v is not directly measured, only estimated
    Eigen::Matrix<float, 2, 1> z;
    z << s, a;

    // Calculate the Kalman gain
    // K = P_pred * H^T * (H * P_pred * H^T + R)^-1
    Eigen::Matrix<float, 2, 2> S = H * P_pred * H.transpose() + R;  // Innovation covariance
    Eigen::Matrix<float, 3, 2> K = P_pred * H.transpose() * S.inverse();  // Kalman gain

    // Update the state estimate using the measurement
    // x_corr = x_pred + K * (z - H * x_pred)
    Eigen::Matrix<float, 2, 1> innovation = z - H * x_pred;  // Innovation (measurement residual)
    x = x_pred + K * innovation;

    // Update the error covariance
    // P_corr = (I - K * H) * P_pred
    P = (I - K * H) * P_pred;

}


float KalmanFilter::get_s() const {
    return x(0);  // position
}

float KalmanFilter::get_v() const {
    return x(1);  // speed
}

float KalmanFilter::get_a() const {
    return x(2);  // acceleration
}
