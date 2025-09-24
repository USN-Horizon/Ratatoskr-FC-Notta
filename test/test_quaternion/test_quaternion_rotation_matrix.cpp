#include <unity.h>
#include "madgwick_filter.h"
#include "quaternion_translation.h"
#include <cmath>

void setUp(void) {
}

void tearDown(void) {
}

void test_identity_quaternion_to_identity_matrix() {
    // Identity quaternion (1, 0, 0, 0) should produce identity matrix
    float matrix[3][3];
    quaternion_to_rotation_matrix(1.0f, 0.0f, 0.0f, 0.0f, matrix);
    
    // Identity matrix
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, matrix[0][0]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, matrix[0][1]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, matrix[0][2]);
    
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, matrix[1][0]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, matrix[1][1]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, matrix[1][2]);
    
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, matrix[2][0]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, matrix[2][1]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, matrix[2][2]);
}

void test_90_degree_x_rotation() {
    // 90° rotation around X-axis: q = (cos(45°), sin(45°), 0, 0)
    float cos45 = 0.7071067812f;
    float matrix[3][3];
    quaternion_to_rotation_matrix(cos45, cos45, 0.0f, 0.0f, matrix);
    
    // Expected matrix for 90° X rotation:
    // [1,  0,  0]
    // [0,  0, -1]
    // [0,  1,  0]
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, matrix[0][0]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, matrix[0][1]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, matrix[0][2]);
    
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, matrix[1][0]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, matrix[1][1]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -1.0f, matrix[1][2]);
    
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, matrix[2][0]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, matrix[2][1]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, matrix[2][2]);
}

void test_90_degree_z_rotation() {
    // 90° rotation around Z-axis: q = (cos(45°), 0, 0, sin(45°))
    float cos45 = 0.7071067812f;
    float matrix[3][3];
    quaternion_to_rotation_matrix(cos45, 0.0f, 0.0f, cos45, matrix);
    
    // Expected matrix for 90° Z rotation:
    // [ 0, -1,  0]
    // [ 1,  0,  0]
    // [ 0,  0,  1]
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, matrix[0][0]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, -1.0f, matrix[0][1]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, matrix[0][2]);
    
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, matrix[1][0]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, matrix[1][1]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, matrix[1][2]);
    
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, matrix[2][0]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, matrix[2][1]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, matrix[2][2]);
}

void test_rotation_matrix_orthogonality() {
    // Test that the resulting matrix is orthogonal (columns are unit vectors and orthogonal)
    float matrix[3][3];
    quaternion_to_rotation_matrix(0.8f, 0.2f, 0.4f, 0.4f, matrix); // Random normalized quaternion
    
    // Check column 1 is unit vector
    float col1_magnitude = sqrt(matrix[0][0]*matrix[0][0] + matrix[1][0]*matrix[1][0] + matrix[2][0]*matrix[2][0]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, col1_magnitude);
    
    // Check column 2 is unit vector  
    float col2_magnitude = sqrt(matrix[0][1]*matrix[0][1] + matrix[1][1]*matrix[1][1] + matrix[2][1]*matrix[2][1]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, col2_magnitude);
    
    // Check column 3 is unit vector
    float col3_magnitude = sqrt(matrix[0][2]*matrix[0][2] + matrix[1][2]*matrix[1][2] + matrix[2][2]*matrix[2][2]);
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 1.0f, col3_magnitude);
    
    // Check columns are orthogonal (dot product = 0)
    float dot_12 = matrix[0][0]*matrix[0][1] + matrix[1][0]*matrix[1][1] + matrix[2][0]*matrix[2][1];
    TEST_ASSERT_FLOAT_WITHIN(0.001f, 0.0f, dot_12);
}

void test_madgwick_filter_to_rotation_matrix_integration() {
    // Test using actual output from madgwick filter
    madgwick_filter filter(1.0f, 0.0f, 0.0f, 0.0f);
    
    // Apply some motion
    filter.filter_update(0.0f, 0.0f, 1.0f, 0.1f, 0.0f, 0.0f);
    
    float matrix[3][3];
    quaternion_to_rotation_matrix(filter.get_w(), filter.get_x(), filter.get_y(), filter.get_z(), matrix);
    
    // Basic sanity checks - should still be orthogonal
    float col1_magnitude = sqrt(matrix[0][0]*matrix[0][0] + matrix[1][0]*matrix[1][0] + matrix[2][0]*matrix[2][0]);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 1.0f, col1_magnitude);
}

int main() {
    UNITY_BEGIN();
    
    RUN_TEST(test_identity_quaternion_to_identity_matrix);
    RUN_TEST(test_90_degree_x_rotation);
    RUN_TEST(test_90_degree_z_rotation);
    RUN_TEST(test_rotation_matrix_orthogonality);
    RUN_TEST(test_madgwick_filter_to_rotation_matrix_integration);
    
    return UNITY_END();
}
