#include "OLED.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void OLED_initialize(void)
{
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);	
}

void WelcomePage(void)
{
  display.clearDisplay();                     //clear the display
  display.setTextSize(3);                     //set the text size of display
  display.setCursor(20,20);                   //set initial position of the text
  display.setTextColor(WHITE);                //set font color
  display.println("ROBOT");                   //print characters and wrap lines
  display.setTextSize(1);                     //set the text size of display
  display.setCursor(0,48);                   //set initial position of the text
  display.println("POWERD BY: ");                   //print characters and wrap lines
  display.println("P Zhang, T Yang");                   //print characters and wrap lines
  display.display();                          //display above
  delay(1500);                                //make a delay to see clearly
  display.clearDisplay();
  display.drawLine(0,18, 126,18, WHITE);
  display.drawLine(0,19, 126,19, WHITE);
  display.drawLine(0,20, 0,43, WHITE);
  display.setTextSize(3);
  display.setCursor(1,20);
  display.setTextColor(BLACK, WHITE);
  display.println("WELCOME");
  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();
}

void MissionComplete(void)
{
  display.clearDisplay();                     //clear the display
  display.setTextSize(2);                     //set the text size of display
  display.setCursor(24,18);                   //set initial position of the text
  display.setTextColor(WHITE);                //set font color
  display.println("MISSION");                   //print characters and wrap lines
  display.setCursor(18,36);                   //set initial position of the text
  display.println("COMPLETE");                   //print characters and wrap lines
  display.display();
}
void Count(int CountNumber)
{
  display.clearDisplay();                     //clear the display
  display.setTextSize(2);                     //set the text size of display
  display.setCursor(8,18);                   //set initial position of the text
  display.setTextColor(WHITE);                //set font color
  display.println("START IN:");                   //print characters and wrap lines
  display.setCursor(36,36);                   //set initial position of the text
  display.println(CountNumber);                   //print characters and wrap lines
  display.display();
}

void SpeedandDistanceInfo(void)
{
  display.clearDisplay();//清屏 
  display.setCursor(22,4);             //set font starting position  
  display.setTextColor(WHITE);//开像素点发光
  display.setTextSize(1); //设置字体大小 
  display.println("Speed&Distance");
  display.println();

  display.setCursor(0,16); 
  display.print("L_Speed:");  
  display.print(LeftMotorSpeed, 3);
  display.println("m/s");

  display.print("R_Speed:");  
  display.print(RightMotorSpeed, 3);
  display.println("m/s");
  
  display.print("M_Distance:");  
  display.print(Distance, 3);
  display.println("m");

  display.print("P_Distance:");  
  display.print(DistancetoWall, 3);
  display.println("cm");


  display.print("Direction:");  
  display.println(Direction, 3);

/*
  display.print("1-2:");  
  display.println((LeftLuminanceOutside + LeftLuminanceInside)/2, 1);

  display.print("2-3:");  
  display.println((LeftLuminanceInside + RightLuminanceInside)/2, 1);

  display.print("3-4:");  
  display.println((RightLuminanceInside + RightLuminanceOutside)/2, 1);


  display.print("Left:");  
  display.println(LeftLuminanceInside, 1);

  display.print("Right:");  
  display.println(RightLuminanceInside, 1);

  display.print("Center:");  
  display.println((LeftLuminanceInside + RightLuminanceInside), 1);
*/  
  display.display();                //display above
  display.clearDisplay();//清屏 
}
