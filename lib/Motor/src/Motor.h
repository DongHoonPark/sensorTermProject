#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

class Motor{

public:
  Motor(int pin_forward, int pin_backward);
  ~Motor();
  void setSpeed(float duty);

private:
  int pin_forward;
  int pin_backward;

};

#endif
