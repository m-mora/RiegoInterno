#include "moisture.h"
// #include "include/moisture.h"
#include <Arduino.h>

#include <cstdlib>

Moisture::Moisture(int pin) { this->pin = pin; }

Moisture::Moisture() {}

Moisture::~Moisture() {}

int Moisture::read() {
  int mapped;
  int value_read = analogRead(pin);
  int constrained_value = constrain(value_read, water_value, dry_value);
  mapped = map(constrained_value, dry_value, water_value, 0, 100);
  Serial.printf("humidity %d \n", mapped);
  //  return value_read;
  return mapped;
}

void Moisture::init(int pin) { this->pin = pin; }
