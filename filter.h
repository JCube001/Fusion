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
 * @file   filter.h
 * @brief  Abstract class for creating orientation filters.
 */

#ifndef FILTER_H
#define FILTER_H

#include <quaternion.h>

/**
 * @brief   Filter class.
 * @details Abstract class for creating more complex orientation filter
 *          classes.
 */
class Filter
{
public:
    /**
     * @brief   Default constructor.
     * @details Initializes the filter to a known state.
     */
    Filter();

    /**
     * @brief   Destructor.
     * @details This is an abstract destructor which prevents this class from
     *          being used directly.
     */
    virtual ~Filter() = 0;

    /**
     * @brief   Gets the current estimated orientation.
     * @details Gets the orientation which was most recently computed in a
     *          filter update.
     *
     * @return The most current estimated orientation quaternion.
     */
    Quaternion orientation() const;

    /**
     * @brief   Sets the gyroscope error gain.
     * @details Sets the beta filter gain. This gain represents all mean zero
     *          gyroscope measurement errors, expressed as the magnitude of a
     *          quaternion derivative.
     * @f[
     *   \beta = \sqrt{\frac{3}{4}} \tilde{\omega}_\beta
     * @f]
     *
     * @param[in] error The gyroscope error rate in rad/s.
     */
    void setGyroErrorGain(const float error);

    /**
     * @brief   Sets the sample rate.
     * @details Sets the sample rate the filter will operate at. This can also
     *          be the change in time since the last filter update was run.
     * @pre     The @p rate should be greater than zero, otherwise this
     *          function does nothing.
     */
    void setSampleRate(const float rate);

protected:
    static const Quaternion Eg_hat; /**< Direction of gravity in the earth
                                         frame */
    Quaternion SEq_hat;             /**< Estimated orientation */
    float beta;                     /**< Filter gain which represents all
                                         mean zero gyroscope measurement
                                         errors */
    float sampleRate;               /**< Rate at which the filter is to be
                                         updated */
};

#endif // FILTER_H
