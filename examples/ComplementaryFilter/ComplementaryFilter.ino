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

// Sensors (modify for your sensors as needed)
Adafruit_L3GD20 gyro;
Adafruit_LSM303_Accel accel = Adafruit_LSM303_Accel(54321);
Adafruit_LSM303_Mag mag = Adafruit_LSM303_Mag(12345);

// The filter we will use
fusion::ComplementaryFilter filter;

void setup() {
  Serial.begin(9600);
  
  // Sensor setup (modify for your sensors as needed)
  if (!gyro.begin(gyro.L3DS20_RANGE_250DPS)) {
    Serial.println("L3GD20 failed to initialize!");
    while (1);
  }
  
  if(!accel.begin())
  {
    Serial.println("LSM303 (accel) failed to initialize!");
    while(1);
  }
  
  if(!mag.begin())
  {
    Serial.println("LSM303 (mag) failed to initialize!");
    while(1);
  }
}

void loop() {
  // Retrieve sensor data (modify for your sensors as needed)
  sensors_event_t event; 
  gyro.read();
  
  // Store sensor data (again, modify input values as needed)
  // Note also that the gyroscope input must be in radians per second
  accel.getEvent(&event);
  filter.accelerometer(event.acceleration.x,
                       event.acceleration.y,
                       event.acceleration.z);
  
  filter.gyroscope(gyro.data.x * L3GD20_DPS_TO_RADS,
                   gyro.data.y * L3GD20_DPS_TO_RADS,
                   gyro.data.z * L3GD20_DPS_TO_RADS);
  
  mag.getEvent(&event);
  filter.magnetometer(event.magnetic.x,
                      event.magnetic.y,
                      event.magnetic.z);
  
  // Process the sensor data
  filter.process();
  
  // Send out the now up-to-date quaternion
  Serial.print(filter.data.w); Serial.print(',');
  Serial.print(filter.data.x); Serial.print(',');
  Serial.print(filter.data.y); Serial.print(',');
  Serial.print(filter.data.z); Serial.print(',');
  Serial.println();
  
  // Don't print out too fast
  delay(50);
}
