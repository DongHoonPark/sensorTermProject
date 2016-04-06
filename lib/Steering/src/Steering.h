#ifndef STEERING_H_
#define STEERING_H_

#include "Arduino.h"
#include "Servo.h"

class Steering : public Servo {

public :
  Steering(int dir_max, int dir_min);
  ~Steering();
  void setDirection(float dir);

private :
  int dir_max;
  int dir_min;
  int dir_mid;
};

#endif
