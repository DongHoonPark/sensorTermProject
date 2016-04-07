#ifndef VEHICLE_CONTROLLER_H_
#define VEHICLE_CONTROLLER_H_

#include "Arduino.h"
#include "Location.h"
#include "Motor.h"
#include "Steering.h"

class VehicleController{
public:
  VehicleController();
  VehicleController(Location& location, Motor& motor, Steering& steering);
private:

};

#endif
