#include "Arduino.h"
#include "Filter.h"

Filter::Filter()
{
}

Filter::~Filter()
{
}

void Filter::setsimplefiltererror(int e) {
  this->simpleerror = e;
  this->simplepast = 0;
  this->count = 0;
}

void Filter::setkalman(float q, float r, float p){
  this->q = q;
  this->r = r;
  this->p = p;
  this->v = 0.0f;
}

int Filter::simplefilter(int x) {
  if (x != 0){
      if (this->simplepast == 0){
        this->simplepast = x;
        return x;
      }
      else{
        if((abs(x-this->simplepast)) >= this->simpleerror){
          if (this->count < 3){
            this->count += 1;
            return this->simplepast;
          }
          else{
            this->simplepast = x;
            this->count = 0;
            return x;
          }
        }
        else{
          this->simplepast = x;
          return x;
        }
      }
  }
  else {
    return 0;
  }
}

int Filter::kalman(int m){
  if (m != 0){
    if (v == 0){
      this->v = float(m);
      return m;
    }
    else {
      //prediction update
      this->p = this->p + this->q;
      //measurement update
      this->k = this->p/(this->p + this->r);
      this->v = this->v + (this->k*(float(m)-this->v));
      this->p = (1.0f - this->k) * this->p;
      return int(this->v);
    }
  }
  else{
    return 0;
  }
}
