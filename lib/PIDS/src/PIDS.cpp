#include "Arduino.h"
#include "PIDS.h"

PIDS::PIDS()
{
}

PIDS::~PIDS()
{
}

void PIDS::setPIDS(float kp, float ki, float dt, float ermax, float steer_v) {
  this->Kp = kp;
  this->Ki = ki;
  this->dt = dt;
  this->ermax = ermax;
  this->error_int = 0.0f;
  this-> steer_v = steer_v;
}
float PIDS::getPIDS(int vec) {
this->Kp_v = this->Kp * float(vec);
this->error_int += float(vec) * this->dt;
if (this->error_int >= this->ermax){
  this->error_int = this->ermax;
}
return (this->Kp_v+(this->Ki * this->error_int))/this->steer_v;
}
