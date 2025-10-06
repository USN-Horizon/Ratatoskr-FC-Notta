//
// Created by syvers on 24.09.2025.
//

#include "quaternion_translation.h"

void quaternion_to_rotation_matrix(float qw, float qx, float qy, float qz, float matrix[3][3])
{
    matrix[0][0] = qw * qw + qx * qx - qy * qy - qz * qz;
    matrix[0][1] = 2 * (qx * qy - qw * qz);
    matrix[0][2] = 2 * (qx * qz + qw * qy);

    matrix[1][0] = 2 * (qx * qy + qw * qz);
    matrix[1][1] = qw * qw - qx * qx + qy * qy - qz * qz;
    matrix[1][2] = 2 * (qy * qz - qw * qx);

    matrix[2][0] = 2 * (qx * qz - qw * qy);
    matrix[2][1] = 2 * (qy * qz + qw * qx);
    matrix[2][2] = qw * qw - qx * qx - qy * qy + qz * qz;
};