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
#define MD3 0 // NO INPUT ON STARTUP !!
#define MD4 2 // NO INPUT ON STARTUP !!, Blaue LED
#define MD5 14
#define MD6 12
#define MD7 13
#define MD8 15 // NO INPUT ON STARTUP !!
#define MD9 3
#define MA0 A0
#define MTX 1
#define MRX 3

//// RobotPins ////
// IR
#define IRSensorPinFR MD8
#define IRSensorPinFL MD7
#define IRSensorPinBR MD6
#define IRSensorPinBL MD5
// Motor
#define MotorPinLDir MD4
#define MotorPinLSpeed MD3
#define MotorPinRDir MD2
#define MotorPinRSpeed MD1
// LED
#define LEDPin 0 // Pin D0

int RobotNumber = 1;
String hostname ="robot" + String(RobotNumber);

int MotorMode = 0;
boolean Power = false;

void Debug(String name,String value) {
  Serial.print(name);
  Serial.print(":");
  Serial.print(value);
  Serial.print("\t");
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("");
  Serial.println("BeerPong Robot " + String(RobotNumber));
  Serial.println(D0);
  //LEDSetup();
  WlanSetup();
  SensorSetup();
  MotorSetup();
  LEDSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("");
  SensorLoop();
  WlanLoop();
  delay(1000);
}

void(* resetFunc) (void) = 0;
