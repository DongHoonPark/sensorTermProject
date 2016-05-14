#include "Arduino.h"
#include "DueTimer.h"
#include "MadgwickAHRS.h"
#include "Steering.h"
#include "Location.h"
#include "Motor.h"
#include "I2Cdev.h"
#include "MPU6050.h"
#include "EulerAngle.h"
#include "CourseVector.h"
#include "Filter.h"

#define DEBUG_MSG_ON //debug message switch

DueTimer gyroTimer = DueTimer(1);
DueTimer controlTimer = DueTimer(6);

Steering steering = Steering( 170.0f , 10.0f );
Location location = Location();
Motor dc = Motor(3,2);
EulerAngle ea = EulerAngle();
CourseVector coursevector = CourseVector(11000,21000,16200,77700,6000); //new course
Filter filterx = Filter();
Filter filtery = Filter();

MPU6050 accelgyro;

int16_t gx, gy, gz, ax, ay, az;

int nowvector;
float svalue;

float dt = 0.02f;
float Kp = 0.55f;
float Ki = 0.1f;
float Kp_v = 0.0f;
float Ki_v = 0.0f;
float error_int = 0.0f;

float gx_rad, gy_rad, gz_rad, ax_ms2, ay_ms2, az_ms2;
float scaleGyro = (2.0f * PI * 250.0f / 360.0f) / 32768.0f;
float scaleAccel = (2.0f * 9.8f) / 32768.0f;

void gyroSensing(void);
void controlVehicle(void);

void setup(){

   nowvector = 0;
   svalue = 0.0f;

  filterx.setsimplefiltererror(7000);
  filtery.setsimplefiltererror(7000);
  Serial.begin(115200);
  Serial3.begin(115200);
  steering.attach(8);

//  accelgyro.initialize();

  pinMode(LED_BUILTIN, OUTPUT);

  //gyroTimer.attachInterrupt(gyroSensing).start(2500);
  controlTimer.attachInterrupt(controlVehicle).start(20000); //real test 50000 -> 20000
}

void loop(){

    while(Serial3.available()){
    char buf  = Serial3.read();
    //Serial.println(buf,HEX);
    location.pushData(buf);

  }

}

void gyroSensing(void){

  accelgyro.getMotion6(&ax, &ay, &ax, &gx, &gy, &gz);

  gx_rad = scaleGyro * gx;
  gy_rad = scaleGyro * gy;
  gz_rad = scaleGyro * gz;

  ax_ms2 = scaleAccel * ax;
  ay_ms2 = scaleAccel * ay;
  az_ms2 = scaleAccel * az;

  MadgwickAHRSupdateIMU(gx_rad, gy_rad, gz_rad, ax_ms2, ay_ms2, az_ms2);
  ea.updateQuaternion(q0, q1, q2, q3);

}

void controlVehicle(void){

  location.update();
  /* and there will be more control code*/
  nowvector = coursevector.getDistanceFromCourse(filterx.simplefilter(location.getXpos()), filtery.simplefilter(location.getYpos()));
  /*moving action*/

/*
  if (nowXvalue != 0){
    //steering.setDirection((-0.7*(float(nowvector))/2500.0f));
    Kp_v = Kp * float(nowvector);
    error_int += float(nowvector) * dt;
    if(error_int > 300){
      error_int = 300;
    }
    steering.setDirection((Kp_v+(Ki* error_int))/2000.0f);
    if (coursevector.sector == 1 || coursevector.sector == 3 || coursevector.sector == 7 || coursevector.sector == 9){
    //steering.setDirection(-(Kp_v+(Ki* error_int))/2000.0f);
    dc.setSpeed(svalue - 0.08f);
    }
    else if(coursevector.sector == 2 || coursevector.sector == 8){
      dc.setSpeed(svalue - 0.05f);
    }
    else{
    //steering.setDirection((Kp_v+(Ki* error_int))/2000.0f);
    dc.setSpeed(svalue);
    }
  }
  */

  #ifdef DEBUG_MSG_ON
  Serial.print("x : ");
  Serial.print(filterx.simplefilter(location.getXpos()));
  //Serial.print(location.getXpos());
  Serial.print("\t");
  Serial.print("y :");
  Serial.print(filtery.simplefilter(location.getYpos()));
  //Serial.print(location.getYpos());
  Serial.print("\t");
  Serial.print(nowvector);
  Serial.print("\n");
  Serial.print(coursevector.sector);
  #endif
//debug
}
