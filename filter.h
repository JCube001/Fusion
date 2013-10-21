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

#ifndef FILTER_H_
#define FILTER_H_

#include <math.h>

#if !defined(_FUSION_TEST)
  #if (ARDUINO >= 100)
    #include <Arduino.h>
  #else
    #include <WProgram.h>
  #endif
#endif

#include "./utility/quaternion.h"
#include "./utility/vector.h"

#define DEG_TO_RAD  (M_PI / 180.0f)
#define RAD_TO_DEG  (180.0f / M_PI)

/**
 * @brief Filter. Abstract class for storing sensor readings.
 *
 * @note Any class which inherits this class must implement the method
 *       process(). This is the method which actually performs the sensor
 *       fusion and determines the orientation of the sensors.
 * @note Orientation should be considered as being relative to the plane of the
 *       surface of the Earth.
 */
class Filter {
 public:
  /**
   * @brief Degrees Of Freedom (DOF) supported by the filter.
   */
  typedef enum {
    6DOF, 9DOF
  } DOF;

  /**
   * @brief Structure for storing quaternion orientation.
   */
  typedef struct orientation_s {
    float w;
    float x;
    float y;
    float z;
  } orientation_t;

  /**
   * @brief Default constructor.
   */
  Filter();

  /**
   * @brief DOF Selection constructor.
   *
   * @param d The Degrees Of Freedom (DOF) to use.
   */
  Filter(DOF d);

  /**
   * @brief Destructor.
   */
  ~Filter();

  /**
   * @brief Store triple axis accelerometer data.
   *
   * @param x The x-axis acceleration value.
   * @param y The y-axis acceleration value.
   * @param z The z-axis acceleration value.
   */
  void accelerometerXYZ(const float x, const float y, const float z);

  /**
   * @brief Store triple axis gyroscope data.
   *
   * @param x The x-axis rotation acceleration in radians per second.
   * @param y The y-axis rotation acceleration in radians per second.
   * @param z The z-axis rotation acceleration in radians per second.
   * @note All values are in radians per second.
   */
  void gyroscopeXYZ(const float x, const float y, const float z);

  /**
   * @brief Store triple axis magnetometer data.
   *
   * @param x The x-axis magnetic field strength value.
   * @param y The y-axis magnetic field strength value.
   * @param z The z-axis magnetic field strength value.
   */
  void magnetometerXYZ(const float x, const float y, const float z);

  /**
   * @brief Sensor fusion algorithm interface. Any implementation must store
   *        the resulting rotation orientation in the data member of this
   *        class.
   *
   * @note Must be overridden in all subclasses.
   */
  virtual void process() = 0;

  orientation_t data;  ///< Orientation output (quaternion).

 protected:
  // User selected DOF.
  DOF _dof;
  
  // 6DOF: Pitch and roll.
  Vector3 _accelerometerData;
  Vector3 _gyroscopeData;
  
  // 9DOF: Compass; heading and yaw.
  Vector3 _magnetometerData;
  
  Quaternion _rotation;
};

#endif  // FILTER_H_
