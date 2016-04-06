#ifndef LOCATION_H
#define LOCATION_H

#include "Arduino.h"

class Location{

public:
  Location(void);
  ~Location(void);
  void update (void);
  void pushData (uint8_t data);
  int  getXpos (void);
  int  getYpos (void);

private:
  uint8_t dataBuffer[12];
  int dataBufferIndex;
  uint8_t data[12];
  int Xpos;
  int Ypos;
  bool searchHeaderRequired;
  int Xpos_previous;
  int Ypos_previous;

};

#endif
