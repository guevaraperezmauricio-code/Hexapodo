#ifndef HEXAPODO_H
#define HEXAPODO_H

#include "Pata.h"

class Hexapodo {
  Pata* patas[6];
  ServoController* servoCtrl;

public:
  Hexapodo(ServoController* sc);
  void asignarPata(int index, Pata* pata);
  void pararse();
  void moverA();
  void moverB();
};

#endif
