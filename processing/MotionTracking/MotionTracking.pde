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
*******************************************************************************/

import processing.serial.*;

Quaternion quat;

void setup() {
  size(640, 480, P3D);
  background(0);
  ortho();
  
  noLoop();
}

void draw() {
  background(0);
  
  // Draw everything
  drawLocationGrid();
}

void drawBuoy() {
}

void drawLocationGrid() {
  pushMatrix();
  translate(width / 2, height / 2, 0);
  
  rotateX(-PI / 6);
  rotateY(PI / 3);
  
  fill(0);
  stroke(255);
  strokeWeight(5);
  line(-100000, 0, 0, 100000, 0, 0);
  line(0, -100000, 0, 0, 100000, 0);
  line(0, 0, -100000, 0, 0, 100000);
  
  popMatrix();
}
