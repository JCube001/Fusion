# Fusion Library

Under heavy development.

Arduino library for performing digital sensor fusion using various filter
implementations.

## Filters

* Complementary
* Kalman
* Extended Kalman

Quaternions will also be used with all of the filters. (Eventually)

## TODO

* Redo the quaternion library header using Vector3 to help store information.
* Unit tests for Vector3 and Quaternion.
* Unit tests for all filters.
* Should look into supporting multiple different degrees of freedom.
* Find a good way to run unit tests on everything.
* Add Direction Cosine Matrix (DCM) to the mix.
