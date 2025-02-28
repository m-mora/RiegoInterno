#include "pump.h"

#include <Arduino.h>

/**
 * @brief Initialize the array with the pin associated to each relay
 *
 * @param pin          Pin where the pump is attached.
 */

void Pump::init(int pin)
{
  this->pump_pin = pin;
  pinMode(pin, OUTPUT);
  pump_on = false;
}

void Pump::turnOn()
{
  Serial.printf("pin = %d is ON\n", pump_pin);
  digitalWrite(pump_pin, HIGH);
  pump_on = true;
}

void Pump::turnOff()
{
  Serial.printf("Turning pin %d off\n", pump_pin);
  digitalWrite(pump_pin, LOW);
  pump_on = false;
}

bool Pump::status() { return this->pump_on; }
