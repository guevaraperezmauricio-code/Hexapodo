#ifndef SERVOCONTROLLER_H
#define SERVOCONTROLLER_H

#include <Adafruit_PWMServoDriver.h>

class ServoController {
  Adafruit_PWMServoDriver pwm;
  int SERVOMIN, SERVOMAX;

public:
  ServoController(int address, int minPulse, int maxPulse);
  void iniciar();
  void mover(int canal, int angulo);
};

#endif
