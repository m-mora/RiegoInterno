#ifndef __PLANTS_H__
#define __PLANTS_H_

#include <Arduino.h>

#include "moisture.h"
#include "pump.h"

class plantSet : public Moisture, public Pump {
 public:
  // moisture humidity;
  // Relays pump;
  int duration;
  int threshold;
  unsigned long time_started;

  plantSet *next;

  plantSet() {
    this->duration = 0;
    this->threshold = 0;
  }

  void check() {
    if (status()) {
      // pump is on, check for time elapsed
      // and turn off if time has passed
      if ((millis() - time_started) >= (duration)) {
        turnOff();
        time_started = 0;
      }
    } else {
      // pump is off, check the humidity to turn it on if required
      if (Moisture::read() < threshold) {
        turnOn();
        time_started = millis();
      }
    }
  }
};

class Garden {
 private:
  plantSet *root;

 public:
  Garden();

  // create a plant
  // pin = pin where the analog/humidity sensor is connected
  // relay - pin where the relay/pump is connected
  // threshold humidity percentage to triger the irrigation
  // duration - duration in second to leave the pump on
  void addPlant(int pin, int relay, int threshold, int duration);
  void checkPlants();
};

#endif  // __PLANTS_H__