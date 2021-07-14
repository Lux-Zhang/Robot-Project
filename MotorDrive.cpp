#include "MotorDrive.h"

const double DutyCycleMax = 255;
const double DutyCycleMin = 0;

double Normalized(double Val, double Xmax, double Xmin, double Ymax, double Ymin)
{

    // Ҫ��һ�ķ�Χ�����ֵ  Ymax 

    // Ҫ��һ�ķ�Χ����Сֵ Ymin
    
    // ����һ�ķ�Χ�����ֵ  Xmax 

    // ����һ�ķ�Χ����Сֵ  Xmin 


    // ��һ������
    double NormalizedVal = (Ymax - Ymin) * (Val - Xmin) / (Xmax - Xmin) + Ymin;
    return NormalizedVal;
}

void MotorDrive_initialize(void)
{
  pinMode(LEFT_MOTOR_IO_PIN, OUTPUT);
  pinMode(RIGHT_MOTOR_IO_PIN, OUTPUT);
}

void PWMOutput(int DrivePin, int IOPin, int DutyCycle) 
{
  //Serial.println(DutyCycle);
  if(DutyCycle >=0) 
  {
    digitalWrite(IOPin, HIGH);
  }
  else 
  {
    digitalWrite(IOPin, LOW);
  }
  analogWrite(DrivePin, abs(DutyCycle));
}

void Power(int DrivePin, int IOPin, double Power) 
{
  double DutyCycle = Normalized(Power, MaxSpeed, -1 * MaxSpeed, DutyCycleMax * 1, -1 * DutyCycleMax * 1);
  //int DrivePower = (DutyCycle + DutyCycleMax)/2;
  int DrivePower = DutyCycle;
  //Serial.println(DutyCycle);
  PWMOutput(DrivePin, IOPin, DrivePower);
}
void MotorPower(void)
{
  Power(LEFT_MOTOR_DRIVE_PIN, LEFT_MOTOR_IO_PIN, LeftMotorOutput);
  Power(RIGHT_MOTOR_DRIVE_PIN, RIGHT_MOTOR_IO_PIN, RightMotorOutput);
  //Serial.println(RightMotorOutput);
}
