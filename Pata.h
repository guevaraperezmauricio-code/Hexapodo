#ifndef PATA_H
#define PATA_H

#include "ServoController.h"

class Pata {
  int servoHorizontal;
  int servoVertical;
  ServoController* servoCtrl;

public:
  Pata(int h, int v, ServoController* sc);
  void levantar(int angulo);
  void moverHorizontal(int angulo);
};

#endif
