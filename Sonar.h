#include "rtwtypes.h"


extern const int SONAR_TRIG_PIN; 
extern const int SONAR_ECHO_PIN;

extern volatile real_T DistancetoWall;

const int TimeOut = 5;
unsigned int StartTime;
unsigned int StopTime;

void Sonar_initialize(void)
{
  pinMode(SONAR_TRIG_PIN, OUTPUT); 
  pinMode(SONAR_ECHO_PIN, INPUT); 
}
double SonarDistanceMeasurement(void) 
{

	//Low -> high -> low level to send a short pulse to TrigPin
	digitalWrite(SONAR_TRIG_PIN, LOW);                    //let TrigPin at a low potential
	delayMicroseconds(2);                          //delay for a short time
	digitalWrite(SONAR_TRIG_PIN, HIGH);                   //let TrigPin at a high potential
	delayMicroseconds(10); 
	digitalWrite(SONAR_TRIG_PIN, LOW);

	//calculate distance
  //StartTime = millis();
  unsigned long PulseDelay = pulseIn(SONAR_ECHO_PIN, HIGH, TimeOut * 1000);
  //unsigned long PulseDelay = 0;
	DistancetoWall = PulseDelay * 0.034 / 2;           //the echo time is converted into cm
  //StopTime = millis();
  if(DistancetoWall <= 0)
  {
    DistancetoWall = 999.0;
  }
  /*if(StopTime - StartTime >= (TimeOut))
  {
    DistancetoWall = 999;
  }*/
}
