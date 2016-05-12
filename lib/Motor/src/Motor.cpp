#include "Motor.h"

Motor::Motor(int pin_forward, int pin_backward){
  this->pin_forward = pin_forward;
  this->pin_backward = pin_backward;
  pinMode(this->pin_forward,OUTPUT);
  pinMode(this->pin_backward,OUTPUT);
  return;
}

Motor::~Motor(){

}

void Motor::setSpeed(float duty){
  if(duty >= 0){
    analogWrite(this->pin_forward, (int)(duty * 80));
    digitalWrite(this->pin_backward, LOW);
  }
  else{
    duty = abs(duty);
    analogWrite(this->pin_backward, (int)(duty * 80));
    digitalWrite(this->pin_forward, LOW);
  }
}
