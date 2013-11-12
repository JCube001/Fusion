/*******************************************************************************
This example shows how to use the Complementary Filter.

The following sensors were used in this example. Note that communication is set
to occur over I2C.
Gyroscope: http://www.adafruit.com/products/1032
Accelerometer + Magnetometer: http://www.adafruit.com/products/1120

The data being printed out is formatted for use with the Processing sketch
located in Fusion/processing/Orientation/Orientation.pde.
*******************************************************************************/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_L3GD20.h>
#include <Adafruit_LSM303.h>
#include <fusion.h>

unsigned long time_now = 0;
unsigned long time_last = 0;

// Sensors (modify for your sensors as needed)
Adafruit_L3GD20 gyro;
Adafruit_LSM303_Accel accel(54321);
Adafruit_LSM303_Mag mag(12345);

// The filter we will use
fusion::ComplementaryFilter filter;

void setup() {
  Serial.begin(9600);
  
  // Sensor setup (modify for your sensors as needed)
  if (!gyro.begin(gyro.L3DS20_RANGE_250DPS)) {
    Serial.println("L3GD20 (gyro) failed to initialize!");
    while (true);
  }
  
  if(!accel.begin())
  {
    Serial.println("LSM303 (accel) failed to initialize!");
    while (true);
  }
  
  if(!mag.begin())
  {
    Serial.println("LSM303 (mag) failed to initialize!");
    while (true);
  }
  
  delay(10);
}

void loop() {
  sensors_event_t accel_event, mag_event;
  
  // Retrieve sensor data (modify for your sensors as needed)
  gyro.read();
  accel.getEvent(&accel_event);
  mag.getEvent(&mag_event);
  
  // Get the time of when data was read
  time_now = millis();
  
  // Determine the difference between this time to the time of the last sensor
  // reading, then convert to seconds
  filter.deltaTime((float)(time_now - time_last) / 1000.0f);
  time_last = time_now;
  
  // Store sensor data (again, modify input values as needed)
  // Note also that the gyroscope input must be in radians per second
  filter.accelerometer(accel_event.acceleration.x,
                       accel_event.acceleration.y,
                       accel_event.acceleration.z);
  
  filter.gyroscope(gyro.data.x * L3GD20_DPS_TO_RADS,
                   gyro.data.y * L3GD20_DPS_TO_RADS,
                   gyro.data.z * L3GD20_DPS_TO_RADS);
  
  filter.magnetometer(mag_event.magnetic.x,
                      mag_event.magnetic.y,
                      mag_event.magnetic.z);
  
  // Process the sensor data
  filter.update();
  
  // Send out the now up-to-date quaternion
  Serial.print(filter.orientation.w()); Serial.print(',');
  Serial.print(filter.orientation.x()); Serial.print(',');
  Serial.print(filter.orientation.y()); Serial.print(',');
  Serial.print(filter.orientation.z()); Serial.print(',');
  Serial.println();
  
  // Do not print out too fast
  delay(50);
}
