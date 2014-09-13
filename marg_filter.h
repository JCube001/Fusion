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
 * @file  marg_filter.h
 * @brief Magnetic, Angular Rate and Gravity (MARG) filter class.
 */

#ifndef MARG_FILTER_H
#define MARG_FILTER_H

#include "filter.h"

/**
 * @brief   MARG filter.
 * @details Filter for computing an orientation using a system that has nine
 *          degrees of freedom (9DoF). Such a system is comprised of a
 *          gyroscope, an accelerometer and a magnetometer.
 */
class MARGFilter : public Filter
{
public:
    MARGFilter();
    void setGyroDriftGain(const float drift);
    void update(float wx, float wy, float wz,
                float ax, float ay, float az,
                float mx, float my, float mz);

private:
    Quaternion Eb_hat; /**< Normalized magnetic flux in the earth frame */
    Quaternion Sw_b;   /**< The angular estimated direction of gyroscope
                            error */
    float zeta;        /**< Filter gain which represents the rate of
                            convergence to remove gyroscope measurement error
                            which are not mean zero */
};

#endif // MARG_FILTER_H
