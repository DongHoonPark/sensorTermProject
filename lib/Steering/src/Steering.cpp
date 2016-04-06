#include "Steering.h"

Steering::Steering(int dir_max, int dir_min){
  this->dir_max = dir_max;
  this->dir_min = dir_min;
  this->dir_mid = (dir_max + dir_min) / 2.0f ;
}

Steering::~Steering(){
    
}

void Steering::setDirection(float dir){
  //dir is -1.0f to 1.0f
  this->write( int( this->dir_mid + dir * ( this->dir_max - this->dir_mid ) ) );
}
