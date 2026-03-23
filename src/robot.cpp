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

    // IRセンサ値をベクター合成で角度計算
    float max_ratio = -1.0;
    float sum_x = 0.0;
    float sum_y = 0.0;
    float ratio_sum = 0.0;

    for (int j = 0; j < 6; j++)
    {
        float raw = analogRead(IRpins[j]);
        float ratio = raw / max_IRstates[j];
        if (ratio > 1.0) ratio = 1.0;
        IRstates[j] = ratio;

        Serial.print(ratio);
        Serial.print("\t");

        if (ratio > max_ratio)
        {
            max_ratio = ratio;
            ball_posit = j; // センサ番号 0..5
        }

        float angle_rad = j * 60.0 * PI / 180.0; // ラジアンに変換
        sum_x += ratio * cos(angle_rad);
        sum_y += ratio * sin(angle_rad);
        ratio_sum += ratio;
    }

    float current_angle;
    if (ratio_sum > 0.0)
    {
        // ベクター合成角度
        float vector_angle_rad = atan2(sum_y, sum_x);
        current_angle = vector_angle_rad * 180.0 / PI; // 度に変換
        if (current_angle < 0) current_angle += 360.0; // 0-360範囲
    }
    else
    {
        current_angle = 0.0; // デフォルト
    }

    Serial.print(max_ratio);
    Serial.print("\t");
    Serial.println(current_angle);
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
        mt.drive_4omnitranslate(speed, current_angle, gain * cp1.getError() * (100.0 / 180.0));
    }
}