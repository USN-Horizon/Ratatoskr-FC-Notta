#include <Arduino.h>
#include <unity.h>
#include "LSM6DSO32.h"
#include "mocks/MockI2C.h"

MockI2C mockI2C;
LSM6DSO32 imu(&mockI2C);

void setUp() {
    // Du kan sette testdata her om sensoren leser bestemte registre
    mockI2C.reset();
}

void test_lsm6dso32_begin_should_succeed() {
    bool ok = imu.begin();
    TEST_ASSERT_TRUE_MESSAGE(ok, "LSM6DSO32 initialization should succeed");
}

void test_lsm6dso32_accel_data_within_expected_range() {
    float ax, ay, az;
    imu.readAcceleration(ax, ay, az);
    TEST_ASSERT_FLOAT_WITHIN(100.0, 0.0, ax);
    TEST_ASSERT_FLOAT_WITHIN(100.0, 0.0, ay);
    TEST_ASSERT_FLOAT_WITHIN(100.0, 0.0, az);
}

void test_lsm6dso32_gyro_data_within_expected_range() {
    float gx, gy, gz;
    imu.readGyroscope(gx, gy, gz);
    TEST_ASSERT_FLOAT_WITHIN(500.0, 0.0, gx);
    TEST_ASSERT_FLOAT_WITHIN(500.0, 0.0, gy);
    TEST_ASSERT_FLOAT_WITHIN(500.0, 0.0, gz);
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_lsm6dso32_begin_should_succeed);
    RUN_TEST(test_lsm6dso32_accel_data_within_expected_range);
    RUN_TEST(test_lsm6dso32_gyro_data_within_expected_range);
    UNITY_END();
}

void loop() {}
