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
 * @note See http://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=2&ved=0CDEQFjAB&url=http%3A%2F%2Fsharenet-wii-motion-trac.googlecode.com%2Ffiles%2FAn_efficient_orientation_filter_for_inertial_and_inertialmagnetic_sensor_arrays.pdf&ei=bml6Utf5OsTiyAHnzICIBA&usg=AFQjCNEBfCip2CAVZhCKjxP1HYvVvWruYw&sig2=nlrT60sY1wPnCxDvpEipRw&bvm=bv.55980276,d.aWc&cad=rja
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
   * @param dt The sample rate.
   *
   * @note If dt is zero or a negative number, then no delta time is set and
   *       update() will not run.
   */
  void deltaTime(float dt);

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
