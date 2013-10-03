#ifndef _FILTER_H
#define _FILTER_H

#include <math.h>

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "quaternion.h"

#define RAD_TO_DEG  (180.0 / PI)

class Filter {
public:
  Filter(void);
  
  void setAccelXYZ(const float x, const float y, const float z);
  void setCompassXYZ(const float x, const float y, const float z);
  void setGyroXYZ(const float x, const float y, const float z);
  
  virtual void process(void) = 0;
  
protected:
  float _accelData[3];
  float _compassData[3];
  float _gyroData[3];
};

#endif
