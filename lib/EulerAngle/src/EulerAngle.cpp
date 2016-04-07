#include "EulerAngle.h"

EulerAngle::EulerAngle(){
  this->roll = 0.0f;
  this->pitch = 0.0f;
  this->yaw = 0.0f;
}

void EulerAngle::updateQuaternion(float q0, float q1, float q2, float q3){
  
}

void EulerAngle::getEuler(float *ypr){
  ypr[0] = this->yaw;
  ypr[1] = this->pitch;
  ypr[2] = this->roll;
}

float EulerAngle::getRoll(){
  return this->roll;
}

float EulerAngle::getYaw(){
  return this->yaw;
}

float EulerAngle::getPitch(){
  return this->pitch;
}
