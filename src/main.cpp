/*
           ESP32 WROOM
  _______________________________
 |  PIN  |  Function              |
 |-------|------------------------|
 |  36 |  Humidity Sensor 0  (A0) |
 |  39 |  Humidity Sensor 1  (A3) |
 |  34 |  Humidity Sensor 2  (A6) |
 |  35 |  Humidity Sensor 3  (A7) |
 |  4  |  Relay 1 (pump)          |
 |  16 |  Relay 2 (pump)          |
 |  17 |  Relay 3 (pump)          |
 |  5  |  Relay 4 (pump)          |
 |  11 |  Water sensor bottom     |
 |  10 |  Water sensor top        |
 |  9  |  Water sensor reservoir  |
 |  22 |  SCL                     |
 |  21 |  SDA                     |
 |  25 |  POWER_SENSOR0           |
 |  26 |  POWER_SENSOR1           |
 |  27 |  POWER_SENSOR2           |
 |  14 |  POWER_SENSOR3           |
 ---------------------------------
 */

#include <Arduino.h>

#if defined(ESP8266)
#include <ESP8266WiFi.h>  //ESP8266 Core WiFi Library
#else
#include <WiFi.h>  //ESP32 Core WiFi Library
#endif
#if defined(ESP8266)
#include <ESP8266WebServer.h>  //Local WebServer used to serve the configuration portal
#else
#include <WebServer.h>  //Local DNS Server used for redirecting all requests to the configuration portal
#endif

#include <DNSServer.h>  //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>

#include "garden.h"
#include "print_status.h"

#define CHECK_PERIOD 600  // 600 = 10min
// pins to connect  moisture sensors
#define SENSOR0 A0  // GPIO36
#define SENSOR1 A3  // GPIO39
#define SENSOR2 A6  // GPIO34
#define SENSOR3 A7  // GPIO35
#define POWER_SENSOR0 25
#define POWER_SENSOR1 26
#define POWER_SENSOR2 27
#define POWER_SENSOR3 14
// #define MUX_ENABLE 33
#define RELAY1 4
#define RELAY2 16
#define RELAY3 17
#define RELAY4 5
#define WATER_SENSOR_PIN 11
#define WATER_SENSOR_PIN_TOP 10
#define RESERVOIR_SENSOR_PIN 9

hw_timer_t *timer1 = NULL;
uint16_t min10 = 0;
bool disable_system;
Pump reservoir_pump;
// Create teh objects
Garden garden;
String plant1 = "Plant1";
String plant2 = "Plant2";
String plant3 = "Plant3";
String plant4 = "Plant4";

void IRAM_ATTR check_status() {
  //
  // Serial.println("Interrupt 1 sec called");
  Serial.print(min10);
  // check water level in the container
  // zero if there is water in the deposit
  if (!digitalRead(WATER_SENSOR_PIN)) {
    disable_system = false;
    Serial.println(" Water in the deposit");
  } else {
    disable_system = true;
    Serial.println(" No water in the deposit");
  }

  garden.checkPump();

  min10++;
}

bool refill_the_tank() {
  // we are here because the water for the pumps is over
  // check if there is water in the reservoir, returs one if there is
  // no water remining, so turn of the pump
  if (!digitalRead(RESERVOIR_SENSOR_PIN)) {
    reservoir_pump.turnOff();
  } else {
    // check if the reservoir pump is on
    if (reservoir_pump.status()) {
      // if it is ON check if thas fill the deposit
      if (!digitalRead(WATER_SENSOR_PIN_TOP)) {
        // deposit is full, turn off the pump
        reservoir_pump.turnOff();
        return true;
      }
    } else {
      // it is off, start filling the deposit
      reservoir_pump.turnOn();
    }
  }
  return false;
}

void inint_timers() {
  // number of timer, prescalar value, true count up
  timer1 = timerBegin(0, 80, true);
  timerAttachInterrupt(timer1, &check_status, true);
  //   1000000 = 1 seg - units are microseconds
  // 600000000 = 10 min
  timerAlarmWrite(timer1, 1000000, true);
  timerAlarmEnable(timer1);
}

void init_wifi() {
  // Create a wifiManager instance
  WiFiManager wm;
  // Remove comments to reset configuration
  // wifiManager.resetSettings();

  // Create AP portal and check if connected
  if (!wm.autoConnect("ESPRiego")) {
    Serial.println("Fail connecting (timeout)");
    ESP.restart();
    delay(1000);
  }
  Serial.println("Connection succesful");
}

void init_garden() {
  // Analog pin, digital pin to relay, humidity threshold, seconds on
  garden.addPlant(plant1, A0, POWER_SENSOR0, RELAY1, 30, 10);
  garden.addPlant(plant2, A3, POWER_SENSOR1, RELAY2, 30, 10);
  garden.addPlant(plant3, A7, POWER_SENSOR2, RELAY3, 30, 10);
  garden.addPlant(plant4, A19, POWER_SENSOR3, RELAY4, 30, 10);
}

void init_gpio() {
  disable_system = false;
  // Set the pin where the water container sensor will be connected
  pinMode(WATER_SENSOR_PIN, INPUT_PULLUP);
}

void init_pump() { reservoir_pump.init(RESERVOIR_SENSOR_PIN); }

void setup() {
  Serial.begin(115200);

  inint_timers();

  init_gpio();

  init_wifi();

  init_garden();
  init_pump();

  init_display();

  check_status();
}

void loop() {
  if ((min10 >= CHECK_PERIOD) && !disable_system) {
    min10 = 0;
    Serial.println("Check plants");
    print_checking();
    // check humidity and turn pump if required.
    garden.checkPlants();
  }

  if (disable_system) {
    // if system is disable, means there are not water in the container
    // will try to refill it
    disable_system = refill_the_tank();
  }

  if (disable_system) {
    print_no_water();
  } else {
    plant_status_t p;
    p = garden.getStatus(plant1);
    print_status(0, plant1, p.humidity, p.pump_status);
    p = garden.getStatus(plant2);
    print_status(1, plant2, p.humidity, p.pump_status);
    p = garden.getStatus(plant3);
    print_status(2, plant3, p.humidity, p.pump_status);
    p = garden.getStatus(plant4);
    print_status(3, plant4, p.humidity, p.pump_status);
  }

  delay(2000);
}
