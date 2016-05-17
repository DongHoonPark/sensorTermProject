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
#include "PIDS.h"
#include "Speedcontrol.h"

#define DEBUG_MSG_OFF //debug message switch

DueTimer gyroTimer = DueTimer(1);
DueTimer controlTimer = DueTimer(6);

Steering steering = Steering( 170.0f , 10.0f );
Location location = Location();
Motor dc = Motor(3,2);
EulerAngle ea = EulerAngle();

CourseVector coursevector = CourseVector(11000,21000,16200,77700,6000); //new course
Filter filterx = Filter();
Filter filtery = Filter();
Filter kalx = Filter();
Filter kaly = Filter();

PIDS pid = PIDS();
Speedcontrol spc = Speedcontrol();

MPU6050 accelgyro;

int16_t gx, gy, gz, ax, ay, az;

float gx_rad, gy_rad, gz_rad, ax_ms2, ay_ms2, az_ms2;
float scaleGyro = (2.0f * PI * 250.0f / 360.0f) / 32768.0f;
float scaleAccel = (2.0f * 9.8f) / 32768.0f;
int course_v;
float speed_v;
float sec_v;
int sect_v;
int lx;
int ly;
int count;

void gyroSensing(void);
void controlVehicle(void);

void setup(){
  //setting value
  filterx.setsimplefiltererror(8000);
  filtery.setsimplefiltererror(8000);

  kalx.setkalman(0.0625f, 4.0f, 0.47f);
  kaly.setkalman(0.0625f, 4.0f, 0.47f);

  pid.setPIDS(0.55f, 0.1f, 0.02f, 300.0f, 2200.0f);
  spc.setSpeedcontrol(0.4f, 0.9f, 0.65f, 0.65f); //basic 0.4f

  //Serial set
  Serial.begin(115200);
  Serial3.begin(115200);
  steering.attach(8);

  count = 0;
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
  if(location.getXpos() != 0){
     lx = filterx.simplefilter(location.getXpos());
     ly = filtery.simplefilter(location.getYpos());
     //lx = kalx.kalman(location.getXpos());
     //ly = kaly.kalman(location.getYpos());

  course_v = coursevector.getDistanceFromCourse(lx, ly);
  sect_v = coursevector.sector;
  sec_v = spc.getSpeedcontrol(sect_v, course_v, 7000);
  /*moving action*/
  steering.setDirection(pid.getPIDS(course_v));

  //spc.getSpeedcontrol(sect_v, int cours, int cmax);
  if(location.getXpos() != lx || location.getYpos() != ly || sec_v < 0){
      dc.setSpeed(0.2f);
  }
  else{
  dc.setSpeed(sec_v); //basic 8000
  }
  }

  #ifdef DEBUG_MSG_ON
  Serial.print("x : ");
  Serial.print(lx);
  //Serial.print(location.getXpos());
  Serial.print("\t");
  Serial.print("y :");
  Serial.print(ly);
  //Serial.print(location.getYpos());
  Serial.print("\t");
  Serial.print(course_v);
  Serial.print("\t");
  Serial.print(sect_v);
  Serial.print("\n");

  #endif
//debug
}
