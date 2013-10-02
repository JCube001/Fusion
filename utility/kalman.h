#ifndef _KALMAN_H
#define _KALMAN_H

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "filter.h"

class KalmanFilter : public Filter {
};

class KalmanExtendedFilter : public KalmanFilter {
};

#endif
