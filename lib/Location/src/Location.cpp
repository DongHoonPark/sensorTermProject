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

void Location::pushData(uint8_t data_input){
  this->dataBuffer[dataBufferIndex] = data_input;
  dataBufferIndex++;
  if(dataBufferIndex == 12){
    if(dataBuffer[0] == 0x4D){
      memcpy(dataBuffer, data, 12);
      dataBufferIndex = 0;
    }
    else{

    }
  }
}

void Location::update(){
}
