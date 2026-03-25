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
    Serial.begin(9600);
    cp1.init();
    mt.init(serial_id);
}

void robot::control()
{
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
    float sum_x = 0.0;
    float sum_y = 0.0;

    for (int j = 0; j < 6; j++)
    {
        float raw = analogRead(IRpins[j]);
        float ratio = raw / max_IRstates[j] * 1000;
        if (ratio > 1000.0)
            ratio = 1000.0;
        IRstates[j] = ratio;

        // ベクター合成: 各センサーの角度を考慮
        float angle_rad = j * 60.0 * PI / 180.0;
        sum_x += ratio * cos(angle_rad);
        sum_y += ratio * sin(angle_rad);
    }

    // ベクター合成から目標角度を計算
    float target_angle = atan2(sum_y, sum_x) * 180.0 / PI;
    if (target_angle < 0) target_angle += 360.0;

    Serial.println(target_angle);

    if (max_line_val > 0.7)
    {
        float line_angle = (lineside * 90 + 180) % 360;
        for (int i = 0; i < 20; i++)
        {
            mt.drive_4omnitranslate(speed, line_angle, gain * cp1.getError() * (100.0 / 180.0));
        }
    }
    else
    {
        // アークを描くアプローチ: 角度に応じた滑らかなオフセットで円弧軌道
        float offset = sin(target_angle * PI / 180.0) * 45.0;  // -45° から +45° の範囲で滑らかに変化
        float final_target_angle = fmod(target_angle + offset + 360.0, 360.0);

        // 走行指令（目標角度＋ゲイン調整）
        mt.drive_4omnitranslate(speed, final_target_angle, gain * cp1.getError() * (100.0 / 180.0));
    }
}

void robot::calibrateIRSensors(unsigned long calibration_time_ms)
{
    // キャリブレーション用の最大値リセット
    float cal_max[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    unsigned long start_time = millis();
    
    Serial.println("=== IR Sensor Calibration Start ===");
    Serial.println("Point all IR sensors at the ball and rotate slowly...");
    Serial.print("Calibration time: ");
    Serial.print(calibration_time_ms);
    Serial.println(" ms");
    Serial.println();
    
    // 指定時間の間センサ値をスキャン
    while (millis() - start_time < calibration_time_ms)
    {
        for (int j = 0; j < 6; j++)
        {
            int raw = analogRead(IRpins[j]);
            if (raw > cal_max[j])
            {
                cal_max[j] = raw;
            }
        }
        
        // 進捗表示 (毎100ms)
        static unsigned long last_print = 0;
        if (millis() - last_print > 100)
        {
            last_print = millis();
            Serial.print(".");
        }
        
        delay(5);
    }
    
    Serial.println();
    Serial.println("=== Calibration Complete ===");
    
    // キャリブレーション値を max_IRstates に設定
    for (int j = 0; j < 6; j++)
    {
        max_IRstates[j] = cal_max[j];
        
        Serial.print("Sensor ");
        Serial.print(j);
        Serial.print(": ");
        Serial.println(max_IRstates[j]);
    }
    
    Serial.println();
}

float robot::getMaxIRValue(int sensor_index)
{
    if (sensor_index < 0 || sensor_index >= 6)
        return 0.0;
    return max_IRstates[sensor_index];
}

void robot::printCalibrationValues()
{
    Serial.println("=== Current Calibration Values ===");
    for (int j = 0; j < 6; j++)
    {
        Serial.print("max_IRstates[");
        Serial.print(j);
        Serial.print("] = ");
        Serial.println(max_IRstates[j]);
    }
    Serial.println();
}