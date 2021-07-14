/*
 *Modified 9 May 2021
 *by Peixuan zhang
 *


Arduino Pin Definition:
  A0:
  A1:
  A2:
  A3:
  A4:
  A5:

  2: Phase A of the left encoder
  3: Phase A of the right encoder
  4: Phase B of the left encoder
  5: Phase B of the right encoder
  6: Sonar EchoPin
  7: Sonar TrigPin
  8:
  9:
  10:
  11:
  12:
  13:

  SDA: SDA for OLED
  SCL: SCL for OLED
*/

#include <FlexiTimer2.h>

#include "OLED.h"
#include "Sonar.h"
#include "Buzzer.h"
#include "Encoder.h"
#include "MotorDrive.h"
#include "LineSensor.h"
#include "UnloadServo.h"
#include "MomentControl.h"
#include "BeaconSearchSensor.h"
#include "DistanceMeasurement.h"

#include "PinConfiguration.cpp"
             
//#define Angle2Arc(x) (3.1415926*(x)/180.0)     //convert radians to degrees


//**********************************************************************************************************************

real_T Direction;
real_T ExpectSpeed;
real_T LeftLuminanceInside;
real_T LeftLuminanceOutside;
real_T RightLuminanceInside;
real_T RightLuminanceOutside;
real_T LeftMotorSpeed;
real_T RightMotorSpeed;
real_T LeftBeaconLuminance;
//real_T CenterBeaconLuminance;
real_T RightBeaconLuminance;

volatile real_T DistancetoWall;
volatile int TimeFlag;
volatile double BeaconSearchServoAngle;

const double MaxSpeed = 2.3;

const double ReadytoStopZone = 25;
const double StopDistance = 7;

int TaskFlag;
int SensorFlag;
int StartingBuzzFlag;
int BeaconSearchBuzzFlag;
int DistanceMeasurementFlag;
int UnloadFlag;

const double LinePatrolSpeedFactor = 0.3;

//**********************************************************************************************************************
void setup() 
{
  DistancetoWall = 999;
  
  TimeFlag = 0;
  
  TaskFlag = 0;
  
  StartingBuzzFlag = 0;
  BeaconSearchBuzzFlag = 0;
  DistanceMeasurementFlag = 0;
  
  ExpectSpeed = 0;
  LeftMotorSpeed = 0;
  RightMotorSpeed = 0;
  UnloadFlag = 0;

  OLED_initialize();
  Sonar_initialize();
  Buzzer_initialize();
  Encoder_initialize();
  LineSensor_initialize();
  MotorDrive_initialize();
  UnloadServo_initialize();
  MomentControl_initialize();
  BeaconSearchSensor_initialize();
  DistanceMeasurement_initialize();

  interrupts();
  
  FlexiTimer2::set(10, 1.0/1000, Isr); 

  Serial.begin(115200);                //初始化波特率为115200

  FlexiTimer2::start();
  pinMode(SWITCH_PIN, INPUT);
  pinMode(A14, INPUT);
  WelcomePage();
}


//**********************************************************************************************************************
void loop()
{
  //TaskFlag = 4;
  switch (TaskFlag)
  {
    case 0: Start(); break;
    case 1: Task_1(); break;
    case 2: Task_2(); break;
    case 4: Task_4(); break;
    default: {ExpectSpeed = 0; MissionComplete();}
  } 
  if(TaskFlag != 5){SpeedandDistanceInfo();}

  Serial.println(BeaconDirection);
}

void Start()
{
  ExpectSpeed = 0;
  if(digitalRead(SWITCH_PIN) == HIGH)
  {
    TaskFlag = 1;
    SetBuzzTime(10);
    delay(2000);
  }
}

void Task_1()
{
  SensorFlag = 0;
  if(StartingBuzzFlag == 0)
  {
    ExpectSpeed = MaxSpeed *  0.08;
  }
  else
  {
    ExpectSpeed = MaxSpeed * LinePatrolSpeedFactor; 
  }
  
  if(((LeftLuminanceOutside >= 250) && (RightLuminanceOutside >= 250)) && ((LeftLuminanceInside <= 800) || (RightLuminanceInside <= 800)) && (StartingBuzzFlag == 0))
  {
    SetBuzzTime(100); 
    DistanceMeasurementFlag = 1;
    StartingBuzzFlag = 1;
  }

  SonarDistanceMeasurement();
  if(DistancetoWall <= ReadytoStopZone)
  {
    TaskFlag = 2;
  }
}

void Task_2()
{
  SonarDistanceMeasurement();
  ExpectSpeed = ((DistancetoWall - StopDistance) / ReadytoStopZone) * MaxSpeed *  0.10;
  if(ExpectSpeed >= (MaxSpeed *  LinePatrolSpeedFactor))
  {
    ExpectSpeed = MaxSpeed *  LinePatrolSpeedFactor;
  }
  else if(ExpectSpeed <= (-1 * MaxSpeed *  LinePatrolSpeedFactor))
  {
    ExpectSpeed = -1 * MaxSpeed *  LinePatrolSpeedFactor;
  }
  SensorFlag = 0;
  
  if(DistancetoWall <= (StopDistance + 1))
  {
    ExpectSpeed = 0;
    TaskFlag = 4;
    SetBuzzTime(200);
    for(int i=20; i>0; i--)
    {
      if(i <= 10){Count(i);}
      delay(1000);
    }
  }
}

void Task_4()
{
  if((UnloadFlag == 0) && (BeaconSearchBuzzFlag == 1))
  {
    ExpectSpeed = MaxSpeed * 0.25;
  }
//  else if(BeaconSearchBuzzFlag == 0)
//  {
//    ExpectSpeed = MaxSpeed * -0.15;
//  }
  else if(UnloadFlag == 1)
  {
    ExpectSpeed = 0;
  }
  SensorFlag = 1;
  
  if(BeaconSearchBuzzFlag == 0)
  {
    SensorFlag = 2;
    SetBuzzTime(100);

    FlexiTimer2::stop();
    Power(LEFT_MOTOR_DRIVE_PIN, LEFT_MOTOR_IO_PIN, -1);
    Power(RIGHT_MOTOR_DRIVE_PIN, RIGHT_MOTOR_IO_PIN, -1);
    delay(1000);
    Power(LEFT_MOTOR_DRIVE_PIN, LEFT_MOTOR_IO_PIN, 1);
    Power(RIGHT_MOTOR_DRIVE_PIN, RIGHT_MOTOR_IO_PIN, -1);
    delay(300);
    FlexiTimer2::start();
//    ExpectSpeed = 1;
//    delay(1000);
    SensorFlag = 1;
    BeaconSearchBuzzFlag = 1;
  }
  if((LeftRMS >= 5.0) && (RightRMS >= 5.0) && UnloadFlag == 0)
  {
    UnloadFlag = 1;
    SetBuzzTime(200);
    TaskFlag = 5;
    Unload();
  }
}

void SensorSwitch()
{
  if(SensorFlag == 0)
  {
    Direction = LinePatrolSensorOutput;
  }
  else if(SensorFlag == 1)
  {
    Direction = -1 * ((BeaconSearchServoAngle - 90) / 27.5);
  }
  else
  {
    Direction = 0;
  }
}

void Isr()
{
  TimeFlag++;

  if(TimeFlag%5 == 0)  {EncoderIsr();}
  if((TimeFlag%5 == 0) && (DistanceMeasurementFlag == 1))  {DistanceMeasurement_step();} 
  if(TimeFlag%5 == 0)  {GetLuminance(); LineSensor_step();}
  if((TimeFlag%5 == 0) && (SensorFlag == 1))  {GetBeaconLuminance(); BeaconSearchSensor_step(); BeaconTrace();}
  if(TimeFlag%5 == 0)  {SensorSwitch();}
  if(TimeFlag%5 == 0)  {MomentControl_step(); MotorPower();}
  if(TimeFlag%1 == 0)  {BuzzIsr();}
  
  if(TimeFlag > 1000)  {TimeFlag = 0;}
}
