#include "Arduino.h"
#include "Speedcontrol.h"

/* sectors
1     2     3
 x1y1   x2y1
4     5     6
 x1y2   x2y2
7     8     9
*/

Speedcontrol::Speedcontrol()
{
}

Speedcontrol::~Speedcontrol()
{
}

void Speedcontrol::setSpeedcontrol(float basics, float linear, float curve, float slinear) {
  this->linear = linear;
	this->curve = curve;
	this->slinear = slinear;
	this->basicspeed = basics;
}
float Speedcontrol::getSpeedcontrol(int sec, int cours, int cmax) {
  if((this->basicspeed * this->curve) / (1.0f - abs(float(cours/cmax))) <= this->basicspeed){
    if(sec == 1 || sec == 7 || sec == 3 || sec == 9){
      return (this->basicspeed * this->curve);// * abs((1.0f - abs(float(cours/cmax))));
    }
    else if(sec == 2 || sec == 8){
      return (this->basicspeed * this->slinear) * (1.0f - abs(float(cours/cmax)));
    }
    else{
      return (this->basicspeed * this->linear) * (1.0f - abs(float(cours/cmax)));
    }
  /*
  switch (sec) {
    case 1:
      return (this->basicspeed * this->curve) * (1.0f - abs(float(cours/cmax)));
    case 2:
      return (this->basicspeed * this->slinear) * (1.0f - abs(float(cours/cmax)));
    case 3:
      return (this->basicspeed * this->curve) * (1.0f - abs(float(cours/cmax)));
    case 4:
      return (this->basicspeed * this->linear) * (1.0f - abs(float(cours/cmax)));
    case 5:
      return (this->basicspeed * this->linear) * (1.0f - abs(float(cours/cmax)));
    case 6:
      return (this->basicspeed * this->linear) * (1.0f - abs(float(cours/cmax)));
    case 7:
      return (this->basicspeed * this->curve) * (1.0f - abs(float(cours/cmax)));
    case 8:
      return (this->basicspeed * this->slinear) * (1.0f - abs(float(cours/cmax)));
    case 9:
      return (this->basicspeed * this->curve) * (1.0f - abs(float(cours/cmax)));
  }
  */
}
else{
  return 0.3f;
}
}
