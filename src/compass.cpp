#include <Arduino.h>
#include "compass.h"


void Compass::init()
{
    bno = Adafruit_BNO055(55, 0x28);
    targetHeading = 0.0;
    if (!bno.begin())
    {
        Serial.println("DSR1603 not found");
        while (1)
            ;
    }
    // IMUモードに明示的に設定
    bno.setExtCrystalUse(true);
    delay(1000); // 安定化待ち
}

float Compass::getRawHeading()
{
    bno.getEvent(&event);
    return event.orientation.x;
}

float Compass::getError()
{
    float diff = getRawHeading();

    // 角度の正規化（-180度〜180度の範囲に変換）
    while (diff > 180)
        diff -= 360;
    while (diff < -180)
        diff += 360;

    return diff;
}