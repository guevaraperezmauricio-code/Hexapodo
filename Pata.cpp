#include "Pata.h"

Pata::Pata(int h, int v, ServoController* sc)
  : servoHorizontal(h), servoVertical(v), servoCtrl(sc) {}

void Pata::levantar(int angulo) {
  servoCtrl->mover(servoVertical, angulo);
}

void Pata::moverHorizontal(int angulo) {
  servoCtrl->mover(servoHorizontal, angulo);
}
