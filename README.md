# Fusion Library

Arduino library for performing orientation sensor fusion on either 6DoF or 9DoF systems. The filters implemented in this library are all a type of complementary filter. These filters integrate sensor data with an estimated orientation computed from the previous update in order to cancel errors and produce an updated orientation estimate. These types of filters are quick to execute but they are not quite as accurate nor as stable as a [Kalman filter](https://en.wikipedia.org/wiki/Kalman_filter).

## Install

1.  Download the zip archive of this library.
2.  Unzip and move the folder into your Arduino libraries folder.
3.  Rename the folder you just moved to `Fusion`.

## Usage

In your sketch, include the header of the filter you wish to use. Either `imu_filter.h` for 6DoF systems or `marg_filter.h` for 9DoF systems. Set the filter gains and the sample rate. To pass new sensor readings to the filter, use the `update()` function. Orientation is computed as a [quaternion](https://en.wikipedia.org/wiki/Quaternion). Orientation can be either retrieved directly or it can be converted to either Euler angles or an axis-angle. Note, all angular values will be in radians.

See the provided examples for information on which objects and functions to use. The examples were designed run on an Arduino connected to a [LSM9DS0](https://www.st.com/en/mems-and-sensors/lsm9ds0.html) MEMS sensor over I2C. A [Processing](https://processing.org/) sketch is also included which can be used to help you verify the Fusion library is setup and working correctly on your system.
