#include <Arduino.h>
#include <cstdlib>

#include "moisture.h"


Moisture::Moisture(int pin, int voltage_for_sensor_pin) {
  this->pin = pin;
  this->voltage_for_sensor_pin = voltage_for_sensor_pin;
  pinMode(this->pin, INPUT);
  pinMode(this->voltage_for_sensor_pin, OUTPUT);
}

Moisture::Moisture() {}

Moisture::~Moisture() {}

int Moisture::read() {
  int mapped;
  digitalWrite(this->voltage_for_sensor_pin, HIGH);
  delay(10);
  int value_read = analogRead(pin);
  digitalWrite(this->voltage_for_sensor_pin, LOW);
  int constrained_value = constrain(value_read, water_value, dry_value);
  mapped = map(constrained_value, dry_value, water_value, 0, 100);
  Serial.printf("humidity %d \n", mapped);
  //  return value_read;
  return mapped;
}

void Moisture::init(int pin, int voltage_for_sensor_pin) {
  this->pin = pin;
  this->voltage_for_sensor_pin = voltage_for_sensor_pin;
  pinMode(this->pin, INPUT);
  pinMode(this->voltage_for_sensor_pin, OUTPUT);
}

bool Moisture::status() { return digitalRead(pin); }