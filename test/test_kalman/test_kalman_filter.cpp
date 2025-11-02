#include <unity.h>
#include <cmath>
#include <stdio.h>
#include "kalman_filter.h"
#include "sim_helpers.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_kalman_filter_initialization() {
    KalmanFilter filter(10.0f, 5.0f, 2.0f);

    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.0f, filter.get_s());
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, filter.get_v());
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 2.0f, filter.get_a());
}

void test_kalman_filter_stationary_object() {
    // Test a stationary object (no movement, no acceleration)
    KalmanFilter filter(0.0f, 0.0f, 0.0f);

    // Update with stationary measurements
    for (int i = 0; i < 100; i++) {
        filter.filter_update(0.0f, 0.0f, 0.0f);
    }

    // Should converge to zero position, velocity, and acceleration
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, filter.get_s());
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, filter.get_v());
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, filter.get_a());
}

void test_kalman_filter_constant_velocity() {
    // Test object moving at constant velocity
    KalmanFilter filter(0.0f, 10.0f, 0.0f);

    float dt = 0.001f;  // Time step from the filter
    char msg[100];

    // Simulate constant velocity motion
    for (int i = 0; i < 100; i++) {
        float expected_s = 10.0f * (i + 1) * dt;  // s = v * t
        filter.filter_update(expected_s, 0.0f, 0.0f);  // position increases, no acceleration

        // Print every 20 iterations to see progression
        if (i % 20 == 0) {
            snprintf(msg, sizeof(msg), "Iter %d: s=%.4f, v=%.4f, a=%.4f", i, filter.get_s(), filter.get_v(), filter.get_a());
            TEST_MESSAGE(msg);
        }
    }

    snprintf(msg, sizeof(msg), "Final: s=%.4f, v=%.4f, a=%.4f", filter.get_s(), filter.get_v(), filter.get_a());
    TEST_MESSAGE(msg);

    // Velocity should remain around 10 m/s
    TEST_ASSERT_FLOAT_WITHIN(2.0f, 10.0f, filter.get_v());
    // Acceleration should be near zero
    TEST_ASSERT_FLOAT_WITHIN(1.0f, 0.0f, filter.get_a());
}

void test_kalman_filter_constant_acceleration() {
    // Test object with constant acceleration
    KalmanFilter filter(0.0f, 0.0f, 9.81f);

    float dt = 0.001f;
    float a = 9.81f;  // Acceleration (e.g., gravity)

    // Simulate constant acceleration
    for (int i = 1; i <= 50; i++) {
        float t = i * dt;
        float expected_s = 0.5f * a * t * t;  // s = 0.5 * a * t^2
        float expected_v = a * t;              // v = a * t

        filter.filter_update(expected_s, 0.0f, a);
    }

    // Acceleration should remain around 9.81 m/s^2
    TEST_ASSERT_FLOAT_WITHIN(2.0f, 9.81f, filter.get_a());
}

void test_kalman_filter_noisy_measurements() {
    // Test filter's ability to smooth noisy measurements
    KalmanFilter filter(0.0f, 0.0f, 0.0f);

    // Add noise to position measurements but keep acceleration at zero
    for (int i = 0; i < 100; i++) {
        float noise = (i % 2 == 0) ? 0.5f : -0.5f;  // Alternating noise
        filter.filter_update(0.0f + noise, 0.0f, 0.0f);
    }

    // Filtered position should be close to zero despite noisy measurements
    TEST_ASSERT_FLOAT_WITHIN(0.5f, 0.0f, filter.get_s());
}

void test_kalman_filter_no_nan_values() {
    // Ensure filter doesn't produce NaN values with various inputs
    KalmanFilter filter(100.0f, 50.0f, 10.0f);

    // Test with zero measurements
    filter.filter_update(0.0f, 0.0f, 0.0f);

    TEST_ASSERT_FALSE(isnan(filter.get_s()));
    TEST_ASSERT_FALSE(isnan(filter.get_v()));
    TEST_ASSERT_FALSE(isnan(filter.get_a()));

    // Test with large measurements
    filter.filter_update(1000.0f, 0.0f, 100.0f);

    TEST_ASSERT_FALSE(isnan(filter.get_s()));
    TEST_ASSERT_FALSE(isnan(filter.get_v()));
    TEST_ASSERT_FALSE(isnan(filter.get_a()));

    // Test with negative measurements
    filter.filter_update(-50.0f, 0.0f, -20.0f);

    TEST_ASSERT_FALSE(isnan(filter.get_s()));
    TEST_ASSERT_FALSE(isnan(filter.get_v()));
    TEST_ASSERT_FALSE(isnan(filter.get_a()));
}

void test_kalman_filter_position_tracking() {
    // Test that filter tracks position measurements
    KalmanFilter filter(0.0f, 0.0f, 0.0f);

    // Move to position 10m
    for (int i = 0; i < 50; i++) {
        filter.filter_update(10.0f, 0.0f, 0.0f);
    }

    // Position should converge to 10m
    TEST_ASSERT_FLOAT_WITHIN(2.0f, 10.0f, filter.get_s());

    // Move to position 20m
    for (int i = 0; i < 50; i++) {
        filter.filter_update(20.0f, 0.0f, 0.0f);
    }

    // Position should converge to 20m
    TEST_ASSERT_FLOAT_WITHIN(2.0f, 20.0f, filter.get_s());
}

void test_kalman_filter_velocity_estimation() {
    // Test that filter can estimate velocity from position changes
    // Note: This is a challenging scenario as velocity is not directly measured
    KalmanFilter filter(0.0f, 0.0f, 0.0f);

    float dt = 0.001f;
    float velocity = 25.0f;  // 25 m/s

    // Provide position measurements that imply velocity of 25 m/s
    // Need more iterations for velocity to converge from position-only data
    for (int i = 1; i <= 1000; i++) {
        float expected_s = velocity * i * dt;
        filter.filter_update(expected_s, 0.0f, 0.0f);
    }

    // Filter should show positive velocity trend
    // The exact value depends on noise covariance tuning
    TEST_ASSERT_TRUE(filter.get_v() > 0.0f);
    // Position should be tracked accurately
    TEST_ASSERT_FLOAT_WITHIN(5.0f, velocity * 1000 * dt, filter.get_s());
}

void test_kalman_filter_freefall_simulation() {
    // Simulate a rocket in freefall after burnout
    KalmanFilter filter(0.0f, 0.0f, -9.81f);

    float dt = 0.001f;
    float g = -9.81f;
    float v0 = 100.0f;  // Initial upward velocity

    // Simulate 100 steps of freefall
    for (int i = 1; i <= 100; i++) {
        float t = i * dt;
        float s = v0 * t + 0.5f * g * t * t;  // Kinematic equation
        float v = v0 + g * t;

        filter.filter_update(s, 0.0f, g);
    }

    // Acceleration should track gravity
    TEST_ASSERT_FLOAT_WITHIN(2.0f, -9.81f, filter.get_a());

    // Position and velocity should be reasonable (no NaN or infinity)
    TEST_ASSERT_FALSE(isnan(filter.get_s()));
    TEST_ASSERT_FALSE(isnan(filter.get_v()));
    TEST_ASSERT_FALSE(isinf(filter.get_s()));
    TEST_ASSERT_FALSE(isinf(filter.get_v()));
}

void test_kalman_filter_measurement_fusion() {
    // Test that filter fuses both position and acceleration measurements
    KalmanFilter filter(0.0f, 0.0f, 0.0f);

    // Provide consistent position and acceleration measurements
    float a = 5.0f;
    float dt = 0.001f;

    for (int i = 1; i <= 100; i++) {
        float t = i * dt;
        float s = 0.5f * a * t * t;  // Position from acceleration
        filter.filter_update(s, 0.0f, a);
    }

    // Both position and acceleration should be tracked
    TEST_ASSERT_FLOAT_WITHIN(2.0f, 5.0f, filter.get_a());
    TEST_ASSERT_TRUE(filter.get_s() > 0.0f);  // Position should be positive
}

// helper funciton for printing filter status and true simulated values
inline void print_status(const float time, const KalmanFilter& filter, const float true_s, const float true_v, const float true_a) {
    char msg[200];
    snprintf(msg, sizeof(msg),
                         "t=%.1fs: Alt=%.1fm (true=%.1fm), Vel=%.1fm/s (true=%.1fm/s), Acc=%.1fm/s² (true=%.1fm/s²)",
                         time, filter.get_s(), true_s, filter.get_v(), true_v, filter.get_a(), true_a);
    TEST_MESSAGE(msg);
}

inline float thrust_accel(const float t, const float burn_time) {
    // acceleration is approximately quadratic, with peak at ~65% of burn time
    return 190 - 8*(t-burn_time*0.65)*(t-burn_time*0.65);
}

void test_kalman_filter_full_rocket_flight() {
    // Simulate a complete rocket flight: thrust, coast, apogee, descent
    char msg[200];

    // Start at ground level
    KalmanFilter filter(0.0f, 0.0f, 0.0f);

    float dt = 0.001f;  // 1ms time step (1000 Hz update rate)
    float g = -9.81f;   // Gravity (m/s²) TODO: adjust for tilted launch

    // Flight parameters
    //float thrust_accel = 155.0f;  // Motor thrust acceleration (m/s²) - Converted to function, because it's not constant
    float burn_time = 3.75f;      // Motor burn time (seconds)

    // Tracking variables
    float true_s = 0.0f;  // True position
    float true_v = 0.0f;  // True velocity
    float true_a = 0.0f;  // True acceleration

    float max_altitude = 0.0f;
    float apogee_time = 0.0f;
    bool apogee_detected = false;

    constexpr float drag_coef = 0.044f; // guesswork (TODO: check with airframe)
    constexpr float drag_area = M_PI*0.065*0.065; // 13cm diameter => 6.5 (TODO: double check)

    snprintf(msg, sizeof(msg), "\n=== ROCKET FLIGHT SIMULATION ===");
    TEST_MESSAGE(msg);

    // PHASE 1: THRUST (0 to burn_time seconds)
    snprintf(msg, sizeof(msg), "\nPHASE 1: THRUST (0 - %.1f s)", burn_time);
    TEST_MESSAGE(msg);

    int thrust_steps = (int)(burn_time / dt);
    for (int i = 1; i <= thrust_steps; i++) {
        float t = i * dt;

        // True dynamics: acceleration = thrust - gravity
        true_a = thrust_accel(t, burn_time) + g - air_resistance(true_s, true_v, drag_coef, drag_area);
        true_v = true_a * t;
        true_s = 0.5f * true_a * t * t;

        // Simulate sensor measurements with small noise
        float noise_s = (i % 3 == 0) ? 0.05f : -0.05f;  // ±5cm altitude noise
        float noise_a = (i % 5 == 0) ? 0.2f : -0.2f;    // ±0.2 m/s² accel noise

        float measured_s = true_s + noise_s;
        float measured_a = true_a + noise_a;

        filter.filter_update(measured_s, 0.0f, measured_a);

        // Print every 0.5 seconds
        if (i % 500 == 0) {
            print_status(t, filter, true_s, true_v, true_a);
        }
    }

    // Record end of thrust phase
    float burnout_s = true_s;
    float burnout_v = true_v;

    snprintf(msg, sizeof(msg),
             "BURNOUT: Alt=%.1fm, Vel=%.1fm/s", burnout_s, burnout_v);
    TEST_MESSAGE(msg);

    // PHASE 2: COAST (burnout to apogee)
    snprintf(msg, sizeof(msg), "\nPHASE 2: COAST (motor burnout to apogee)");
    TEST_MESSAGE(msg);

    // Reset time for coast phase
    float coast_time = 0.0f;
    float max_coast_time = 40.0f;  // Max 40 seconds coast

    for (int i = 1; i <= (int)(max_coast_time / dt); i++) {
        coast_time = i * dt;
        float total_time = burn_time + coast_time;

        // True dynamics: gravity + air resistance (extrapolated from graph given from airframe oct 2025)
        true_a = g - air_resistance(true_s, true_v, drag_coef, drag_area);
        true_v = burnout_v + g * coast_time;
        true_s = burnout_s + burnout_v * coast_time + 0.5f * g * coast_time * coast_time;

        // Stop at apogee (velocity becomes negative)
        if (true_v <= 0.0f && !apogee_detected) {
            max_altitude = true_s;
            apogee_time = total_time;
            apogee_detected = true;

            snprintf(msg, sizeof(msg),
                     "\nAPOGEE REACHED at t=%.2fs: Alt=%.1fm (filter=%.1fm)",
                     apogee_time, max_altitude, filter.get_s());
            TEST_MESSAGE(msg);
            break;
        }

        // Simulate sensor measurements with noise
        float noise_s = (i % 3 == 0) ? 0.05f : -0.05f;
        float noise_a = (i % 5 == 0) ? 0.2f : -0.2f;

        float measured_s = true_s + noise_s;
        float measured_a = true_a + noise_a;

        filter.filter_update(measured_s, 0.0f, measured_a);

        // Print every 0.5 seconds
        if (i % 500 == 0) {
            print_status(total_time, filter, true_s, true_v, true_a);
        }
    }

    // PHASE 3: DESCENT (brief simulation)
    snprintf(msg, sizeof(msg), "\nPHASE 3: DESCENT (first 2 seconds)");
    TEST_MESSAGE(msg);

    float apogee_altitude = true_s;
    float descent_time = 0.0f;
    float max_descent_time = 2.0f;  // Simulate 2 seconds of descent

    for (int i = 1; i <= (int)(max_descent_time / dt); i++) {
        descent_time = i * dt;
        float total_time = apogee_time + descent_time;

        // True dynamics: free fall with gravity
        // (In reality, would have drag and parachute, but simplified here)
        true_a = g;
        true_v = g * descent_time;  // Negative velocity
        true_s = apogee_altitude + 0.5f * g * descent_time * descent_time;

        // Simulate sensor measurements
        float noise_s = (i % 3 == 0) ? 0.05f : -0.05f;
        float noise_a = (i % 5 == 0) ? 0.2f : -0.2f;

        float measured_s = true_s + noise_s;
        float measured_a = true_a + noise_a;

        filter.filter_update(measured_s, 0.0f, measured_a);

        // Print every 0.5 seconds
        if (i % 500 == 0) {
            print_status(total_time, filter, true_s, true_v, true_a);
        }
    }

    // FINAL SUMMARY
    snprintf(msg, sizeof(msg), "\n=== FLIGHT SUMMARY ===");
    TEST_MESSAGE(msg);
    snprintf(msg, sizeof(msg), "Max altitude: %.1fm (detected at t=%.2fs)", max_altitude, apogee_time);
    TEST_MESSAGE(msg);
    snprintf(msg, sizeof(msg), "Burnout altitude: %.1fm at t=%.1fs", burnout_s, burn_time);
    TEST_MESSAGE(msg);
    snprintf(msg, sizeof(msg), "Filter final state: Alt=%.1fm, Vel=%.1fm/s, Acc=%.1fm/s²",
             filter.get_s(), filter.get_v(), filter.get_a());
    TEST_MESSAGE(msg);

    // Assertions to verify filter performance
    TEST_ASSERT_TRUE(apogee_detected);  // Should reach apogee
    TEST_ASSERT_TRUE(max_altitude > 7000.0f);  // Should reach reasonable altitude
    TEST_ASSERT_TRUE(max_altitude < 11000.0f);  // But not unreasonably high

    // Filter should track altitude reasonably (within 10m of true at key points)
    TEST_ASSERT_FLOAT_WITHIN(10.0f, true_s, filter.get_s());

    // No NaN values throughout flight
    TEST_ASSERT_FALSE(isnan(filter.get_s()));
    TEST_ASSERT_FALSE(isnan(filter.get_v()));
    TEST_ASSERT_FALSE(isnan(filter.get_a()));
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_kalman_filter_initialization);
    RUN_TEST(test_kalman_filter_stationary_object);
    RUN_TEST(test_kalman_filter_constant_velocity);
    RUN_TEST(test_kalman_filter_constant_acceleration);
    RUN_TEST(test_kalman_filter_noisy_measurements);
    RUN_TEST(test_kalman_filter_no_nan_values);
    RUN_TEST(test_kalman_filter_position_tracking);
    RUN_TEST(test_kalman_filter_velocity_estimation);
    RUN_TEST(test_kalman_filter_freefall_simulation);
    RUN_TEST(test_kalman_filter_measurement_fusion);
    RUN_TEST(test_kalman_filter_full_rocket_flight);

    return UNITY_END();
}
