#include "plants.h"

Garden::Garden() { root = nullptr; }

// create a plant
// pin = pin where the analog/humidity sensor is connected
// relay - pin where the relay/pump is connected
// threshold humidity percentage to triger the irrigation
// duration - duration in second to leave the pump on
void Garden::addPlant(int pin, int relay, int threshold, int duration) {
  plantSet *newNode = new plantSet();
  newNode->Moisture::init(pin);
  newNode->Pump::init(relay);
  newNode->duration = duration;
  newNode->threshold = threshold;
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
    temp->check();
    temp = temp->next;
  }
}
