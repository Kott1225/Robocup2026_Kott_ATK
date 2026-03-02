
#include "Arduino.h"
#include "drive.h"

String MOTA::turn(int id_1, int id_2, int id_3, int id_4, int id_5, int id_6) {

  String m1;
  String m2;
  String m3;
  String m4;
  String m5;
  String m6;

  // 0
  // 正
  // 負
  // 100
  //////////
  ////////
  if (id_1 == 0) {
    m1.concat("1F000");
  }
  else if (id_1 >= 1)
  {
    if ((id_1 >= 1) && (id_1 <= 9))
    {
      m1.concat("1F00");
      m1.concat(abs(id_1));
    }
    else if ((id_1 >= 10) && (id_1 <= 99))
    {
      m1.concat("1F0");
      m1.concat(abs(id_1));
    }
    else if (id_1 == 100)
    {
      m1.concat("1F100");
    }
  }
  else if (id_1 <= -1)
  {
    if ((id_1 >= -9) && (id_1 <= -1))
    {
      m1.concat("1R00");
      m1.concat(abs(id_1));
    }
    else if ((id_1 >= -99) && (id_1 <= -10))
    {
      m1.concat("1R0");
      m1.concat(abs(id_1));
    }
    else if (id_1 == -100)
    {
      m1.concat("1R100");
    }
  }
  ///////////
  if (id_2 == 0) {
    m2.concat("2F000");
  }
  else if (id_2 >= 1)
  {
    if ((id_2 >= 1) && (id_2 <= 9))
    {
      m2.concat("2F00");
      m2.concat(abs(id_2));
    }
    else if ((id_2 >= 10) && (id_2 <= 99))
    {
      m2.concat("2F0");
      m2.concat(abs(id_2));
    }
    else if (id_2 == 100)
    {
      m2.concat("2F100");
    }
  }
  else if (id_2 <= -1)
  {
    if ((id_2 >= -9) && (id_2 <= -1))
    {
      m2.concat("2R00");
      m2.concat(abs(id_2));
    }
    else if ((id_2 >= -99) && (id_2 <= -10))
    {
      m2.concat("2R0");
      m2.concat(abs(id_2));
    }
    else if (id_2 == -100)
    {
      m2.concat("2R100");
    }
  }
  ///////////
  if (id_3 == 0) {
    m3.concat("3F000");
  }
  else if (id_3 >= 1)
  {
    if ((id_3 >= 1) && (id_3 <= 9))
    {
      m3.concat("3F00");
      m3.concat(abs(id_3));
    }
    else if ((id_3 >= 10) && (id_3 <= 99))
    {
      m3.concat("3F0");
      m3.concat(abs(id_3));
    }
    else if (id_3 == 100)
    {
      m3.concat("3F100");
    }
  }
  else if (id_3 <= -1)
  {
    if ((id_3 >= -9) && (id_3 <= -1))
    {
      m3.concat("3R00");
      m3.concat(abs(id_3));
    }
    else if ((id_3 >= -99) && (id_3 <= -10))
    {
      m3.concat("3R0");
      m3.concat(abs(id_3));
    }
    else if (id_3 == -100)
    {
      m3.concat("3R100");
    }
  }
  ///////////
  if (id_4 == 0) {
    m4.concat("4F000");
  }
  else if (id_4 >= 1)
  {
    if ((id_4 >= 1) && (id_4 <= 9))
    {
      m4.concat("4F00");
      m4.concat(abs(id_4));
    }
    else if ((id_4 >= 10) && (id_4 <= 99))
    {
      m4.concat("4F0");
      m4.concat(abs(id_4));
    }
    else if (id_4 == 100)
    {
      m4.concat("4F100");
    }
  }
  else if (id_4 <= -1)
  {
    if ((id_4 >= -9) && (id_4 <= -1))
    {
      m4.concat("4R00");
      m4.concat(abs(id_4));
    }
    else if ((id_4 >= -99) && (id_4 <= -10))
    {
      m4.concat("4R0");
      m4.concat(abs(id_4));
    }
    else if (id_4 == -100)
    {
      m4.concat("4R100");
    }
  }
  ///////////
  if (id_5 == 0) {
    m5.concat("5F000");
  }
  else if (id_5 >= 1)
  {
    if ((id_5 >= 1) && (id_5 <= 9))
    {
      m5.concat("5F00");
      m5.concat(abs(id_5));
    }
    else if ((id_5 >= 10) && (id_5 <= 99))
    {
      m5.concat("5F0");
      m5.concat(abs(id_5));
    }
    else if (id_5 == 100)
    {
      m5.concat("5F100");
    }
  }
  else if (id_5 <= -1)
  {
    if ((id_5 >= -9) && (id_5 <= -1))
    {
      m5.concat("5R00");
      m5.concat(abs(id_5));
    }
    else if ((id_5 >= -99) && (id_5 <= -10))
    {
      m5.concat("5R0");
      m5.concat(abs(id_5));
    }
    else if (id_5 == -100)
    {
      m5.concat("5R100");
    }
  }
  ///////////
  if (id_6 == 0) {
    m6.concat("6F000");
  }
  else if (id_6 >= 1)
  {
    if ((id_6 >= 1) && (id_6 <= 9))
    {
      m6.concat("6F00");
      m6.concat(abs(id_6));
    }
    else if ((id_6 >= 10) && (id_6 <= 99))
    {
      m6.concat("6F0");
      m6.concat(abs(id_6));
    }
    else if (id_6 == 100)
    {
      m6.concat("6F100");
    }
  }
  else if (id_6 <= -1)
  {
    if ((id_6 >= -9) && (id_6 <= -1))
    {
      m6.concat("6R00");
      m6.concat(abs(id_6));
    }
    else if ((id_6 >= -99) && (id_6 <= -10))
    {
      m6.concat("6R0");
      m6.concat(abs(id_6));
    }
    else if (id_6 == -100)
    {
      m6.concat("6R100");
    }
  }
  return m1 + m2 + m3 + m4 + m5 + m6;
}





void MOTA::Setup(int i)
{
  serial_id = i;
  if (serial_id == 0) {
    Serial.begin(19200);
  } else if (serial_id == 1) {
    Serial1.begin(19200);
  } else if (serial_id == 2) {
    Serial2.begin(19200);
  } else if (serial_id == 3) {
    Serial3.begin(19200);
  }
}
