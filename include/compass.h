#ifndef COMPASS_H
#define COMPASS_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

/**
 * @brief コンパスモジュールDSR1603を扱い相対角度を得る
 */
class Compass
{
private:
    Adafruit_BNO055 bno;
    float targetHeading;
    sensors_event_t event;

public:
    /**
     * @brief コンストラクタ：アドレス値の代入
     */
    Compass();

    /**
     * @brief センサーの初期化
     */
    void init();

    /**
     * @brief 現在の角度を取得 (0.0 ~ 359.9)
     * @return (float）現在の初期位置からずれた角度（0.0 ~ 359.9）
     */
    float getRawHeading();

    /**
     * @brief 目標角度（0度）からのズレを計算
     * @note 最短経路（-180 ~ 180）で返す
     * @return (float)現在の初期位置から補正すべき角度（-180 ~ 180）
     */
    float getError();
};

#endif