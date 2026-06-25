#include <Wire.h>
#include <SoftwareSerial.h>
#include "ServoController.h"
#include "Pata.h"
#include "Hexapodo.h"

SoftwareSerial bluetooth(11, 10);
int cicloActivo = 0;

ServoController servoCtrl(0x40, 125, 625);
Hexapodo robot(&servoCtrl);

void setup() {
  servoCtrl.iniciar();
  bluetooth.begin(9600);

  robot.asignarPata(0, new Pata(5, 4, &servoCtrl));
  robot.asignarPata(1, new Pata(15, 14, &servoCtrl));
  robot.asignarPata(2, new Pata(8, 9, &servoCtrl));
  robot.asignarPata(3, new Pata(10, 11, &servoCtrl));
  robot.asignarPata(4, new Pata(7, 6, &servoCtrl));
  robot.asignarPata(5, new Pata(13, 12, &servoCtrl));

  robot.pararse();
}

void loop() {
  if (bluetooth.available() > 0) {
    char comando = bluetooth.read();
    if (comando == 'W' || comando == 'w') {
      cicloActivo = 1;
    } else if (comando == 'S' || comando == 's') {
      cicloActivo = 0;
      robot.pararse();
    }
  }

  if (cicloActivo == 1) {
    robot.moverA();
    delay(300);
    robot.moverB();
    delay(300);
  }
}
