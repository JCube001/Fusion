# Fusion Library

Arduino library for performing digital sensor fusion using various filter
implementations.

## Install

1.  Download the zip archive of this library.
2.  Unzip and move the folder into your Arduino libraries folder.
3.  Rename the folder you just moved to Fusion.
4.  Done!

## Usage

All you will need to include in your Arduino sketch is the fusion.h header file.
You may then instantiate and use a filter. The following is an example of this.

```Arduino
#include <fusion.h>

// Any other includes, globals, or objects
// ...

fusion::ComplementaryFilter filter;

// For tracking delta time
unsigned long time_now = 0;
unsigned long time_last = 0;

void setup() {
  Serial.begin(9600);
  
  // Initialize your sensors
  // ...
  
  // Set gyroscope errors if you know them
  filter.setGyroscopeError(error);
  filter.setGyroscopeDrift(drift);
}

void loop() {
  // Read your sensors
  // ...
  
  // Get the time of when data was read
  time_now = millis();
  
  // Determine the difference between this time to the time of the last sensor
  // reading, then convert to seconds
  filter.setSampleRate((float)(time_now - time_last) / 1000.0f);
  time_last = time_now;
  
  // Set the values within the filter
  filter.setAccelerometer(a_x, a_y, a_z);
  filter.setGyroscope(g_x, g_y, g_z);
  filter.setMagnetometer(m_x, m_y, m_z);  // Optional, for 9 DoF systems
  
  // Process the sensor data
  filter.update();
  
  // Handle quaternion output
  Serial.print(filter.orientation.w()); Serial.print(',');
  Serial.print(filter.orientation.x()); Serial.print(',');
  Serial.print(filter.orientation.y()); Serial.print(',');
  Serial.print(filter.orientation.z()); Serial.println();
}
```

Note: All angular values are in radians.

## Testing

The [Google Testing](http://code.google.com/p/googletest/) framework for C++
unit tests is used to help develop this library.

If you would like to run the tests yourself, you will need the package
libgtest-dev. The following script should be enough to create the tests on a
Debian based Linux system.

```Bash
sudo apt-get install libgtest-dev
cd test
make
```

## TODO

* Finish writing all of the filters.
* Unit tests for all filters.
* Flight test.
