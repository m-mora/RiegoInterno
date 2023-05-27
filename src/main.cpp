#include <Arduino.h>

#include "plants.h"

#define CHECK_PERIOD 600
// pins to connect  moisture sensors
#define SELECT0 4
#define SELECT1 5
#define SELECT2 9
#define SELECT3 10
#define MUX_ENABLE 33

hw_timer_t *timer1 = NULL;
uint16_t min10 = 0;
bool disable_system;

// Create teh objects
Garden garden;

void IRAM_ATTR check_status() {
  //
  Serial.println("Interrupt 1 sec called");
  // check water level in the container
  if (digitalRead(34)) {
    disable_system = false;
  } else {
    disable_system = true;
  }

  min10++;
  if ((min10 == CHECK_PERIOD) && !disable_system) {
    min10 = 0;
    // check humidity and turn pump if required.
    garden.checkPlants();
  }
}

void setup() {
  Serial.begin(115200);
  // number of timer, prescalar value, true count up
  timer1 = timerBegin(0, 80, true);
  timerAttachInterrupt(timer1, &check_status, true);
  //   1000000 = 1 seg - units are microseconds
  // 600000000 = 10 min
  timerAlarmWrite(timer1, 1000000, true);
  timerAlarmEnable(timer1);

  disable_system = false;
  garden.addPlant(A0, 12, 30, 10);
  garden.addPlant(A3, 13, 30, 10);
  garden.addPlant(A7, 14, 30, 10);
  garden.addPlant(A19, 16, 30, 10);
}

void loop() { delay(300); }