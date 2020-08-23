// https://lastminuteengineers.com/sim800l-gsm-module-arduino-tutorial/
// https://elchupanibrei.livejournal.com/53252.html
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "const.h"
#include <SoftwareSerial.h>
// AESLib
// https://github.com/suculent/thinx-aes-lib
#include "AES.h"
// ArduinoJson
#include <ArduinoJson.h>
// Time Timekeeping functionality for Arduino
#include <TimeLib.h>

#define WEMOS_D0     16
#define WEMOS_D1     5
#define WEMOS_D2     4
#define WEMOS_D3     0
#define WEMOS_D4_LED 2
#define WEMOS_D5     14
#define WEMOS_D6     12
#define WEMOS_D7     13
#define WEMOS_D8     15
#define WEMOS_TX     1
#define WEMOS_RX     3

void setup() {
  wemosSetup();
  ledSetup();
  wifiSetup();
  timeSetup();
  dbgSetup();
  simSetup();
}

void loop() {
  srLoop();
  dbgLoop();
  wifiLoop();
  
  simLoop();
  ledBlink(1, 500);
}
