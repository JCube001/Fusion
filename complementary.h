#ifndef _COMPLEMENTARY_H
#define _COMPLEMENTARY_H

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
  float _alpha;      // The percentage of gyroscope data to use
  float _deltaTime;  // The time in seconds since the last good sensor reading
};

#endif
