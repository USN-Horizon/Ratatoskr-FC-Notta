#include <Arduino.h>
#include <unity.h>
#include "KX134.h"
#include "mocks/MockSPI.h"

MockSPI mockSPI;
KX134 accel(&mockSPI);

void setUp() {}
void tearDown() {}

void test_kx134_initialization_should_succeed() {
    bool ok = accel.begin();
    TEST_ASSERT_TRUE_MESSAGE(ok, "KX134 initialization should succeed");
}

void test_kx134_read_acceleration_returns_reasonable_values() {
    float x, y, z;
    accel.readAcceleration(x, y, z);
    TEST_ASSERT_FLOAT_WITHIN(10.0, 0.0, x);
    TEST_ASSERT_FLOAT_WITHIN(10.0, 0.0, y);
    TEST_ASSERT_FLOAT_WITHIN(10.0, 0.0, z);
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_kx134_initialization_should_succeed);
    RUN_TEST(test_kx134_read_acceleration_returns_reasonable_values);
    UNITY_END();
}

void loop() {}
