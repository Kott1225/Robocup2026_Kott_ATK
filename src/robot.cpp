#include <Arduino.h>
#include "robot.h"

robot::robot(int pinnumber_IRsensors[6], int pinnumber_LINEsensors[4], int Serialnumber)
{
    for(int i = 0; i < 4; i++)
    {
        IRpins[i] = pinnumber_IRsensors[i];
        LINEpins[i] = pinnumber_LINEsensors[i];
    }
    serial_id = Serialnumber;
}

void robot::init()
{
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
    cp1.init();
    mt.init(serial_id);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
}

void robot::control()
{
    direction = cp1.getError();
    Serial.println(direction);
    mt.output(100, 100, 100, 100, 100, 100);
    delay(50);
}