#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>                      //the OLED display required this library
#include <Adafruit_SSD1306.h>                  //the OLED display required this library

#include "rtwtypes.h"

extern const int OLED_SDA;
extern const int OLED_SCL;

extern real_T LeftMotorSpeed;
extern real_T RightMotorSpeed;

extern real_T Direction;

extern real_T Distance;

extern volatile real_T DistancetoWall;

extern real_T LeftLuminanceInside;
extern real_T LeftLuminanceOutside;
extern real_T RightLuminanceInside;
extern real_T RightLuminanceOutside;

extern void OLED_initialize(void);
extern void WelcomePage(void);
extern void MissionComplete(void);
extern void SpeedandDistanceInfo(void);
extern void Count(int CountNumber);
