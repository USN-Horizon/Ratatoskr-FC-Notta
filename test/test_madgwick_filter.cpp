#include <unity.h>
#include "../lib/filters/madgwick_filter.h"
#include <cmath>

void setUp(void) {
}

void tearDown(void) {
}

void test_madgwick_filter_initialization() {
    madgwick_filter filter(1.0f, 0.0f, 0.0f, 0.0f);
    
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, filter.get_w());
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, filter.get_x());
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, filter.get_y());
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, filter.get_z());
}

void test_madgwick_filter_quaternion_normalization() {
    madgwick_filter filter(0.5f, 0.5f, 0.5f, 0.5f);
    
    float w = filter.get_w();
    float x = filter.get_x();
    float y = filter.get_y();
    float z = filter.get_z();
    
    float magnitude = sqrt(w*w + x*x + y*y + z*z);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, magnitude);
}

void test_madgwick_filter_no_motion() {
    madgwick_filter filter(1.0f, 0.0f, 0.0f, 0.0f);
    
    float acc_x = 0.0f, acc_y = 0.0f, acc_z = 1.0f;
    float gyro_x = 0.0f, gyro_y = 0.0f, gyro_z = 0.0f;
    
    float initial_w = filter.get_w();
    float initial_x = filter.get_x();
    float initial_y = filter.get_y();
    float initial_z = filter.get_z();
    
    filter.filter_update(acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z);
    
    float w = filter.get_w();
    float x = filter.get_x();
    float y = filter.get_y();
    float z = filter.get_z();
    
    float magnitude = sqrt(w*w + x*x + y*y + z*z);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, magnitude);
}

void test_madgwick_filter_gravity_alignment() {
    madgwick_filter filter(1.0f, 0.0f, 0.0f, 0.0f);
    
    float acc_x = 0.0f, acc_y = 0.0f, acc_z = 1.0f;
    float gyro_x = 0.0f, gyro_y = 0.0f, gyro_z = 0.0f;
    
    for (int i = 0; i < 100; i++) {
        filter.filter_update(acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z);
    }
    
    float w = filter.get_w();
    float x = filter.get_x();
    float y = filter.get_y();
    float z = filter.get_z();
    
    float magnitude = sqrt(w*w + x*x + y*y + z*z);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, magnitude);
    
    TEST_ASSERT_FLOAT_WITHIN(0.1f, 1.0f, abs(w));
}

void test_madgwick_filter_x_axis_gravity() {
    madgwick_filter filter(1.0f, 0.0f, 0.0f, 0.0f);
    
    float acc_x = 1.0f, acc_y = 0.0f, acc_z = 0.0f;
    float gyro_x = 0.0f, gyro_y = 0.0f, gyro_z = 0.0f;
    
    for (int i = 0; i < 1000; i++) {
        filter.filter_update(acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z);
    }
    
    float w = filter.get_w();
    float x = filter.get_x();
    float y = filter.get_y();
    float z = filter.get_z();
    
    float magnitude = sqrt(w*w + x*x + y*y + z*z);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, magnitude);
}

void test_madgwick_filter_multiple_updates() {
    madgwick_filter filter(1.0f, 0.0f, 0.0f, 0.0f);
    
    for (int i = 0; i < 1000; i++) {
        float acc_x = 0.1f * sin(i * 0.01f);
        float acc_y = 0.1f * cos(i * 0.01f);
        float acc_z = 0.9f;
        float gyro_x = 0.01f * cos(i * 0.02f);
        float gyro_y = 0.01f * sin(i * 0.02f);
        float gyro_z = 0.005f;
        
        filter.filter_update(acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z);
        
        float w = filter.get_w();
        float x = filter.get_x();
        float y = filter.get_y();
        float z = filter.get_z();
        
        float magnitude = sqrt(w*w + x*x + y*y + z*z);
        TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, magnitude);
    }
}

void test_madgwick_filter_zero_acceleration_handling() {
    madgwick_filter filter(1.0f, 0.0f, 0.0f, 0.0f);
    
    float acc_x = 0.0f, acc_y = 0.0f, acc_z = 0.0f;
    float gyro_x = 0.1f, gyro_y = 0.0f, gyro_z = 0.0f;
    
    filter.filter_update(acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z);
    
    float w = filter.get_w();
    float x = filter.get_x();
    float y = filter.get_y();
    float z = filter.get_z();
    
    TEST_ASSERT_FALSE(isnan(w));
    TEST_ASSERT_FALSE(isnan(x));
    TEST_ASSERT_FALSE(isnan(y));
    TEST_ASSERT_FALSE(isnan(z));
}

void test_madgwick_filter_large_inputs() {
    madgwick_filter filter(1.0f, 0.0f, 0.0f, 0.0f);
    
    float acc_x = 100.0f, acc_y = 100.0f, acc_z = 100.0f;
    float gyro_x = 10.0f, gyro_y = 10.0f, gyro_z = 10.0f;
    
    filter.filter_update(acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z);
    
    float w = filter.get_w();
    float x = filter.get_x();
    float y = filter.get_y();
    float z = filter.get_z();
    
    float magnitude = sqrt(w*w + x*x + y*y + z*z);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, magnitude);
    
    TEST_ASSERT_FALSE(isnan(w));
    TEST_ASSERT_FALSE(isnan(x));
    TEST_ASSERT_FALSE(isnan(y));
    TEST_ASSERT_FALSE(isnan(z));
}

int main() {
    UNITY_BEGIN();
    
    RUN_TEST(test_madgwick_filter_initialization);
    RUN_TEST(test_madgwick_filter_quaternion_normalization);
    RUN_TEST(test_madgwick_filter_no_motion);
    RUN_TEST(test_madgwick_filter_gravity_alignment);
    RUN_TEST(test_madgwick_filter_x_axis_gravity);
    RUN_TEST(test_madgwick_filter_multiple_updates);
    RUN_TEST(test_madgwick_filter_zero_acceleration_handling);
    RUN_TEST(test_madgwick_filter_large_inputs);
    
    return UNITY_END();
}