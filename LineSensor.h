#ifndef RTW_HEADER_LineSensor_h_
#define RTW_HEADER_LineSensor_h_
#include <math.h>
#ifndef LineSensor_COMMON_INCLUDES_
# define LineSensor_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif

#include <SPI.h>

extern const int LEFT_LINE_PATROL_OUTSIDE_SENSOR;
extern const int LEFT_LINE_PATROL_INSIDE_SENSOR;
extern const int RIGHT_LINE_PATROL_INSIDE_SENSOR;
extern const int RIGHT_LINE_PATROL_OUTSIDE_SENSOR;
extern void GetLuminance(void);
extern real_T LeftLuminanceInside;
extern real_T RightLuminanceInside;
extern real_T LeftLuminanceOutside;
extern real_T RightLuminanceOutside;
extern real_T LinePatrolSensorOutput;
extern void LineSensor_initialize(void);
extern void LineSensor_step(void);
extern void LineSensor_terminate(void);

#endif

