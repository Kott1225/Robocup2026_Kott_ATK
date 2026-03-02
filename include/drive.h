
#ifndef DRIVE_H
#define DRIVE_H

#include "Arduino.h"

class MOTA {
  private:
    int serial_id;
  public:
    String turn(int id_1, int id_2, int id_3, int id_4, int id_5, int id_6);
    void Setup(int i);

};

#endif
