/*
#include <Arduino.h>
#include "drive.h"
#include <SoftwareSerial.h>

MOTA motor;
SoftwareSerial motorserial(2, 3);

void setup() {
  Serial.begin(19200);
  Serial1.begin(19200);
}

void loop() {
  String motorstate = motor.turn(100, 100, 100, 100, 100, 100);
  Serial1.println(motorstate);
  delay(50);
}
*/
#include <Arduino.h>
#include <Wire.h>

// DSR1302 (HMC6352) のI2Cアドレス
int compassAddress = 0x42 >> 1; 
int reading = 0; 
void setup() {
  Wire.begin();
  Serial.begin(9600); // シリアルモニタ表示用
  
  // 連続計測モードに設定
  Wire.beginTransmission(compassAddress);
  Wire.write('G');    // RAM書き込みコマンド
  Wire.write(0x74);   // アドレス
  Wire.write(0x72);   // 連続モード設定値
  Wire.endTransmission();
  delayMicroseconds(70);
} 
  
void loop() {
  // 2バイト（角度データ）を要求
  Wire.requestFrom(compassAddress, 2);
  
  if(Wire.available() >= 2){
    // 上位バイトを読み込み、8ビットシフト
    reading = Wire.read() << 8;
    // 下位バイトを合成
    reading += Wire.read();
    
    // 0~3599の値を10で割り、0.0~359.9度に変換
    float degrees = reading / 10.0; 
    
    Serial.print("Heading: ");
    Serial.println(degrees);
  } 
  delay(50); // 20Hzで更新
}
