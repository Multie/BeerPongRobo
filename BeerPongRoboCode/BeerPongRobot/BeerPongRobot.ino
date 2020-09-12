#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#include <FastLED.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>
#include <EEPROM.h>

// MD Pins
#define MD0 16
#define MD1 5
#define MD2 4
#define MD3 0 // NO INPUT ON STARTUP, Pull-Up!!
#define MD4 2 // NO INPUT ON STARTUP  Pull-Up!!, Blaue LED
#define MD5 14
#define MD6 12
#define MD7 13
#define MD8 15 // NO INPUT ON STARTUP Pull-Down !!
#define MD9 3
#define MA0 A0
#define MTX 1
#define MRX 3

//// RobotPins ////
// IR
#define IRSensorPinFR MD5
#define IRSensorPinFL MD6
#define IRSensorPinBR MD7
#define IRSensorPinBL MD0
// Motor
#define MotorPinLDir MD4
#define MotorPinLSpeed MD3
#define MotorPinRDir MD2
#define MotorPinRSpeed MD1
// LED
#define LEDPinNodeMCU 8 // Pin D8
#define LEDPin MD8
// Debug
#define DEBUG
//#define WIFIDEBUG
#define SENSORDEBUG
//#define MOTORDEBUG
//#define LEDDEBUG


bool debugprint = false;
bool Unblock() {
   //LEDLoop();
   WlanLoop();
   SensorLoop();
   if (debugprint) {
    Serial.println("");
   }
}


void Debug(String name,String value) {
  Serial.print(name);
  Serial.print(":");
  Serial.print(value);
  Serial.print("\t");
  debugprint = true;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("");
  Serial.println(D0);
  randomSeed(analogRead(MA0));

  //LEDSetup();
  WlanSetup();
  SensorSetup();
  MotorSetup();

}

void loop() {
  // put your main code here, to run repeatedly:
  MotorLoop();
  Unblock();
}

void(* resetFunc) (void) = 0;
