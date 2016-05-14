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
}
