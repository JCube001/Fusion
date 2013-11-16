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

#include "quaternion.h"

namespace fusion {

/**
 * @brief Swap the states between two quaternions.
 *
 * @param q0 The first quaternion.
 * @param q1 The quaternion to swap with.
 */
void swap(Quaternion& q0, Quaternion& q1) {
  Quaternion temp;

  // Set temp equal to the state of q0.
  temp.data_[0] = q0.data_[0];
  temp.data_[1] = q0.data_[1];
  temp.data_[2] = q0.data_[2];
  temp.data_[3] = q0.data_[3];

  // Set q0 equal to the state of q1.
  q0.data_[0] = q1.data_[0];
  q0.data_[1] = q1.data_[1];
  q0.data_[2] = q1.data_[2];
  q0.data_[3] = q1.data_[3];

  // Set q1 equal to the state of temp.
  q1.data_[0] = temp.data_[0];
  q1.data_[1] = temp.data_[1];
  q1.data_[2] = temp.data_[2];
  q1.data_[3] = temp.data_[3];
}

}  // namespace fusion
