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
 *
 * @addtogroup marg_filter
 * @{
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
    /**
     * @brief   Default construction.
     * @details Initializes the filter to a known state.
     */
    MARGFilter();

    /**
     * @brief   Sets the gyroscope drift gain.
     * @details Sets the zeta filter gain. This gain represents the rate of
     *          convergence to remove gyroscope measurement error which are
     *          not mean zero. Expressed as the magnitude of a quaternion
     *          derivative.
     *
     * @param[in] drift The drift rate in @f$\text{rad}\over\text{s}^{2}@f$.
     */
    void setGyroDriftGain(const float drift);

    /**
     * @brief   Updates estimated orientation.
     * @details Executes the filter algorithm and updates the estimated
     *          orientation.
     * @pre     The sample rate must be set to a value greater than zero.
     * @pre     The proper units must be used for the input parameters.
     * @post    The estimated orientation is updated.
     *
     * @param[in] wx The gyroscope X axis measurement in
     *               @f$\text{rad}\over\text{s}@f$.
     * @param[in] wy The gyroscope Y axis measurement in
     *               @f$\text{rad}\over\text{s}@f$.
     * @param[in] wz The gyroscope Z axis measurement in
     *               @f$\text{rad}\over\text{s}@f$.
     * @param[in] ax The accelerometer X axis measurement in units of gravity.
     * @param[in] ay The accelerometer Y axis measurement in units of gravity.
     * @param[in] az The accelerometer Z axis measurement in units of gravity.
     * @param[in] mx The magnetometer X axis measurement in units of magnetic
     *               flux.
     * @param[in] my The magnetometer Y axis measurement in units of magnetic
     *               flux.
     * @param[in] mz The magnetometer Z axis measurement in units of magnetic
     *               flux.
     */
    void update(float wx, float wy, float wz,
                float ax, float ay, float az,
                float mx, float my, float mz);

private:
    Quaternion Eb_hat; /**< TODO */
    Quaternion Sw_b;   /**< TODO */
    float zeta;        /**< Filter gain which represents the rate of
                            convergence to remove gyroscope measurement error
                            which are not mean zero */
};

#endif // MARG_FILTER_H

/** @} */
