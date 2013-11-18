/**
This sketch can help the user to determine a gyroscope's baseline
error reading as well as the bias (drift rate) observed during
operation.

Note: For this to work the gyroscope must remain completely
motionless.

Note: All outputs angle readings are in radians.
*/

#include <Wire.h>
#include <Adafruit_L3GD20.h>

unsigned long time_now = 0;
unsigned long time_last = 0;

float roll = 0.0f;
float pitch = 0.0f;
float yaw = 0.0f;

float mean = 0.0f;

// Sensors (modify for your sensors as needed)
Adafruit_L3GD20 gyro;

void setup() {
  Serial.begin(9600);
  
  // Sensor setup
  if (!gyro.begin(gyro.L3DS20_RANGE_250DPS)) {
    Serial.println("L3GD20 (gyro) failed to initialize!");
    while (true);
  }
  
  // Give the system time to warm up
  delay(5000);
  
  // Run the baseline test many times to get a good average
  for (int i = 0; i < 1000; i++) {
    // Get the reading from the gyro as the baseline error
    gyro.read();
    roll  = gyro.data.x * L3GD20_DPS_TO_RADS;
    pitch = gyro.data.y * L3GD20_DPS_TO_RADS;
    yaw   = gyro.data.z * L3GD20_DPS_TO_RADS;
    
    // Accumulate for the mean calculation
    mean += (roll + pitch + yaw) / 3.0f;
  }
  
  // Print the baseline error
  Serial.print("Mean error: ");
  printFloat(fabs(mean / 1000.0f), 6);
  Serial.println(" rad/s");
  
  // Reset the mean to zero
  mean = 0.0f;
  
  // Loop through accumulating drift to find the bias
  for (int i = 0; i < 1000; i++) {
    float delta_time;
    float prev_mean;
    
    // Retrieve sensor data
    gyro.read();
    
    // Get the time of when data was read
    time_now = millis();
    
    // Determine the difference between this time to the time of
    // the last sensor reading in seconds
    delta_time = (time_now - time_last) / 1000.0f;
    time_last = time_now;
    
    // Integrate measurements
    roll  += gyro.data.x * L3GD20_DPS_TO_RADS * delta_time;
    pitch += gyro.data.y * L3GD20_DPS_TO_RADS * delta_time;
    yaw   += gyro.data.z * L3GD20_DPS_TO_RADS * delta_time;
    
    // Accumulate for the mean calculation
    prev_mean = mean;
    mean += (roll + pitch + yaw) / 3.0f;
    mean -= prev_mean;
    
    // Pseudo sample rate
    delay(10);
  }
  
  // Print out the bias
  Serial.print("Mean bias: ");
  printFloat(fabs(mean / 1000.0f), 6);
  Serial.println(" rad/s/s");
  
  // Bye
  Serial.println("Finished");
}

void loop() {
  // Do nothing
}

void printFloat(float n, int places) {
  int integer;
  float decimals;
  
  // Check if n is negative
  // Print a minus sign and convert n to a positive value if it is
  if (n < 0.0f) {
    n = fabs(n);
    Serial.print('-');
  }
  
  // Print the integer component and a decimal point character
  integer = (int)floor(n);
  decimals = n - integer;
  Serial.print(integer); Serial.print('.');
  
  // Print the decimal place components
  for (int i = 0; i < places; i++) {
    decimals *= 10.0f;
    integer = (int)floor(decimals);
    decimals -= integer;
    Serial.print(integer);
  }
}
