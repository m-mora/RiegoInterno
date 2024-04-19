#include "print_status.h"

// Liquid crystal
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x3F, 20, 4);
// Character definitions
byte pump_on[] = {0x04, 0x0E, 0x15, 0x04, 0x04, 0x04, 0x04, 0x04};
byte pump_off[] = {0x00, 0x00, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x00};

void init_display() {
  // Wire.begin();
  // scan_i2c();
  // Liquid Crystal
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, pump_on);
  lcd.createChar(1, pump_off);
}

void print_checking() {
  lcd.clear();
  lcd.setCursor(2, 1);
  lcd.printstr("Checking plants");
  lcd.setCursor(3, 2);
  lcd.print("In progress...");
}

void print_status(int pos, String name, int humid, bool status) {
  if (pos == 0) {
    lcd.clear();
  }
  lcd.blink_off();
  lcd.setCursor(0, pos);
  lcd.print(name);
  lcd.setCursor(8, pos);
  lcd.print(humid);
  lcd.print("%");
  lcd.setCursor(14, pos);
  lcd.print("Pump ");
  if (status) {
    lcd.write(0);
  } else {
    lcd.write(1);
  }
}

void print_no_water() {
  lcd.clear();
  lcd.setCursor(9, 1);
  lcd.blink_on();
  lcd.print("NO");
  lcd.setCursor(5, 2);
  lcd.print("** WATER **");
}
