#ifndef _COMPLEMENTARY_H
#define _COMPLEMENTARY_H

#include <math.h>

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "filter.h"

class ComplementaryFilter : public Filter {
public:
  typedef struct eulerAngles_s {
    float roll;
    float pitch;
    float yaw;
  } eulerAngles;
  
  // Output angles (degrees)
  eulerAngles angle;
  
  ComplementaryFilter(void);
  
  void setAlpha(const float a);
  void setDeltaTime(const float dt);
  
  void process(void);

protected:
  // The percentage of gyroscope data to use
  float alpha;
  
  // The time in seconds since the last good sensor reading
  float deltaTime;
  
  // Choose between 6 and 9 DoF
  bool findYaw;
};

#endif
