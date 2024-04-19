#ifndef __PRINT_STATUS__
#define __PRINT_STATUS__

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

void init_display();

void print_checking();

void print_status(int pos, String name, int humid, bool status);

void print_no_water();

#endif  // !__PRINT_STATUS__