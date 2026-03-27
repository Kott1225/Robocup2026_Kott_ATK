#define MAIN_CODE
//define TEST_CODE
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
#include "drive.h"

drive mt1;
void setup()
{
    Serial.begin(9600);
    mt1.init(1);
}

void loop()
{
    mt1.drive_4omnitranslate(80, 0, 0);
    delay(10);
}
#endif