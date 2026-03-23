#include <Arduino.h>
#include "robot.h"

robot::robot(int pinnumber_IRsensors[6], int pinnumber_LINEsensors[4], int Serialnumber)
{
    for (int i = 0; i < 4; i++)
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

void robot::control()
{
    int ball_posit = 0;
    int lineside = 0;

    // ラインセンサの最大値とインデックスを同時に探す
    float max_line_val = -1;
    for (int i = 0; i < 4; i++)
    {
        int val = analogRead(LINEpins[i]);
        LINEstates[i] = val / max_LINEstates[i];
        if (LINEstates[i] > 1)
        {
            LINEstates[i] = 1;
        }
        if (LINEstates[i] > max_line_val)
        {
            max_line_val = LINEstates[i];
            lineside = i;
        }
    }

    // IRセンサの最大値とインデックスを同時に探す
    float max_ir_val = -1;
    for (int j = 0; j < 6; j++)
    {
        float val = analogRead(IRpins[j]);
        IRstates[j] = val / max_IRstates[j];
        Serial.print(IRstates[j]);
        Serial.print("\t");
        if (IRstates[j] > max_ir_val)
        {
            max_ir_val = IRstates[j];
            ball_posit = j;
        }
    }
    Serial.print(max_ir_val);
    Serial.print("\t");
    Serial.println(ball_posit);
    if (max_line_val > 0.7)
    {
        ball_posit = (lineside * 90 + 180) % 360;
        for (int i = 0; i < 20; i++)
        {
            mt.drive_4omnitranslate(speed, ball_posit, gain * cp1.getError() * (100.0 / 180.0));
        }
    }
    else
    {
        ball_posit = ball_posit * 60;
        mt.drive_4omnitranslate(speed, ball_posit, gain * cp1.getError() * (100.0 / 180.0));
    }
}