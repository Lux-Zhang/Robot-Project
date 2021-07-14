#include <SPI.h>
extern const int BUZZER_PIN;

extern void Buzzer_initialize(void);
extern void SetBuzzTime(int StepTime);
extern void BuzzIsr(void);
