#include "Motor.h"

Motor::Motor(int pin_forward, int pin_backward){
  this->pin_forward = pin_forward;
  this->pin_backward = pin_backward;
  return;
}

Motor::~Motor(){

}

void Motor::setSpeed(float duty){
  if(duty > 0){
    analogWrite(this->pin_forward, duty * 255);
    digitalWrite(this->pin_backward, LOW);
  }
  else{
    duty = abs(duty);
    analogWrite(this->pin_backward, duty * 255);
    digitalWrite(this->pin_forward, LOW);
  }
}
