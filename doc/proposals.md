# Proposals

Work that may or may not make it into the library.

## Filter.h - Add 10DOF and 11DOF

### Reasoning

We should have a robust and complete sensor fusion library. This should include
the ability to track where the sensors are relative to the surface of the Earth
as well as their orientation.

Information that will be added to the system will include airspeed, altitude,
temperature, latitude, longitude, GPS speed, and GPS altitude.

### Code

```C++
class Filter {
 public:
  typedef enum DOF {
    6DOF, 9DOF, 10DOF, 11DOF
  };
 
  /**
   * @brief Store anemometer data.
   *
   * @param p The fluid pressure value which represents airspeed.
   * @param t Either the external or the sensor temprature.
   */
  void anemometer(const float p, const float t);
  
  /**
   * @brief Store barometer data.
   *
   * @param p The fluid pressure value which represents altitude.
   * @param t Either the external or the sensor temprature.
   */
  void barometer(const float p, const float t);
  
  /**
   * @brief Store Global Positioning System (GPS) data.
   *
   * @param lat The latitude the GPS module is at.
   * @param lon The longitude the GPS module is at.
   * @param alt The altitude the GPS module is at.
   * @param spd The speed the GPS module is traveling at.
   */
  void gps(const float lat, const float lon, const float alt, const float spd);

 protected:
  // 10DOF: Fluid pressure and temperature; speed and altitude.
  float _anemometerData[2];
  float _barometerData[2];
  float _thermometerData;
  
  // 11DOF: Location on Earth; latitude, longitude, another altitude and another
  // speed all in that order.
  float _gpsData[4];
};
```
