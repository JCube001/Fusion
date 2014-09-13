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
 * @file  imu_filter.cpp
 * @brief IMU filter implementation.
 */

#include <math.h>
#include "imu_filter.h"
#include "quaternion.h"

/**
 * @brief   Default constructor.
 * @details Initializes the filter to a known state.
 */
IMUFilter::IMUFilter() :
    Filter()
{
}

/**
 * @brief   Updates estimated orientation.
 * @details Executes the filter algorithm and updates the estimated
 *          orientation.
 * @pre     The sample rate must be set to a value greater than zero.
 * @pre     The proper units must be used for the input parameters.
 * @post    The estimated orientation is updated.
 *
 * @param[in] wx The gyroscope X axis measurement in
 *               @f$\frac{\text{rad}}{\text{s}}@f$.
 * @param[in] wy The gyroscope Y axis measurement in
 *               @f$\frac{\text{rad}}{\text{s}}@f$.
 * @param[in] wz The gyroscope Z axis measurement in
 *               @f$\frac{\text{rad}}{\text{s}}@f$.
 * @param[in] ax The accelerometer X axis measurement in units of gravity.
 * @param[in] ay The accelerometer Y axis measurement in units of gravity.
 * @param[in] az The accelerometer Z axis measurement in units of gravity.
 */
void IMUFilter::update(float wx, float wy, float wz,
                       float ax, float ay, float az)
{
    // Auxiliary variables to avoid repeated calculations
    const Quaternion two_SEq = 2.0f * SEq_hat;

    // Compute the objective function
    const Quaternion f_g = SEq_hat.conjugate() * Eg_hat * SEq_hat
            - Quaternion(0.0f, ax, ay, az).normalized();

    // Compute the Jacobian matrix
    // Negative elements are negated in matrix multiplication
    const float J_11_or_24 = two_SEq.y;
    const float J_12_or_23 = two_SEq.z;
    const float J_13_or_22 = two_SEq.w;
    const float J_14_or_21 = two_SEq.x;
    const float J_32 = 2.0f * J_14_or_21;
    const float J_33 = 2.0f * J_11_or_24;

    // Compute the normalized gradient descent (matrix multiplication)
    const Quaternion SEq_hat_dot
            = Quaternion(J_14_or_21 * f_g.y - J_11_or_24 * f_g.x,
                         J_12_or_23 * f_g.x + J_13_or_22 * f_g.y - J_32 * f_g.z,
                         J_12_or_23 * f_g.y - J_33 * f_g.z - J_13_or_22 * f_g.x,
                         J_14_or_21 * f_g.x + J_11_or_24 * f_g.y).normalized();

    // Compute the quaternion derivative measured by the gyroscope
    const Quaternion SEq_dot_omega = 0.5f * SEq_hat * Quaternion(0.0f, wx, wy, wz);

    // Compute then integrate the estimated quaternion derivative
    SEq_hat += (SEq_dot_omega - (beta * SEq_hat_dot)) * sampleRate;

    // Normalize the output quaternion
    SEq_hat.normalize();
}
