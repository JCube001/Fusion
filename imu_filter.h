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
 * @file   imu_filter.h
 * @brief  Inertial measurement unit (IMU) filter class.
 */

#ifndef IMU_FILTER_H
#define IMU_FILTER_H

#include "filter.h"

/**
 * @brief   IMU filter.
 * @details Filter for computing an orientation using a system that has six
 *          degrees of freedom (6DoF). Such a system is comprised of a
 *          gyroscope and an accelerometer.
 */
class IMUFilter : public Filter
{
public:
    IMUFilter();
    void update(float wx, float wy, float wz,
                float ax, float ay, float az);
};

#endif // IMU_FILTER_H
