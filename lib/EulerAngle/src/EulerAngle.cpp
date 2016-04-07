#include "EulerAngle.h"

EulerAngle::EulerAngle(){
  this->roll = 0.0f;
  this->pitch = 0.0f;
  this->yaw = 0.0f;
}

void EulerAngle::updateQuaternion(float q0, float q1, float q2, float q3){
  this->roll = atan2f(
    2 * (q0 * q1 + q2 * q3),
    1 - 2 * (q1 * q1 + q2 * q2)
  );
  this->pitch = asinf(
    2 * (q0 * q2 - q3 * q1)
  );
  this->yaw = atan2f(
    2 * (q0 * q3 + q1 * q2),
    1 - 2* (q2 * q2 + q3 * q3)
  );
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
