/******************************************************************
Displays an animation of the rotation encountered by an external
IMU. Accepts input as a quaternion packed as comma seperated
values (CSV) in a string. Each value is a float component of the
quaternion. A single newline character delimits each message.
Serial communication is used to read input.
******************************************************************/

import processing.serial.*;

// Change these to reflect your serial configuration.
final int BAUDRATE = 9600;
final String PORTNAME = "/dev/ttyACM0";

float[] quaternion = {0.0f, 0.0f, 0.0f, 0.0f};
float[] euler = {0.0f, 0.0f, 0.0f};
Serial port;

/**
 * @brief Processing setup method.
 */
void setup() {
  size(500, 400, P3D);
  
  // Text setup.
  PFont font = loadFont("SansSerif.plain-48.vlw");
  textFont(font, 18);
  
  // Serial port setup.
  port = new Serial(this, PORTNAME, BAUDRATE);
  port.clear();
  port.bufferUntil('\n');
  
  // Only draw when an event occurs.
  noLoop();
}

/**
 * @brief Processing draw method.
 */
void draw() {
  String orientation;
  
  background(0);
  fill(255);
  
  // Update global information.
  euler = quaternionToEulerAngles(quaternion);
  
  // Draw all elements.
  drawRotationCube();
  drawUnitCircles();
  
  // Display data as human readable text.
  orientation = "Quaternion\nW: " + quaternion[0] + "\nX: " +
    quaternion[1] + "\nY: " + quaternion[2] + "\nZ: " +
    quaternion[3];
  textAlign(LEFT, TOP);
  text(orientation, 10, 10);
  
  orientation = "Euler Angles\nPhi: " + euler[0] + "\nTheta: " +
    euler[1] + "\nPsi: " + euler[2];
  textAlign(RIGHT, TOP);
  text(orientation, width - 10, 10);
}

/**
 * @brief Processing serial event method. Input must be a string
 *        of four floats seperated by only a comma. A newline
 *        character marks the end of each message. This method has
 *        the side effect of storing the quaternion.
 *
 * @note Overridden.
 */
void serialEvent(Serial port) {
  try {
    String buffer = port.readString();
    String[] input = splitTokens(buffer, ",");
    
    for (int i = 0; i < input.length; i++) {
      quaternion[i] = float(input[i]);
    }
    
    redraw();
  } catch (Exception e) {
    println("Error while reading serial port: ");
    println(e);
  }
}

/**
 * @brief Draws a cube according to stored Euler angles.
 *
 * @note Euler angles should be updated before calling this method.
 */
void drawRotationCube() {
  // TODO(JCube001): Implement!
}

/**
 * @brief Draws circles which have a line showing the amount of
 *        rotation.
 *
 * @note Euler angles should be updated before calling this method.
 */
void drawUnitCircles() {
  // TODO(JCube001): Implement!
}

/**
 * @brief Converts a quaternion to Euler angles.
 *
 * @param q The quaternion to convert.
 * @return An array of size three which contains the converted
 *         Euler angles in radians. The format of the array is
 *         [phi, theta, psi].
 *
 * @note All angles are in radians.
 */
float[] quaternionToEulerAngles(final float[] q) {
  float[] e = new float[3];
  
  e[0] = atan2(2.0f*(q[0]*q[1] + q[2]*q[3]),
               1.0f - 2.0f*(q[1]*q[1] + q[2]*q[2]));
  e[1] = asin(2.0f*(q[0]*q[2] - q[3]*q[1]));
  e[2] = atan2(2.0f*(q[0]*q[3] + q[1]*q[2]),
               1.0f - 2.0f*(q[2]*q[2] + q[3]*q[3]));
  
  return e;
}
