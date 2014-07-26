# Fusion Library

Arduino library for performing orientation sensor fusion on either 6DoF or
9DoF systems. The Madgwick algorithms were used to implement these filters.

## Install

1.  Download the zip archive of this library.
2.  Unzip and move the folder into your Arduino libraries folder.
3.  Rename the folder you just moved to Fusion.

## Usage

Include the header of the filter you wish to use, either imu_filter.h or
marg_filter.h. Set the filter gains and the sample rate. To pass new sensor
readings to the filter, use the update() function. Orientation is computed as
a quaternion. This orientation can be either retrieved directly or it can be
converted to either Euler angles or an axis-angle. Note that all angular values
will be in radians.

See the provided examples for information on which objects and functions to
use. A Processing sketch is also included which can be used to help you verify
that the Fusion library is setup and working correctly on your system.

