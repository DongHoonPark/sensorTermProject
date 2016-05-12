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
  if(searchHeaderRequired){
    //header missing situation.
    //searching header
    if(data_input == 0x4D){
      dataBuffer[0] = data_input;
      dataBufferIndex = 1;
      searchHeaderRequired = false;
    }
    else{
      dataBufferIndex = 0;
    }
  }
  else{
    this->dataBuffer[dataBufferIndex] = data_input;
    dataBufferIndex++;
    if(dataBufferIndex == 12){
      if(dataBuffer[0] == 0x4D){
        for(int i=0; i<12; i++){
          data[i] = dataBuffer[i];
        }
        dataBufferIndex = 0;
      }
      else{
        //error handling
        dataBufferIndex = 0;
        searchHeaderRequired = true;
      }
    }
  }
}

void Location::update(){
  if( (data[0]==0x4D)
      && (data[1]==0x00)
      && (data[2]==0x00)
      && (data[3]==0x00)
    ){
    //maybe more error situation can occur...
    uint32_t XposRead = ((uint32_t)data[4]<<24)|((uint32_t)data[5]<<16)|((uint32_t)data[6]<<8)|((uint32_t)data[7]);
    uint32_t YposRead = ((uint32_t)data[8]<<24)|((uint32_t)data[9]<<16)|((uint32_t)data[10]<<8)|((uint32_t)data[11]);
    this->Xpos_previous = this->Xpos;
    this->Ypos_previous = this->Ypos;
    this->Xpos = XposRead;
    this->Ypos = YposRead;
  }
  else{
    //error handling
    dataBufferIndex = 0;
    searchHeaderRequired = true;
  }
}
