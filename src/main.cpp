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

CourseVector coursevector = CourseVector(11000,21000,16200,77700,5000); //new course
Filter filterx = Filter();
Filter filtery = Filter();
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

void gyroSensing(void);
void controlVehicle(void);

void setup(){
  //setting value
  filterx.setsimplefiltererror(5000);
  filtery.setsimplefiltererror(5000);
  pid.setPIDS(0.55f, 0.1f, 0.02f, 300.0f, 2500.0f);
  spc.setSpeedcontrol(0.4f, 1.0f, 0.6f, 0.7f); //basic 0.4f
  //Serial set
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
  course_v = coursevector.getDistanceFromCourse(filterx.simplefilter(location.getXpos()), filtery.simplefilter(location.getYpos()));
  sec_v = spc.getSpeedcontrol(coursevector.sector, course_v, 8000);
  /*moving action*/
  steering.setDirection(pid.getPIDS(course_v));
  if(location.getXpos() != 0){
  //spc.getSpeedcontrol(coursevector.sector, int cours, int cmax)
  dc.setSpeed(sec_v); //basic 8000
  }

  #ifdef DEBUG_MSG_ON
  Serial.print("x : ");
  Serial.print(filterx.simplefilter(location.getXpos()));
  //Serial.print(location.getXpos());
  Serial.print("\t");
  Serial.print("y :");
  Serial.print(filtery.simplefilter(location.getYpos()));
  //Serial.print(location.getYpos());
  Serial.print("\t");
  Serial.print(coursevector.getDistanceFromCourse(filterx.simplefilter(location.getXpos()), filtery.simplefilter(location.getYpos())));
  Serial.print("\t");
  Serial.print(coursevector.sector);
  Serial.print("\n");

  #endif
//debug
}
