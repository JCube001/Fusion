/*******************************************************************************
The MIT License (MIT)

Copyright (c) 2013 JCube001

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

#if 0

#ifndef COMPLEMENTARY_H_
#define COMPLEMENTARY_H_

#include <math.h>
#include "filter.h"

namespace fusion {

/**
 * @brief Complementary filter. Weighs data from the gyroscope sensor frame
 *        against data from the accelerometer earth and sensor frames and
 *        optionally, the magnetometer earth and sensor frames. All data is
 *        processed as quaternions. Magnetic distortion compensation and
 *        gyroscope bias drift compensation are also accounted for.
 *
 * @see http://www.x-io.co.uk/res/doc/madgwick_internal_report.pdf
 * @see https://github.com/xioTechnologies/Open-Source-AHRS-With-x-IMU/
 */
class ComplementaryFilter : public Filter {
 public:
  /**
   * @brief Default constructor.
   */
  ComplementaryFilter();

  /**
   * @brief Destructor.
   */
  ~ComplementaryFilter();

  /**
   * @brief Sets the sample rate.
   *
   * @param rate The sample rate.
   *
   * @note If rate is zero or a negative number, then no delta time is set and
   *       update() will not run.
   */
  void setSampleRate(float rate);

  /**
   * @brief Sets the beta filter gain using the known value for error.
   *
   * @note Input must be in radians per second.
   */
  void setGyroscopeError(float error);

  /**
   * @brief Sets the zeta filter gain using the known value for bias.
   *
   * @note Input must be in radians per second squared.
   */
  void setGyroscopeDrift(float drift);

  /**
   * @brief The complementary filter algorithm. This implementation can handle
   *        both IMU (6 DoF) and MARG (9 DoF) Attitude and Heading Reference
   *        Systems (AHRS). This is accomplished by checking to see which
   *        values were stored in the filter for each sensor prior to update()
   *        being called.
   */
  virtual void update();

 protected:
  float beta_;          /**< Gyroscope error filter gain. */
  float zeta_;          /**< Gyroscope drift filter gain. */
  float delta_time_;    /**< Sample rate. */
  Quaternion Eb_hat_;   /**< Reference direction of flux in earth frame. */
  Quaternion SEq_hat_;  /**< Estimated orientation */
};

}  // namespace fusion

#endif  // COMPLEMENTARY_H_

#endif // Enable/disable
