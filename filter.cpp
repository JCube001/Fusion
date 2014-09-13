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
 * @file  filter.cpp
 * @brief Filter implementation.
 */

#include <math.h>
#include "filter.h"

const Quaternion Filter::Eg_hat = Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

/**
 * @brief   Default constructor.
 * @details Initializes the filter to a known state.
 */
Filter::Filter() :
    SEq_hat(Quaternion()),
    beta(1.0f),
    sampleRate(0.0f)
{
}

/**
 * @brief   Destructor.
 * @details This is an abstract destructor which prevents this class from being
 *          used directly.
 */
Filter::~Filter()
{
}

/**
 * @brief   Gets the current estimated orientation.
 * @details Gets the orientation which was most recently computed in a filter
 *          update.
 *
 * @return The most current estimated orientation quaternion.
 */
Quaternion Filter::orientation() const
{
    return SEq_hat;
}

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
void Filter::setGyroErrorGain(const float error)
{
    beta = sqrt(3.0f / 4.0f) * error;
}

/**
 * @brief   Sets the sample rate.
 * @details Sets the sample rate the filter will operate at. This can also be
 *          the change in time since the last filter update was run.
 * @pre     The @p rate should be greater than zero, otherwise this function
 *          does nothing.
 */
void Filter::setSampleRate(const float rate)
{
    if (rate > 0.0f)
    {
        sampleRate = rate;
    }
}
