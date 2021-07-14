#ifndef HEADER_PINCONFIGURATION_H_
#define HEADER_PINCONFIGURATION_H_

#define A0 54
#define A1 55
#define A2 56
#define A3 57
#define A4 58
#define A5 59
#define A6 60
#define A7 61
#define A8 62
#define A9 63
#define A10 64
#define A11 65
#define A12 66
#define A13 67
#define A14 68
#define A15 69

const int LEFT_ENCODER_A = 19;
const int LEFT_ENCODER_B = 17;
const int RIGHT_ENCODER_A = 18;
const int RIGHT_ENCODER_B = 16;

const int SONAR_TRIG_PIN = 7; 
const int SONAR_ECHO_PIN = 8;

const int OLED_SDA = 20;
const int OLED_SCL = 21;

const int LEFT_MOTOR_DRIVE_PIN = 4;
const int RIGHT_MOTOR_DRIVE_PIN = 5;

const int LEFT_MOTOR_IO_PIN = 22;
const int RIGHT_MOTOR_IO_PIN = 23;

const int BEACON_SEARCH_SERVO_PIN = 11;
const int UNLOAD_SERVO_PIN = 12;

const int BUZZER_PIN = 26;

const int SWITCH_PIN = 28;

const int LEFT_LINE_PATROL_OUTSIDE_SENSOR = A0;
const int LEFT_LINE_PATROL_INSIDE_SENSOR = A1;
const int RIGHT_LINE_PATROL_INSIDE_SENSOR = A2;
const int RIGHT_LINE_PATROL_OUTSIDE_SENSOR = A3;

const int LEFT_BEACON_SEARCH_SENSOR = A13;
//const int CENTER_BEACON_SEARCH_SENSOR = A14;
const int RIGHT_BEACON_SEARCH_SENSOR = A14;

#endif
