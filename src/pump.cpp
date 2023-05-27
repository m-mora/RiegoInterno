#include "pump.h"

#include <Arduino.h>

/**
 * @brief Initialize the array with the pin associated to each relay
 *
 * @param num          Number of relays used
 * @param ...          Pin where is attached.
 * @return bool        True on success.
 */

bool Pump::init(int pin) {
  this->pump_pin = pin;
  return true;
}

bool Pump::turnOn() {
  // Only one pump should be on at the time
  if (!pump_on) {
    Serial.printf("pin = %d is ON\n", pump_pin);
    pump_on = true;
    return true;
  }
  return false;
}

bool Pump::turnOff() {
  if (ON) {
    Serial.printf("Turning pin %d off\n", pump_pin);
    pump_on = false;
    return true;
  }
}

bool Pump::status() { return this->pump_on; }
