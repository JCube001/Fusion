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

#include "./filter.h"

/**
 * @brief Complementary filter. Weighs data from the gyroscope against data
 *        from the accelerometer in order to produce a reading of a
 *        rotation orientation with little error.
 *
 * @note  Using a gyroscope and an accelerometer only yields pitch and roll
 *        (6DOF). A magnetometer must also be used in order to determine yaw
 *        (9DOF).
 */
class ComplementaryFilter : public Filter {
 public:
  /**
   * @brief Default constructor.
   */
  ComplementaryFilter();
  
  /**
   * @brief Initialization constructor.
   *
   * @param d The Degrees Of Freedom (DOF) to use.
   * @param a A number between 0 and 1 which represents the weight to give
   *          the gyroscope data relative to other sensor data.
   */
  ComplementaryFilter(const DOF d, const float a);
  
  /**
   * @brief Destructor.
   */
  ~ComplementaryFilter();

  /**
   * @brief Set the alpha value.
   *
   * @param a A number between 0 and 1 which represents the weight to give
   *          the gyroscope data relative to other sensor data.
   *
   * @note Does nothing if the input is out of range.
   */
  void alpha(const float a);
  
  /**
   * @brief Set the delta time.
   *
   * @param dt The time in seconds since the last sensor reading.
   *
   * @note Sets the delta time to zero if the input is negative or also zero.
   */
  void deltaTime(const float dt);

  /**
   * @brief The complementary filter algorithm.
   */
  void process();

 protected:
  float _alpha;      ///< The percentage of gyroscope data to use.
  float _deltaTime;  ///< The time in seconds since the last sensor reading.
};

#endif  // COMPLEMENTARY_H_
