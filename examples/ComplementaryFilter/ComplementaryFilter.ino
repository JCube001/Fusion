#include <fusion.h>

ComplementaryFilter filter;

void setup() {
  Serial.begin(9600);
  
  // Initialize the filter. More of a safty mechanism to ensure
  // that the user specifies a DoF number.
  filter.init(DOF9);
}

void loop() {
  // Retrieve sensor data (modify for your sensors).
  
  // Store sensor data.
  filter.accelerometerXYZ();
  filter.gyroscopeXYZ();
  filter.magnetometerXYZ();
  
  // Process the sensor data.
  filter.process();
  
  // Send out quaternions.
  Serial.print(filter.data.w); Serial.print(',');
  Serial.print(filter.data.x); Serial.print(',');
  Serial.print(filter.data.y); Serial.print(',');
  Serial.print(filter.data.z); Serial.print(',');
  Serial.println();
}
