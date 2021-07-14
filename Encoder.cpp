#include"Encoder.h"

volatile long LeftEncoderCount=0;
volatile long RightEncoderCount=0;      //该变量用于存储编码器的值，所以用类型修饰符volatile；

double LeftMotorSpeedData[5];
double RightMotorSpeedData[5];
void Encoder_initialize(void)
{
  pinMode(LEFT_ENCODER_A, INPUT);
  pinMode(LEFT_ENCODER_B, INPUT);                    //设置为输入模式，并且2,3号引脚是中断口0,1；
  pinMode(RIGHT_ENCODER_A, INPUT);
  pinMode(RIGHT_ENCODER_B, INPUT);
                  
  attachInterrupt(digitalPinToInterrupt(LEFT_ENCODER_A), LeftEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(RIGHT_ENCODER_A), RightEncoder, RISING);
} 

//外部中断处理函数
void LeftEncoder(void)
{
  if(digitalRead(LEFT_ENCODER_B) == HIGH) //B脉冲为低电平
  {
    LeftEncoderCount++;    //每一个中断加一
  } 
  else
  {
    LeftEncoderCount--;
  }
}
void RightEncoder(void)
{
  if(digitalRead(RIGHT_ENCODER_B) == LOW) //B脉冲为低电平
  {
    RightEncoderCount++;    //每一个中断加一
  } 
  else
  {
    RightEncoderCount--;
  }
}
//定时器中断处理函数
void EncoderIsr(void)
{   
  double LeftMotorAngleSpeed=(1/0.05)*LeftEncoderCount/580.0;    //这里的单位是转每s：r/s
  double RightMotorAngleSpeed=(1/0.05)*RightEncoderCount/580.0;    //这里的单位是转每s：r/s
   
//  LeftMotorSpeedData[0] = LeftMotorSpeedData[1];
//  LeftMotorSpeedData[1] = LeftMotorSpeedData[2];
//  LeftMotorSpeedData[2] = LeftMotorSpeedData[3];
//  LeftMotorSpeedData[3] = LeftMotorSpeedData[4];
//  LeftMotorSpeedData[4] = LeftMotorAngleSpeed * 0.2065;
//
//  RightMotorSpeedData[0] = RightMotorSpeedData[1];
//  RightMotorSpeedData[1] = RightMotorSpeedData[2];
//  RightMotorSpeedData[2] = RightMotorSpeedData[3];
//  RightMotorSpeedData[3] = RightMotorSpeedData[4];
//  RightMotorSpeedData[4] = RightMotorAngleSpeed * 0.2065;
//
//  LeftMotorSpeed = (LeftMotorSpeedData[0] + LeftMotorSpeedData[1] +
//                   LeftMotorSpeedData[2] + LeftMotorSpeedData[3] +
//                   LeftMotorSpeedData[4]) / 5;
//  RightMotorSpeed = (RightMotorSpeedData[0] + RightMotorSpeedData[1] +
//                    RightMotorSpeedData[2] + RightMotorSpeedData[3] +
//                    RightMotorSpeedData[4]) / 5;
  LeftMotorSpeed = LeftMotorAngleSpeed * 0.215;
  RightMotorSpeed = RightMotorAngleSpeed * 0.215;   
  
  LeftEncoderCount=0;
  RightEncoderCount=0;               //清空该时间段内的脉冲数           
}
