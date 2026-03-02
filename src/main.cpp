#include <Arduino.h>
#include "robot.h"

//センサのピンの値は仮だ!!!
int pin_IRsensor[6] = {A0, A1, A2, A3, A4, A5};
int pin_LINEsensor[4] = {A6, A7, A8, A9};
robot Rb1(pin_IRsensor, pin_LINEsensor, 1);

void setup()
{
    Rb1.init();
}

void loop()
{
    Rb1.control();
}