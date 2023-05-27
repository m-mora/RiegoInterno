#ifndef __MOISTURE_H__
#define __ MOISTURE_H__

#include <Arduino.h>
#include <stdint.h>

const int dry_value = 2700;
const int water_value = 1040;

class Moisture {
 private:
  int pin;

 public:
  Moisture(int pin);
  Moisture();
  ~Moisture();
  int read();
  void init(int pin);
};

#endif  //__MOISTURE_H__
