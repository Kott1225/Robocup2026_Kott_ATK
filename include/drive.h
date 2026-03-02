#ifndef DRIVE_H
#define DRIVE_H

#include "Arduino.h"

/**
 * @brief モーターモジュールDDK0668Tを用いてモーターを動作させる
 */
class drive
{
private:
  int serial_id;
  int motor_powers[6] = {0, 0, 0, 0, 0, 0};
  float target_direction = 0.0;
  String drivepattern;

public:

  /**
   * @brief モータードライバーの初期設定
   * @param Serialnumber 使用するシリアルの番号（1または2を推奨）
   */
  void init(int Serialnumber);

  /**
   * @brief モータードライバーに接続されている各モーターの回転方向を決定し，モータードライバーに情報を送信する
   * @param id_1 モーター1の回転方向（-100 ~ 100）
   * @param id_2 モーター2の回転方向（-100 ~ 100）
   * @param id_3 モーター3の回転方向（-100 ~ 100）
   * @param id_4 モーター4の回転方向（-100 ~ 100）
   * @param id_5 モーター5の回転方向（-100 ~ 100）
   * @param id_6 モーター6の回転方向（-100 ~ 100）
   */
  void output(int id_1, int id_2, int id_3, int id_4, int id_5, int id_6);

  /**
   * @brief モータードライバーにオムニホイールが4つついていると仮定して，指定した速度と角度方向に並進移動させる
   * @param speed オムニホイールの最大出力に比する速度比（0 ~ 100）
   * @param direction オムニホイールを進行させる角度
   * @param turn コンパスなどで得た，正面に対する角度的誤差
   */
  void drive_4omnitranslate(int speed, float direction, float turn);
  void drive_4omnirotate(float direction);
};

#endif
