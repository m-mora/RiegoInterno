#include "moisture.h"
// #include "include/moisture.h"
#include <Arduino.h>

#include <cstdlib>

Moisture::Moisture(int pin, int v_pin) {
  this->pin = pin;
  this->v_pin = v_pin;
  pinMode(v_pin, OUTPUT);
}

Moisture::Moisture() {}

Moisture::~Moisture() {}

int Moisture::read() {
  int mapped;
  digitalWrite(v_pin, HIGH);
  delay(10);
  int value_read = analogRead(pin);
  digitalWrite(v_pin, LOW);
  int constrained_value = constrain(value_read, water_value, dry_value);
  mapped = map(constrained_value, dry_value, water_value, 0, 100);
  Serial.printf("humidity %d \n", mapped);
  //  return value_read;
  return mapped;
}

void Moisture::init(int pin, int v_pin) {
  this->pin = pin;
  this->v_pin = v_pin;
  pinMode(v_pin, OUTPUT);
}

bool Moisture::status() { return digitalRead(pin); }