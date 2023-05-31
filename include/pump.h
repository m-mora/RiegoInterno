#ifndef __RELAY_H__
#define __RELAY_H__

#include <Arduino.h>

#define ON 1
#define OFF 0
// #define MAX_RELAYS 8

class Pump {
 private:
  bool pump_on;
  uint8_t pump_pin;

 public:
  bool init(int pin);
  bool turnOn();
  bool turnOff();
  bool status();
};

#endif  // !__RELAY_H__