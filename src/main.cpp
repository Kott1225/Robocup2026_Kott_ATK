#define MAIN_CODE
//#define TEST_CODE
//#define CALIBRATION

#ifdef MAIN_CODE
#include <Arduino.h>
#include "robot.h"

// センサのピンの値は仮だ!!!
int pin_IRsensor[6] = {A1, A2, A3, A4, A5, A0};
int pin_LINEsensor[4] = {A6, A8, A9, A7};
robot Rb1(pin_IRsensor, pin_LINEsensor, 1);

void setup()
{
    Rb1.init();
}

void loop()
{
    Rb1.control();
    delay(10);
}

#endif

#ifdef TEST_CODE
#include <Arduino.h>

int pins[6] = {A0, A1, A2, A3, A4, A5};

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    for(int i= 0; i < 6; i++)
    {
        Serial.print(analogRead(pins[i]));
        Serial.print("\t");
    }
    Serial.println("\t");
}
#endif