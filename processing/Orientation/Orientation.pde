/*******************************************************************************
The MIT License (MIT)

Copyright (c) 2013 JCube001

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
********************************************************************************

Orientation

Displays an animation of the rotation encountered by an external
IMU. Accepts input as a quaternion packed as comma seperated
values (CSV) in a string. Each value is a float component of the
quaternion. A single newline character delimits each message.
Serial communication is used to read input.

Controls:
P - Toggle pause for reading input.
H - Return to home position.
T - Enter test mode. Manual control of the rotation enabled.
  UP ARROW - Pitch down.
  DOWN ARROW - Pitch up.
  LEFT ARROW - Roll left.
  RIGHT ARROW - Roll right.
  < - Yaw left.
  > - Yaw right.
*******************************************************************************/

import processing.serial.*;

// Change these to reflect your serial configuration.
final int BAUDRATE = 9600;
final String PORTNAME = "/dev/ttyACM0";

// Global states and storage.
boolean paused = false;
boolean testing = false;
float[] quaternion = {1.0f, 0.0f, 0.0f, 0.0f};
float[] euler = {0.0f, 0.0f, 0.0f};
Serial port;

/**
 * @brief Processing setup method.
 */
void setup() {
  size(500, 400, P3D);
  background(0);
  
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
  
  // Setup drawing.
  background(0);
  
  // Update global information.
  if (testing) {
    quaternion = eulerAnglesToQuaternion(euler);
  } else {
    euler = quaternionToEulerAngles(quaternion);
  }
  
  // Keep Euler angles within the unit circle.
  for (int i = 0; i < euler.length; i++) {
    if (euler[i] >= TWO_PI) {
      euler[i] -= TWO_PI;
    } else if (euler[i] < 0.0f) {
      euler[i] += TWO_PI;
    }
  }
  
  // Draw all elements.
  drawRotationCube();
  drawUnitCircles();
  
  // Display data as human readable text.
  fill(255);
  
  orientation = "Quaternion\nW: " + quaternion[0] + "\nX: " + quaternion[1] +
    "\nY: " + quaternion[2] + "\nZ: " + quaternion[3];
  textAlign(LEFT, TOP);
  text(orientation, 10, 10);
  
  orientation = String.format(
    "Euler Angles\nDegrees\nPhi: %.3f\nTheta: %.3f\nPsi: %.3f",
    degrees(euler[0]), degrees(euler[1]), degrees(euler[2]));
  textAlign(RIGHT, TOP);
  text(orientation, width - 10, 10);
  
  if (testing) {
    textAlign(CENTER, TOP);
    text("TEST MODE", width / 2, 10);
  } else if (paused) {
    textAlign(CENTER, TOP);
    text("PAUSED", width / 2, 10);
  }
}

/**
 * @brief Processing key press event method.
 */
void keyPressed() {
  switch (key) {
  case CODED:
    switch (keyCode) {
    case UP:
      if (testing) {
        euler[1] -= radians(1.0f);
      }
      break;
    case DOWN:
      if (testing) {
        euler[1] += radians(1.0f);
      }
      break;
    case LEFT:
      if (testing) {
        euler[0] += radians(1.0f);
      }
      break;
    case RIGHT:
      if (testing) {
        euler[0] -= radians(1.0f);
      }
      break;
    default:
      break;
    }
    break;
  case '<':
  case ',':
    if (testing) {
      euler[2] -= radians(1.0f);
    }
    break;
  case '>':
  case '.':
    if (testing) {
      euler[2] += radians(1.0f);
    }
    break;
  default:
    break;
  }
  
  redraw();
}

/**
 * @brief Processing key released event.
 */
void keyReleased() {
  switch (key) {
  case 'T':
  case 't':
    // Toggle test mode, also pauses.
    testing = !testing;
    paused = true;
    quaternion = new float[] {1.0f, 0.0f, 0.0f, 0.0f};
    euler = new float[] {0.0f, 0.0f, 0.0f};
    port.clear();
    break;
  case 'p':
  case 'P':
    // Toggle serial input paused.
    paused = !paused;
    port.clear();
    break;
  case 'H':
  case 'h':
    // Return to home position.
    quaternion = new float[] {1.0f, 0.0f, 0.0f, 0.0f};
    euler = new float[] {0.0f, 0.0f, 0.0f};
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
  // If paused or testing, then do not act on serial events.
  if (paused || testing) {
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
  // Remember, 3D rotations are not commutative!
  // TODO Therefore we need additional logic.
  rotateZ(-euler[0]);
  rotateX(-euler[1]);
  rotateY(-euler[2]);
  
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
  pushMatrix();
  translate(width / 2, height - 40);
  strokeWeight(2);
  fill(0, 153, 153, 200);
  
  // X axis rotation.
  pushMatrix();
  translate(-100, 0);
  rotate(-euler[0]);
  stroke(255, 0, 0);
  line(0, 0, 20, 0);
  ellipse(0, 0, 40, 40);
  popMatrix();
  
  // Y axis rotation.
  pushMatrix();
  translate(0, 0);
  rotate(-euler[1]);
  stroke(0, 255, 0);
  line(0, 0, 20, 0);
  ellipse(0, 0, 40, 40);
  popMatrix();
  
  // Z axis rotation.
  pushMatrix();
  translate(100, 0);
  rotate(-euler[2]);
  stroke(0, 0, 255);
  line(0, 0, 20, 0);
  ellipse(0, 0, 40, 40);
  popMatrix();
  
  popMatrix();
}

/**
 * @brief Converts Euler angles to a quaternion.
 *
 * @param e The Euler angles to convert, in radians.
 * @return An array of size four which contains the converted
 *         unit quaternion. The format of the array is
 *         [W, X, Y, Z].
 *
 * @note All angles are in radians.
 */
float[] eulerAnglesToQuaternion(final float[] e) {
  final float t = 0.5f;
  final float cr = cos(e[0] * t);
  final float cp = cos(e[1] * t);
  final float cy = cos(e[2] * t);
  final float sr = sin(e[0] * t);
  final float sp = sin(e[1] * t);
  final float sy = sin(e[2] * t);
  
  float[] q = new float[4];
  
  q[0] = cr*cp*cy + sr*sp*sy;
  q[1] = sr*cp*cy - cr*sp*sy;
  q[2] = cr*sp*cy + sr*cp*sy;
  q[3] = cr*cp*sy - sr*sp*cy;
  
  return q;
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
