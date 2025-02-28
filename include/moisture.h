#ifndef __MOISTURE_H__
#define __ MOISTURE_H__

#include <Arduino.h>
#include <stdint.h>

const int dry_value = 2700;
const int water_value = 1040;

class Moisture {
 private:
  int pin;
  int voltage_for_sensor_pin;

 public:
  Moisture(int pin, int voltage_for_sensor_pin);
  Moisture();
  ~Moisture();
  int read();
  bool status();
  void init(int pin, int voltage_for_sensor_pin);
};

#endif  //__MOISTURE_H__
