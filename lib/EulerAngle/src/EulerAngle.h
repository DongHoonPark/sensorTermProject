#ifndef EULER_ANGLE_H_
#define EULER_ANGLE_H_

#include "Arduino.h"

class EulerAngle{
public:
  EulerAngle();
  void updateQuaternion(float q0, float q1, float q2, float q3);
  void getEuler(float* ypr);
  float getYaw();
  float getPitch();
  float getRoll();
private:
  float yaw;
  float pitch;
  float roll;
};

#endif
