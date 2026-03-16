#include <Arduino.h>
#include <unity.h>
#include "MAX_M10S.h"
#include "mocks/MockI2C.h"

MockI2C mockI2C;
MAX_M10S gps(&mockI2C);

void setUp() {
    mockI2C.reset();
}

void test_maxm10s_begin_should_succeed() {
    bool ok = gps.begin();
    TEST_ASSERT_TRUE_MESSAGE(ok, "MAX-M10S should initialize successfully");
}

void test_maxm10s_read_coordinates_should_return_valid_data() {
    float lat = 0, lon = 0;
    bool ok = gps.readCoordinates(lat, lon);
    TEST_ASSERT_TRUE_MESSAGE(ok, "readCoordinates should return true");
    TEST_ASSERT_FLOAT_WITHIN(180.0, 0.0, lat);
    TEST_ASSERT_FLOAT_WITHIN(180.0, 0.0, lon);
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_maxm10s_begin_should_succeed);
    RUN_TEST(test_maxm10s_read_coordinates_should_return_valid_data);
    UNITY_END();
}

void loop() {}
