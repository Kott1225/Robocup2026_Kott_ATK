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
    int speed = 100;

    float direction = 0.0;
    float IRstates[4] = {0.0, 0.0, 0.0, 0.0};
    float max_IRstates[4] = {2000.0, 2000.0, 2000.0, 2000.0};
    float LINEstates[4] = {0.0, 0.0, 0.0, 0.0};
    float max_LINEstates[4] = {2000.0, 2000.0, 2000.0, 2000.0};

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
     * @brief ロボットから見てボールがどこにあるかを検出する．
     * @note すべての赤外線センサーの値を読み取ってしきい値をとり，その後もっとも大きなセンサ値を選び返す
     * @return 一番反応が大きいボールセンサ
     */
    int detect_ball();

    /**
     * @brief ロボットのコントロールを行う
     */
    void control();
};

#endif