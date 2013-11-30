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
long frame = 0;
float[] euler = {0.0f, 0.0f, 0.0f};
Quaternion quat = new Quaternion();
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
  try {
    port = new Serial(this, PORTNAME, BAUDRATE);
    port.clear();
    port.bufferUntil('\n');
  } catch (Exception e) {
    testing = true;
    println(e);
  }
  
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
    quat = convertFromEulerAngles(euler);
  } else {
    euler = convertToEulerAngles(quat);
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
  
  orientation = "Quaternion\nW: " + quat.w() + "\nX: " + quat.x() +
    "\nY: " + quat.y() + "\nZ: " + quat.z();
  textAlign(LEFT, TOP);
  text(orientation, 10, 10);
  
  orientation = String.format(
    "Euler Angles\nDegrees\nPhi: %.3f\nTheta: %.3f\nPsi: %.3f",
    degrees(euler[0]), degrees(euler[1]), degrees(euler[2]));
  textAlign(RIGHT, TOP);
  text(orientation, width - 10, 10);
  
  textAlign(CENTER, TOP);
  if (testing) {
    text("TEST MODE", width / 2, 10);
  } else if (paused) {
    text("PAUSED", width / 2, 10);
  } else {
    text(String.format("Frame\n%d", ++frame), width / 2, 10);
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
        euler[1] += radians(1.0f);
      }
      break;
    case DOWN:
      if (testing) {
        euler[1] -= radians(1.0f);
      }
      break;
    case LEFT:
      if (testing) {
        euler[0] -= radians(1.0f);
      }
      break;
    case RIGHT:
      if (testing) {
        euler[0] += radians(1.0f);
      }
      break;
    default:
      break;
    }
    break;
  case '<':
  case ',':
    if (testing) {
      euler[2] += radians(1.0f);
    }
    break;
  case '>':
  case '.':
    if (testing) {
      euler[2] -= radians(1.0f);
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
    euler = new float[] {0.0f, 0.0f, 0.0f};
    quat = new Quaternion();
    try {
      port.clear();
    } catch (Exception e) {
      // Port not available.
    }
    break;
  case 'p':
  case 'P':
    // Toggle serial input paused.
    paused = !paused;
    try {
      port.clear();
    } catch (Exception e) {
      // Port not available.
    }
    break;
  case 'H':
  case 'h':
    // Return to home position.
    euler = new float[] {0.0f, 0.0f, 0.0f};
    quat = new Quaternion();
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
    quat.set(
      float(input[0]),
      float(input[1]),
      float(input[2]),
      float(input[3]));
    redraw();
  } catch (Exception e) {
    println(e);
  }
}

/**
 * @brief Draws a cube according to the stored quaternion. Uses a
 *        left handed coordinate system.
 */
void drawRotationCube() {
  float[] aa = new float[4];
  
  pushMatrix();
  translate(width / 2, height / 2, 0);
  strokeWeight(2);
  
  // Set the rotation for the entire cube.
  aa = convertToAxisAngle(quat);
  rotate(aa[0], aa[2], aa[3], aa[1]);
  
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
  translate(100, 0, 0);
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
