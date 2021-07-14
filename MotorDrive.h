#include <math.h>
#include <SPI.h>

#include "rtwtypes.h"


extern const int LEFT_MOTOR_DRIVE_PIN; 
extern const int RIGHT_MOTOR_DRIVE_PIN; 

extern const int LEFT_MOTOR_IO_PIN;
extern const int RIGHT_MOTOR_IO_PIN;

extern const double MaxSpeed;

extern real_T LeftMotorOutput;
extern real_T RightMotorOutput;

extern double Normalized(double Val, double Xmax, double Xmin, double Ymax, double Ymin);
extern void MotorDrive_initialize(void);
extern void PWMOutput(int DrivePin, int IOPin, int DutyCycle);
extern void Power(int DrivePin, int IOPin, double Power);
extern void MotorPower(void);
