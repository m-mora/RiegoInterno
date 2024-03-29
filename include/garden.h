#ifndef __GARDEN_H__
#define __GARDEN_H__

#include <Arduino.h>

#include "plants.h"


class Garden {
 private:
  plantSet* root;

 public:
  Garden();

  void addPlant(String name, int pin, int relay, int threshold, int duration);
  void checkPlants();
  void checkPump();
  plant_status_t getStatus(String name);
};
#endif // !__GARDEN_H__
#define __GARDEN_H__

