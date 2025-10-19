#include <Arduino.h>
#include <unity.h>
#include "MS5611.h"
#include "mocks/MockI2C.h"

MockI2C mockI2C;
MS5611 sensor(&mockI2C);

void setUp() {}
void tearDown() {}

void test_initialization_should_succeed() {
    bool result = sensor.begin();
    TEST_ASSERT_TRUE_MESSAGE(result, "MS5611 should initialize successfully");
}

void test_read_pressure_returns_valid_value() {
    float pressure = sensor.readPressure();
    TEST_ASSERT_TRUE_MESSAGE(pressure > 0, "Pressure should be greater than zero");
}

void test_read_temperature_returns_valid_value() {
    float temperature = sensor.readTemperature();
    TEST_ASSERT_TRUE_MESSAGE(temperature > -50 && temperature < 100, "Temperature should be realistic");
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(test_initialization_should_succeed);
    RUN_TEST(test_read_pressure_returns_valid_value);
    RUN_TEST(test_read_temperature_returns_valid_value);
    UNITY_END();
}

void loop() {}

