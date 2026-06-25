#include "Hexapodo.h"

Hexapodo::Hexapodo(ServoController* sc) : servoCtrl(sc) {}

void Hexapodo::asignarPata(int index, Pata* pata) {
  patas[index] = pata;
}

void Hexapodo::pararse() {
  patas[0]->levantar(145); patas[0]->moverHorizontal(110);
  patas[1]->levantar(145); patas[1]->moverHorizontal(100);
  patas[2]->levantar(140); patas[2]->moverHorizontal(120);
  patas[3]->levantar(145); patas[3]->moverHorizontal(75);
  patas[4]->levantar(145); patas[4]->moverHorizontal(100);
  patas[5]->levantar(145); patas[5]->moverHorizontal(75);
  delay(500);
}

void Hexapodo::moverA() {
  patas[0]->levantar(145); patas[0]->moverHorizontal(80);
  patas[1]->levantar(165); patas[1]->moverHorizontal(150);
  patas[2]->levantar(135); patas[2]->moverHorizontal(100);
  delay(500);
}

void Hexapodo::moverB() {
  patas[3]->levantar(175); patas[3]->moverHorizontal(105);
  patas[4]->levantar(135); patas[4]->moverHorizontal(50);
  patas[5]->levantar(175); patas[5]->moverHorizontal(40);
  delay(500);
}
