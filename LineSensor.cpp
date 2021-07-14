#include "LineSensor.h"

int LeftLuminanceOutsideData[5];
int LeftLuminanceInsideData[5];
int RightLuminanceInsideData[5];
int RightLuminanceOutsideData[5];
void GetLuminance(void)
{
  LeftLuminanceInside = analogRead(LEFT_LINE_PATROL_INSIDE_SENSOR);
  RightLuminanceInside = analogRead(RIGHT_LINE_PATROL_INSIDE_SENSOR);
  LeftLuminanceOutside = analogRead(LEFT_LINE_PATROL_OUTSIDE_SENSOR);
  RightLuminanceOutside = analogRead(RIGHT_LINE_PATROL_OUTSIDE_SENSOR);
}

real_T LinePatrolSensorOutput;
void LineSensor_step(void)
{
  real_T rtb_Add2;
  rtb_Add2 = ((7.0 * log10(LeftLuminanceOutside) + 4.0 * log10
               (LeftLuminanceInside)) - 4.0 * log10(RightLuminanceInside)) - 7.0
    * log10(RightLuminanceOutside);
  if (rtb_Add2 > 0.4) {
    LinePatrolSensorOutput = rtb_Add2 - 0.4;
  } else if (rtb_Add2 >= -0.4) {
    LinePatrolSensorOutput = 0.0;
  } else {
    LinePatrolSensorOutput = rtb_Add2 - -0.4;
  }
}

void LineSensor_initialize(void)
{
  pinMode(LEFT_LINE_PATROL_OUTSIDE_SENSOR, INPUT);
  pinMode(LEFT_LINE_PATROL_INSIDE_SENSOR, INPUT);
  pinMode(RIGHT_LINE_PATROL_INSIDE_SENSOR, INPUT);
  pinMode(RIGHT_LINE_PATROL_OUTSIDE_SENSOR, INPUT);
}

void LineSensor_terminate(void)
{
}
