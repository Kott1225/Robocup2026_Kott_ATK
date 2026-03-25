#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>
#include "compass.h"
#include "drive.h"

class robot
{
private:
    int IRpins[6] = {0, 0, 0, 0, 0, 0};
    int LINEpins[4] = {0, 0, 0, 0};
    int serial_id = 1;
    int speed = 85;

    float direction = 0.0;
    float IRstates[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    float max_IRstates[6] = {1023.0, 1023.0, 1019.0, 1023, 1000.0, 974.0};
    float LINEstates[4] = {0.0, 0.0, 0.0, 0.0};
    float max_LINEstates[4] = {700.0, 800.0, 500.0, 700.0};
    float gain = 1.0;

    Compass cp1;
    drive mt;

public:
    /**
     * @brief コンストラクタ，固定値に対し代入を行う
     * @param pinnumber_IRsensors[4] ボールセンサのピン配列
     * @param pinnumber_LINEsensors[4] ラインセンサのピン配列
     * @param Serialnumber シリアル番号，本回路では1を使用することを推奨する
     */
    robot(int pinnumber_IRsensors[6], int pinnumber_LINEsensors[4], int Serialnumber);

    /**
     * @brief コンパス，モーターモジュールとともに初期化を行う
     */
    void init();
    /**
     * @brief ロボットのコントロールを行う
     */
    void control();
    
    /**
     * @brief IRセンサの自動キャリブレーション (起動時)
     * @param calibration_time_ms キャリブレーション時間 (ミリ秒)
     */
    void calibrateIRSensors(unsigned long calibration_time_ms = 2000);
    
    /**
     * @brief キャリブレーション済みの最大値を取得
     * @param sensor_index センサインデックス (0-5)
     * @return キャリブレーション値
     */
    float getMaxIRValue(int sensor_index);
    
    /**
     * @brief キャリブレーション値を表示 (Serial経由)
     */
    void printCalibrationValues();
};

#endif