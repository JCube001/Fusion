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
 *
 * @addtogroup imu_filter
 * @{
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
    /**
     * @brief   Default constructor.
     * @details Initializes the filter to a known state.
     */
    IMUFilter();

    /**
     * @brief   Updates estimated orientation.
     * @details Executes the filter algorithm and updates the estimated
     *          orientation.
     * @pre     The sample rate must be set to a value greater than zero.
     * @pre     The proper units must be used for the input parameters.
     * @post    The estimated orientation is updated.
     *
     * @param[in] wx The gyroscope X axis measurement in rad/s.
     * @param[in] wy The gyroscope Y axis measurement in rad/s.
     * @param[in] wz The gyroscope Z axis measurement in rad/s.
     * @param[in] ax The accelerometer X axis measurement in units of gravity.
     * @param[in] ay The accelerometer Y axis measurement in units of gravity.
     * @param[in] az The accelerometer Z axis measurement in units of gravity.
     */
    void update(float wx, float wy, float wz,
                float ax, float ay, float az);
};

#endif // IMU_FILTER_H

/** @} */
