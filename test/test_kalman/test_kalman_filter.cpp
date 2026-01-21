#include <unity.h>
#include <cmath>
#include <stdio.h>
#include <random>
#include "kalman_filter.h"
#include "sim_helpers.h"

void setUp(void) {
}

void tearDown(void) {
}

void test_kalman_filter_initialization() {
    const KalmanFilter filter(10.0f, 5.0f, 2.0f);

    TEST_ASSERT_FLOAT_WITHIN(0.001f, 10.0f, filter.get_s());
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 5.0f, filter.get_v());
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 2.0f, filter.get_a());
}

void test_kalman_filter_stationary_object() {
    // Test a stationary object (no movement, no acceleration)
    KalmanFilter filter(0.0f, 0.0f, 0.0f);

    constexpr float dt = 0.001f;

    // Update with stationary measurements
    for (int i = 0; i < 100; i++) {
        filter.filter_update(0.0f, 0.0f, dt);
    }

    // Should converge to zero position, velocity, and acceleration
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, filter.get_s());
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, filter.get_v());
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 0.0f, filter.get_a());
}

void test_kalman_filter_constant_velocity() {
    // Test object moving at constant velocity
    KalmanFilter filter(0.0f, 10.0f, 0.0f);

    constexpr float dt = 0.001f;
    char msg[100];

    // Simulate constant velocity motion
    for (int i = 0; i < 100; i++) {
        const float expected_s = 10.0f * (i + 1) * dt;  // s = v * t
        filter.filter_update(expected_s, 0.0f, dt);  // position increases, no acceleration

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

    constexpr float dt = 0.001f;
    constexpr float a = 9.81f;  // Acceleration (e.g., gravity)

    // Simulate constant acceleration
    for (int i = 1; i <= 50; i++) {
        const float t = i * dt;
        const float expected_s = 0.5f * a * t * t;  // s = 0.5 * a * t^2

        filter.filter_update(expected_s, a, dt);
    }

    // Acceleration should remain around 9.81 m/s^2
    TEST_ASSERT_FLOAT_WITHIN(2.0f, 9.81f, filter.get_a());
}

void test_kalman_filter_noisy_measurements() {
    // Test filter's ability to smooth noisy measurements
    KalmanFilter filter(0.0f, 0.0f, 0.0f);

    constexpr float dt = 0.001f;

    // Add noise to position measurements but keep acceleration at zero
    for (int i = 0; i < 100; i++) {
        const float noise = (i % 2 == 0) ? 0.5f : -0.5f;  // Alternating noise
        filter.filter_update(0.0f + noise, 0.0f, dt);
    }

    // Filtered position should be close to zero despite noisy measurements
    TEST_ASSERT_FLOAT_WITHIN(0.5f, 0.0f, filter.get_s());
}

void test_kalman_filter_no_nan_values() {
    // Ensure filter doesn't produce NaN values with various inputs
    KalmanFilter filter(100.0f, 50.0f, 10.0f);

    constexpr float dt = 0.001f;

    // Test with zero measurements
    filter.filter_update(0.0f, 0.0f, dt);

    TEST_ASSERT_FALSE(isnan(filter.get_s()));
    TEST_ASSERT_FALSE(isnan(filter.get_v()));
    TEST_ASSERT_FALSE(isnan(filter.get_a()));

    // Test with large measurements
    filter.filter_update(1000.0f, 100.0f, dt);

    TEST_ASSERT_FALSE(isnan(filter.get_s()));
    TEST_ASSERT_FALSE(isnan(filter.get_v()));
    TEST_ASSERT_FALSE(isnan(filter.get_a()));

    // Test with negative measurements
    filter.filter_update(-50.0f, -20.0f, dt);

    TEST_ASSERT_FALSE(isnan(filter.get_s()));
    TEST_ASSERT_FALSE(isnan(filter.get_v()));
    TEST_ASSERT_FALSE(isnan(filter.get_a()));
}

void test_kalman_filter_position_tracking() {
    // Test that filter tracks position measurements
    KalmanFilter filter(0.0f, 0.0f, 0.0f);

    constexpr float dt = 0.001f;

    // Move to position 10m
    for (int i = 0; i < 50; i++) {
        filter.filter_update(10.0f, 0.0f, dt);
    }

    // Position should converge to 10m
    TEST_ASSERT_FLOAT_WITHIN(2.0f, 10.0f, filter.get_s());

    // Move to position 20m
    for (int i = 0; i < 50; i++) {
        filter.filter_update(20.0f, 0.0f, dt);
    }

    // Position should converge to 20m
    TEST_ASSERT_FLOAT_WITHIN(2.0f, 20.0f, filter.get_s());
}

void test_kalman_filter_velocity_estimation() {
    // Test that filter can estimate velocity from position changes
    // Note: This is a challenging scenario as velocity is not directly measured
    KalmanFilter filter(0.0f, 0.0f, 0.0f);

    constexpr float dt = 0.001f;
    constexpr float velocity = 25.0f;  // 25 m/s

    // Provide position measurements that imply velocity of 25 m/s
    // Need more iterations for velocity to converge from position-only data
    for (int i = 1; i <= 1000; i++) {
        const float expected_s = velocity * i * dt;
        filter.filter_update(expected_s, 0.0f, dt);
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

    constexpr float dt = 0.001f;
    constexpr float g = -9.81f;
    constexpr float v0 = 100.0f;  // Initial upward velocity

    // Simulate 100 steps of freefall
    for (int i = 1; i <= 100; i++) {
        const float t = i * dt;
        const float s = v0 * t + 0.5f * g * t * t;  // Kinematic equation
        //float v = v0 + g * t; not needed

        filter.filter_update(s, g, dt);
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
    const float a = 5.0f;
    const float dt = 0.001f;

    for (int i = 1; i <= 100; i++) {
        const float t = i * dt;
        const float s = 0.5f * a * t * t;  // Position from acceleration
        filter.filter_update(s, a, dt);
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
    // acceleration is approximately quadratic, with peak at ~44% of burn time
    return std::max(0.0f, 195.0f - 8*(t-burn_time*0.44f)*(t-burn_time*0.44f));
}

/**
 * @brief Simulates a complete rocket flight and tests the Kalman filter's ability
 *        to track the rocket's state (position, velocity, and acceleration) throughout
 *        all stages of flight.
 *
 * This method performs a series of simulations for the following phases of a rocket flight:
 * - Thrust phase: Simulates rocket acceleration due to motor thrust until burnout.
 * - Coast phase: Simulates the rocket's motion from motor burnout to apogee (when velocity reaches zero).
 * - Descent phase: Simulates initial descent under gravity after apogee.
 *
 * The acceleration values are calculated using the motor and airframe specifications of the Ratatoskr rocket.
 * Which rocket of which the forces are simulated from is not really that important. What's important is testing
 * the deviance from the true path.
 */
void test_kalman_filter_full_rocket_flight() {
    // Simulate a complete rocket flight: thrust, coast, apogee, descent
    char msg[200];

    // Start at ground level
    KalmanFilter filter(0.0f, 0.0f, 0.0f);

    constexpr float dt = 0.001f;  // 1ms time step (1000 Hz update rate)
    constexpr float g = -9.81f;   // Gravity (m/s²)

    // Flight parameters
    //float thrust_accel = 155.0f;  // Motor thrust acceleration (m/s²) - Converted to function, because it's not constant
    constexpr float burn_time = 6.3f;      // Motor burn time (seconds)
    // Is only this high because thust accel is variable. mean max accel time is more like 3.75

    // Tracking variables
    float true_s = 0.0f;  // True position
    float true_v = 0.0f;  // True velocity
    float true_a = 0.0f;  // True acceleration

    // true / non-filter values updated by this function
    float true_max_altitude = 0.0f;
    float true_apogee_time = 0.0f;
    bool true_apogee_reached = false;

    // filter values
    float max_altitude = 0.0f;
    float apogee_time = 0.0f;
    bool apogee_detected = false;

    constexpr float drag_coef = 0.044f; // guesswork (TODO: check with airframe)
    constexpr float drag_area = M_PI*0.065*0.065; // 13cm diameter => 6.5 (TODO: double check)

    // Initialize seeded random number generators for reproducible noise
    std::mt19937 rng(42);  // Fixed seed for deterministic tests
    std::normal_distribution<float> noise_dist_s(0.0f, 0.1f);   // Mean=0, StdDev=10cm (MS5611 altitude resolution)
    std::normal_distribution<float> noise_dist_a(0.0f, 0.053f); // Mean=0, StdDev=0.053 m/s² (LSM6DSO32 ±32g RMS noise)

    snprintf(msg, sizeof(msg), "\n=== ROCKET FLIGHT SIMULATION ===");
    TEST_MESSAGE(msg);

    // PHASE 1: THRUST (0 to burn_time seconds)
    snprintf(msg, sizeof(msg), "\nPHASE 1: THRUST (0 - %.1f s)", burn_time);
    TEST_MESSAGE(msg);

    constexpr int thrust_steps = static_cast<int>(burn_time / dt);
    for (int i = 1; i <= thrust_steps; i++) {
        const float t = i * dt;

        // True dynamics: acceleration = thrust - gravity
        true_a = thrust_accel(t, burn_time) + g - air_resistance(true_s, true_v, drag_coef, drag_area);
        true_v += true_a * dt;
        true_s += true_v * dt;

        // Simulate sensor measurements with normally distributed noise
        const float noise_s = noise_dist_s(rng);  // Gaussian noise, σ=10cm
        const float noise_a = noise_dist_a(rng);  // Gaussian noise, σ=0.053 m/s²

        const float measured_s = true_s + noise_s;
        const float measured_a = true_a + noise_a;

        filter.filter_update(measured_s, measured_a, dt);

        // Print every 0.5 seconds
        if (i % 500 == 0) {
            print_status(t, filter, true_s, true_v, true_a);
        }
    }

    // Record end of thrust phase
    const float burnout_s = true_s;
    const float burnout_v = true_v;

    snprintf(msg, sizeof(msg),
             "BURNOUT: Alt=%.1fm, Vel=%.1fm/s", burnout_s, burnout_v);
    TEST_MESSAGE(msg);

    // PHASE 2: COAST (burnout to apogee)
    snprintf(msg, sizeof(msg), "\nPHASE 2: COAST (motor burnout to apogee)");
    TEST_MESSAGE(msg);

    // Reset time for coast phase
    float coast_time = 0.0f;
    constexpr float max_coast_time = 40.0f;  // Max 40 seconds coast

    for (int i = 1; i <= static_cast<int>(max_coast_time / dt); i++) {
        coast_time = i * dt;
        const float total_time = burn_time + coast_time;

        // True dynamics: gravity + air resistance (extrapolated from graph given from airframe oct 2025)
        true_a = g - air_resistance(true_s, true_v, drag_coef, drag_area);
        true_v += true_a * dt;
        true_s += true_v * dt;

        if (filter.get_v() <= 0.0f && !apogee_detected) {
            max_altitude = filter.get_s();
            apogee_time = total_time;
            apogee_detected = true;
        }
        // Stop phase at true apogee (velocity becomes negative)
        if (true_v <= 0.0f) {
            true_max_altitude = true_s;
            true_apogee_time = total_time;
            true_apogee_reached = true;

            snprintf(msg, sizeof(msg),
                     "\nAPOGEE REACHED at t=%.2fs: Alt=%.1fm (filter=%.1fm)",
                     true_apogee_time, true_max_altitude, filter.get_s());
            TEST_MESSAGE(msg);
            break;
        }

        // Simulate sensor measurements with normally distributed noise
        const float noise_s = noise_dist_s(rng);  // Gaussian noise, σ=10cm
        const float noise_a = noise_dist_a(rng);  // Gaussian noise, σ=0.053 m/s²

        const float measured_s = true_s + noise_s;
        const float measured_a = true_a + noise_a;

        filter.filter_update(measured_s, measured_a, dt);

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

    for (int i = 1; i <= static_cast<int>(max_descent_time / dt); i++) {
        descent_time = i * dt;
        const float total_time = true_apogee_time + descent_time;

        // True dynamics: free fall with gravity
        // (In reality, would have drag and parachute, but simplified here)
        true_a = g;
        true_v = g * descent_time;  // Negative velocity
        true_s = apogee_altitude + 0.5f * g * descent_time * descent_time;

        // Simulate sensor measurements with normally distributed noise
        const float noise_s = noise_dist_s(rng);  // Gaussian noise, σ=10cm
        const float noise_a = noise_dist_a(rng);  // Gaussian noise, σ=0.053 m/s²

        const float measured_s = true_s + noise_s;
        const float measured_a = true_a + noise_a;

        filter.filter_update(measured_s, measured_a, dt);

        // Print every 0.5 seconds
        if (i % 500 == 0) {
            print_status(total_time, filter, true_s, true_v, true_a);
        }
    }

    // FINAL SUMMARY
    snprintf(msg, sizeof(msg), "\n=== FLIGHT SUMMARY ===");
    TEST_MESSAGE(msg);
    snprintf(msg, sizeof(msg), "Max altitude: %.1fm (reached at t=%.2fs)", true_max_altitude, true_apogee_time);
    TEST_MESSAGE(msg);
    snprintf(msg, sizeof(msg), "Detected max altitude: %.1fm (reached at t=%.2fs)", max_altitude, apogee_time);
    TEST_MESSAGE(msg);
    snprintf(msg, sizeof(msg), "Burnout altitude: %.1fm at t=%.1fs", burnout_s, burn_time);
    TEST_MESSAGE(msg);
    snprintf(msg, sizeof(msg), "Filter final state: Alt=%.1fm, Vel=%.1fm/s, Acc=%.1fm/s²",
             filter.get_s(), filter.get_v(), filter.get_a());
    TEST_MESSAGE(msg);

    // Assertions to verify filter performance
    // This one isn't really evaluating the filter performance, more the realism of the sim forces applied
    TEST_ASSERT_TRUE(true_apogee_reached);  // Should reach apogee
    TEST_ASSERT_TRUE(true_max_altitude > 7000.0f);  // Should reach reasonable altitude
    TEST_ASSERT_TRUE(true_max_altitude < 11000.0f);  // But not unreasonably high

    // Filter should track altitude reasonably (within 10m of true at key points)
    TEST_ASSERT_FLOAT_WITHIN(10.0f, true_s, filter.get_s());

    // Filter should track time of apogee reasonably (within 1.5s of true)
    TEST_ASSERT_FLOAT_WITHIN(1.5f, true_apogee_time, apogee_time);
    snprintf(msg, sizeof(msg), "Delta apogee detection time (positive number means late detection): %.2f",
             apogee_time - true_apogee_time);
    TEST_MESSAGE(msg);

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
