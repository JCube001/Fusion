# Fusion Library

Under heavy development.

Arduino library for performing digital sensor fusion using various filter
implementations.

## Filters

* Complementary
* Kalman
* Extended Kalman

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

fusion::ComplementaryFilter filter;
```

More information coming as soon as the filter interface is finalized.

## Testing

The [Google Testing](http://code.google.com/p/googletest/) framework for C++
unit tests is used to help develop this library.

If you would like to run the tests yourself, you will need the package
libgtest-dev. The following script should be enough to create the tests.

```Bash
sudo apt-get install libgtest-dev
cd test
make
```

## TODO

* Finish writing all of the filters.
* Unit tests for all filters.
* Flight test.
