/*
#include <Arduino.h>
#include "drive.h"
#include <SoftwareSerial.h>

MOTA motor;
SoftwareSerial motorserial(2, 3);

void setup() {
  Serial.begin(19200);
  Serial1.begin(19200);
}

void loop() {
  String motorstate = motor.turn(100, 100, 100, 100, 100, 100);
  Serial1.println(motorstate);
  delay(50);
}
*/
#include <Arduino.h>