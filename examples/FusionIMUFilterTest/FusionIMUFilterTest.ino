/*******************************************************************************
This example shows how to use the IMU Filter.

The data being printed out is formatted for use with the Processing sketch
located in Fusion/processing/Orientation/Orientation.pde.
*******************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <SFE_LSM9DS0.h>

// Fusion library includes
#include <imu_filter.h>
#include <quaternion.h>

// Helper macros
#define DPS_TO_RADS(n) (n * 0.017453293f)
#define DEG_TO_RAD(n) (n * (PI / 180.0f))
#define RAD_TO_DEG(n) (n * (180.0f / PI))

// Change these values based on your own gyroscope's error
#define error (0.015074f) // rad/s

// Variables for keeping track of the actual sample rate
unsigned long time_now = 0;
unsigned long time_last = 0;

// Sensors (modify for your sensors as needed)
#define LSM9DS0_XM (0x1D)
#define LSM9DS0_G  (0x6B)
LSM9DS0 imu(MODE_I2C, LSM9DS0_G, LSM9DS0_XM);

// The filter we will use
IMUFilter filter;

void setup() {
  Serial.begin(115200);
  
  // Sensor setup (modify for your sensors as needed)
  if (imu.begin() != 0x49D4)
  {
    while (true);
  }
  
  // Set known error values
  filter.setGyroErrorGain(error);
  
  // Delay startup
  delay(100);
}

void loop() {
  // Retrieve sensor data (modify for your sensors as needed)
  imu.readGyro();
  imu.readAccel();
  
  // Get the time of when data was read
  time_now = millis();
  
  // Disable interrupts for time critical code
  noInterrupts();
  
  // Determine the difference between this time to the time of the last sensor
  // reading, then convert to seconds
  filter.setSampleRate((float)(time_now - time_last) / 1000.0f);
  time_last = time_now;
  
  // Process the sensor data
  filter.update(DPS_TO_RADS(imu.calcGyro(imu.gx)),
                DPS_TO_RADS(imu.calcGyro(imu.gy)),
                DPS_TO_RADS(imu.calcGyro(imu.gz)),
                imu.calcAccel(imu.ax),
                imu.calcAccel(imu.ay),
                imu.calcAccel(imu.az));
  Quaternion q = filter.orientation();
  
  // Reenable interrupts
  interrupts();
  
  // Send out the now up-to-date quaternion
  Serial.print(q.w, 5); Serial.print(',');
  Serial.print(q.x, 5); Serial.print(',');
  Serial.print(q.y, 5); Serial.print(',');
  Serial.print(q.z, 5); Serial.println();
  
  // Sample rate of ~200 Hz
  delay(5);
}
