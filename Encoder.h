#include <SPI.h>

#include "rtwtypes.h"

extern real_T LeftMotorSpeed;
extern real_T RightMotorSpeed;


extern const int LEFT_ENCODER_A;
extern const int LEFT_ENCODER_B;
extern const int RIGHT_ENCODER_A;
extern const int RIGHT_ENCODER_B;


extern void Encoder_initialize(void);
extern void LeftEncoder(void);
extern void RightEncoder(void);
extern void EncoderIsr(void);
