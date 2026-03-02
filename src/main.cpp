#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>

// DSR1603 (BNO055) のインスタンス作成。アドレスは通常 0x28
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28);

void setup() {
  Serial.begin(9600);
  
  // センサーの初期化
  if(!bno.begin()) {
    Serial.print("DSR1603が見つかりません。配線を確認してください。");
    while(1);
  }
  
  delay(1000);
  // 外部クリスタルを使用（精度向上のため）
  bno.setExtCrystalUse(true);
}

void loop() {
  // センサーからオイラー角（角度データ）を取得
  sensors_event_t event;
  bno.getEvent(&event);

  // 方位角 (Heading) を表示
  // 0度 = 北, 90度 = 東, 180度 = 南, 270度 = 西
  Serial.print("Heading: ");
  Serial.print(event.orientation.x, 1); // 小数点1位まで
  Serial.println(" degrees");

  delay(100); // 10Hzで更新
}
