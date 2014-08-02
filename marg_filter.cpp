/*******************************************************************************
The MIT License (MIT)

Copyright (c) 2013, 2014 JCube001

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
*******************************************************************************/

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
    
    // Compute the magnetic flux in the earth frame
    const Quaternion Eh_hat = SEq_hat * Sm_hat * SEq_hat.conjugate();

    // Normalize the magnetic flux vector to have only x and z components
    Eb_hat = Quaternion(0.0f, sqrt((Eh_hat.x * Eh_hat.x) + (Eh_hat.y * Eh_hat.y)), 0.0f, Eh_hat.z);

    // Compute the gravity objective function
    const Quaternion f_g = SEq_hat.conjugate() * Eg_hat * SEq_hat
            - Quaternion(0.0f, ax, ay, az).normalized();

    // Compute the gravity Jacobian matrix
    // TODO

    // Compute the magnetic field objective function
    const Quaternion Sm_hat = Quaternion(0.0f, mx, my, mz).normalized();
    const Quaternion f_b = SEq_hat.conjugate() * Eb_hat * SEq_hat - Sm_hat;

    // Compute the magnetic field Jacobian matrix
    // TODO

    // Compute the normalized gradient descent (matrix multiplication)
    // TODO
    const Quaternion SEq_hat_dot =
            Quaternion().normalized;

    // Compute the angular estimated direction of gyroscope error then compute
    // and remove the gyroscope biases while computing the quaternion
    // derivative measured by the gyroscope
    Sw_b += zeta * (two_SEq.conjugate() * SEq_hat_dot) * deltaTime;
    const Quaternion SEq_dot_omega = 0.5f * SEq_hat * (Quaternion(0.0f, wx, wy, wz) - Sw_b);

    // Compute then integrate the estimated quaternion derivative
    SEq_hat += (SEq_dot_omega - (beta * SEq_hat_dot)) * deltaTime;

    // Normalize the output quaternion
    SEq_hat.normalize();
}

