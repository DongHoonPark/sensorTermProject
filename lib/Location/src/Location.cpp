#include "Location.h"

Location::Location(){
  this->Xpos = 0;
  this->Ypos = 0;
}

Location::~Location(){
}

int Location::getXpos(){
  return this->Xpos;
}

int Location::getYpos(){
  return this->Ypos;
}

void Location::update(){
}
