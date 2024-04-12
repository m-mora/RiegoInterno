#include "pump.h"

#include <Arduino.h>

/**
 * @brief Initialize the array with the pin associated to each relay
 *
 * @param pin          Pin where is attached.
 * @return bool        True on success.
 */

bool Pump::init(int pin) {
  this->pump_pin = pin;
  pinMode(pin, OUTPUT);
  pump_on = false;
  return true;
}

bool Pump::turnOn() {
  // Only one pump should be on at the time
  if (!pump_on) {
    Serial.printf("pin = %d is ON\n", pump_pin);
    digitalWrite(pump_pin, HIGH);
    pump_on = true;
    return true;
  }
  return false;
}

bool Pump::turnOff() {
  if (pump_on) {
    Serial.printf("Turning pin %d off\n", pump_pin);
    digitalWrite(pump_pin, LOW);
    pump_on = false;
    return true;
  }
  return false;
}

bool Pump::status() { return this->pump_on; }
