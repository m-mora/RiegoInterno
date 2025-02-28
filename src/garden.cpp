#include "garden.h"

#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;

Garden::Garden() {
  root = nullptr;
  this->any_pump_is_on = false;
}

/*
 * @brief create a plant
 * @param name        Name of the plant
 * @param pin         pin where the analog/humidity sensor is connected
 * @param v_pin       pin where the voltage for the sensor is connected
 * @param relay       pin where the relay/pump is connected
 * @param threshold   humidity percentage to triger the irrigation
 * @param duration    duration in second to leave the pump on
 */
void Garden::addPlant(String name, int pin, int v_pin, int relay, int threshold,
                      int duration) {
  plantSet *newNode = new plantSet();
  newNode->Moisture::init(pin, v_pin);
  newNode->Pump::init(relay);
  newNode->duration = duration * 600000;  // stored in miliseconds
  newNode->threshold = threshold;
  newNode->name = name;
  newNode->next = nullptr;

  if (root == nullptr) {
    root = newNode;
  } else {
    plantSet *temp = root;
    while (temp->next != nullptr) {
      temp = temp->next;
    }
    temp->next = newNode;
  }
}

void Garden::checkPlants() {
  plantSet *temp = root;
  while (temp != nullptr) {
    Serial.println("Check...");
    temp->check();
    temp = temp->next;
  }
}

void Garden::checkPump() {
  plantSet *temp = root;
  while (temp != nullptr) {
    temp->check_pump();
    temp = temp->next;
  }
}

plant_status_t Garden::getStatus(String name) {
  plantSet *temp = root;
  plant_status_t p_status;
  p_status.humidity = 0;
  p_status.pump_status = 0;
  while (temp != nullptr) {
    if (temp->name != name) {
      temp = temp->next;
      continue;
    }
    p_status.humidity = temp->humidity;
    p_status.pump_status = temp->Pump::status();
    break;
  }
  return p_status;
}