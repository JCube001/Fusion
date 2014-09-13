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

Filter::Filter() :
    SEq_hat(Quaternion()),
    beta(1.0f),
    sampleRate(0.0f)
{
}

Filter::~Filter()
{
}

Quaternion Filter::orientation() const
{
    return SEq_hat;
}

void Filter::setGyroErrorGain(const float error)
{
    beta = sqrt(3.0f / 4.0f) * error;
}

void Filter::setSampleRate(const float rate)
{
    if (rate > 0.0f)
    {
        sampleRate = rate;
    }
}
