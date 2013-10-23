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

boolean paused = false;
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
  
  if (paused) {
    textAlign(CENTER, TOP);
    text("PAUSED", width / 2, 10);
  }
}

/**
 * @brief Processing key press event method.
 */
void keyPressed() {
  switch (key) {
  case 'p':
  case 'P':
    paused = !paused;
    break;
  default:
    break;
  }
  
  redraw();
}

/**
 * @brief Processing serial event method. Input must be a string
 *        of four floats seperated by only a comma. A newline
 *        character marks the end of each message. This method has
 *        the side effect of storing the quaternion.
 */
void serialEvent(Serial port) {
  // If paused, then do not act on serial events.
  if (paused) {
    return;
  }
  
  // Retrieve and store data, then draw.
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
 * @brief Draws a cube according to stored Euler angles. Uses a
 *        left handed coordinate system.
 *
 * @note Euler angles should be updated before calling this method.
 */
void drawRotationCube() {
  pushMatrix();
  translate(width / 2, height / 2, 0);
  strokeWeight(2);
  
  // Set the rotation for the entire cube.
  // TODO(JCube001): Test if this works.
  rotateX(euler[0]);
  rotateY(euler[1]);
  rotateZ(euler[2]);
  
  // Cube
  stroke(0, 153, 153);
  fill(0, 153, 153, 200);
  box(100);
  
  // Get ready to draw all axes.
  fill(255);
  
  // X axis (phi or roll).
  stroke(255, 0, 0);
  line(0, 0, -100, 0, 0, 100);
  pushMatrix();
  translate(0, 0, -100);
  box(10);
  popMatrix();
  
  // Y axis (theta or pitch).
  stroke(0, 255, 0);
  line(-100, 0, 0, 100, 0, 0);
  pushMatrix();
  translate(-100, 0, 0);
  box(10);
  popMatrix();
  
  // Z axis (psi or yaw).
  stroke(0, 0, 255);
  line(0, -100, 0, 0, 100, 0);
  pushMatrix();
  translate(0, -100, 0);
  box(10);
  popMatrix();
  
  popMatrix();
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
 * @param q The unit quaternion to convert.
 * @return An array of size three which contains the converted
 *         Euler angles in radians. The format of the array is
 *         [phi, theta, psi].
 *
 * @note All angles are in radians.
 * @note The quaternion for input must be a unit quaternion.
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
