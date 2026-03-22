#include <Arduino.h>
#include "robot.h"

robot::robot(int pinnumber_IRsensors[6], int pinnumber_LINEsensors[4], int Serialnumber)
{
    for (int i = 0; i < 4 ;i++)
    {
        LINEpins[i] = pinnumber_LINEsensors[i];
    }
    for (int j = 0; j < 6; j++)
    {
        IRpins[j] = pinnumber_IRsensors[j];
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

int robot::detect_ball()
{
    int ball_posit = 0;
    int lineside = 0;
    for (int i = 0; i < 4; i++)
    {
        LINEstates[i] = analogRead(LINEpins[i]);
        if (LINEstates[i] > LINEstates[lineside])
        {
            // より大きい値が見つかったらインデックスを更新
            lineside = i;
        }
    }
    for (int j = 0; j < 6; j++)
    {
        IRstates[j] = analogRead(IRpins[j]);
        if (IRstates[j] > IRstates[ball_posit])
        {
            ball_posit = j;
        }
    }
    if (LINEstates[lineside] > 60)
    {
        ball_posit = lineside * 90;
    }
    else
    {
        ball_posit = ball_posit * 90;
    }
    return ball_posit;
}

void robot::control()
{
    // 角度誤差を回転パワーに変換（ゲイン調整）
    float rotation_power = cp1.getError() * 0.5f;  // ゲインは実験的に調整

    mt.drive_4omnitranslate(speed, detect_ball(), rotation_power);
}