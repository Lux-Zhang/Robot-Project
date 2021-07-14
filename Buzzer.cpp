#include "Buzzer.h" 

int BuzzTime;

void Buzzer_initialize(void) 
 
{  
  pinMode(BUZZER_PIN,OUTPUT);
} 

void SetBuzzTime(int StepTime)
{
  BuzzTime = StepTime; // every step 10ms
}
 
void BuzzIsr(void) 
{   
  if(BuzzTime <= 0)
  {
    digitalWrite(BUZZER_PIN, LOW);
  }
  else
  {
    digitalWrite(BUZZER_PIN, HIGH);
    BuzzTime--;
  }
  //Serial.println(BuzzTime);
}
