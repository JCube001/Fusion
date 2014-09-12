/*
The MIT License (MIT)

Copyright (c) 2013, 2014 Jacob McGladdery

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/**
 * @file marg_filter.cpp
 * @brief MARG filter implementation.
 */

#include <math.h>

#include "marg_filter.h"
#include "quaternion.h"

MARGFilter::MARGFilter() :
    Filter(),
    Eb_hat(Quaternion(0.0f, 1.0f, 0.0f, 0.0f)),
    Sw_b(Quaternion()),
    zeta(1.0f)
{
}

void MARGFilter::setGyroDriftGain(const float drift)
{
    zeta = sqrt(3.0f / 4.0f) * drift;
}

void MARGFilter::update(float wx, float wy, float wz,
                        float ax, float ay, float az,
                        float mx, float my, float mz)
{
    // Auxiliary variables to avoid repeated calculations
    const Quaternion two_SEq = 2.0f * SEq_hat;
    const Quaternion two_Eb = 2.0f * Eb_hat;
    const Quaternion two_Eb_x_SEq = two_Eb.x * SEq_hat;
    const Quaternion two_Eb_z_SEq = two_Eb.z * SEq_hat;

    // Compute the gravity objective function
    const Quaternion f_g = SEq_hat.conjugate() * Eg_hat * SEq_hat
            - Quaternion(0.0f, ax, ay, az).normalized();

    // Compute the gravity Jacobian matrix
    // Negative elements are negated in matrix multiplication
    const float J_11_or_24 = two_SEq.y;
    const float J_12_or_23 = two_SEq.z;
    const float J_13_or_22 = two_SEq.w;
    const float J_14_or_21 = two_SEq.x;
    const float J_32 = 2.0f * J_14_or_21;
    const float J_33 = 2.0f * J_11_or_24;

    // Compute the magnetic field objective function
    const Quaternion Sm_hat = Quaternion(0.0f, mx, my, mz).normalized();
    const Quaternion f_b = SEq_hat.conjugate() * Eb_hat * SEq_hat - Sm_hat;

    // Compute the magnetic field Jacobian matrix
    // Negative elements are negated in matrix multiplication
    const float J_41 = two_Eb_z_SEq.y;
    const float J_42 = two_Eb_z_SEq.z;
    const float J_43 = 2.0f * two_Eb_x_SEq.y + two_Eb_z_SEq.w;
    const float J_44 = 2.0f * two_Eb_x_SEq.z - two_Eb_z_SEq.x;
    const float J_51 = two_Eb_x_SEq.z - two_Eb_z_SEq.x;
    const float J_52 = two_Eb_x_SEq.y + two_Eb_z_SEq.w;
    const float J_53 = two_Eb_x_SEq.x + two_Eb_z_SEq.z;
    const float J_54 = two_Eb_x_SEq.w - two_Eb_z_SEq.y;
    const float J_61 = two_Eb_x_SEq.y;
    const float J_62 = two_Eb_x_SEq.z - 2.0f * two_Eb_z_SEq.x;
    const float J_63 = two_Eb_x_SEq.w - 2.0f * two_Eb_z_SEq.y;
    const float J_64 = two_Eb_x_SEq.x;

    // Compute the normalized gradient descent (matrix multiplication)
    const Quaternion SEq_hat_dot =
            Quaternion(J_14_or_21 * f_g.y - J_11_or_24 * f_g.x - J_41 * f_b.x - J_51 * f_b.y + J_61 * f_b.z,
                       J_12_or_23 * f_g.x + J_13_or_22 * f_g.y - J_32 * f_g.z + J_42 * f_b.x + J_52 * f_b.y + J_62 * f_b.z,
                       J_12_or_23 * f_g.y - J_33 * f_g.z - J_13_or_22 * f_g.x - J_43 * f_b.x + J_53 * f_b.y + J_63 * f_b.z,
                       J_14_or_21 * f_g.x + J_11_or_24 * f_g.y - J_44 * f_b.x - J_54 * f_b.y + J_64 * f_b.z).normalized();

    // Compute the angular estimated direction of gyroscope error then compute
    // and remove the gyroscope biases while computing the quaternion
    // derivative measured by the gyroscope
    Sw_b += zeta * (two_SEq.conjugate() * SEq_hat_dot) * deltaTime;
    const Quaternion SEq_dot_omega = 0.5f * SEq_hat * (Quaternion(0.0f, wx, wy, wz) - Sw_b);

    // Compute then integrate the estimated quaternion derivative
    SEq_hat += (SEq_dot_omega - (beta * SEq_hat_dot)) * deltaTime;

    // Normalize the output quaternion
    SEq_hat.normalize();
    
    // Compute the magnetic flux in the earth frame
    const Quaternion Eh_hat = SEq_hat * Sm_hat * SEq_hat.conjugate();

    // Normalize the magnetic flux vector to have only x and z components
    Eb_hat = Quaternion(0.0f, sqrt((Eh_hat.x * Eh_hat.x) + (Eh_hat.y * Eh_hat.y)), 0.0f, Eh_hat.z);
}
