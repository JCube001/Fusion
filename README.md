# Fusion Library

Under heavy development.

Arduino library for performing digital sensor fusion using various filter
implementations.

## Filters

* Complementary
* Kalman
* Extended Kalman

Quaternions will also be used with all of the filters. (Eventually)

## Install

1.  Download the zip archive of this library.
2.  Unzip and move the folder into your Arduino libraries folder.
3.  Rename the folder you just moved to Fusion.
4.  Done!

## Usage

All you will need to include in your Arduino sketch is the fusion.h header file.
You may then instantiate and use a filter. The following is an example of this.

```C++
#include <fusion.h>

ComplementaryFilter filter;
```

More information coming as soon as the filter interface is finalized.

## Testing

The Google C++ unit testing framework
[gtest](http://code.google.com/p/googletest/) is used to help develop this
library.

## TODO

* Redo the quaternion library header using Vector3 to help store information.
* Unit tests for Vector3 and Quaternion.
* Unit tests for all filters.
* Should look into supporting multiple different degrees of freedom.
* Find a good way to run unit tests on everything.
* Add Direction Cosine Matrix (DCM) to the mix.
