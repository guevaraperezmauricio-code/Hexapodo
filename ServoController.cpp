#include "ServoController.h"

ServoController::ServoController(int address, int minPulse, int maxPulse)
  : pwm(address), SERVOMIN(minPulse), SERVOMAX(maxPulse) {}

void ServoController::iniciar() {
  pwm.begin();
  pwm.setPWMFreq(60);
}

void ServoController::mover(int canal, int angulo) {
  int pulso = map(angulo, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(canal, 0, pulso);
}
