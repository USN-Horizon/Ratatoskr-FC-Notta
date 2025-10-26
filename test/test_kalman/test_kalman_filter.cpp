#include <unity.h>
#include "kalman_filter.h"
#include <cmath>

void setUp(void) {
}

void tearDown(void) {
}

void test_kalman_filter_gain_calculation() {
    KalmanFilter filter(1.0f, 0.0f, 0.0f);
    
}

int main() {
    UNITY_BEGIN();
    
    RUN_TEST(test_kalman_filter_gain_calculation);

    return UNITY_END();
}
