#ifndef RTW_HEADER_BeaconSearchSensor_h_
#define RTW_HEADER_BeaconSearchSensor_h_
#include "rtwtypes.h"
#include <math.h>
#ifndef BeaconSearchSensor_COMMON_INCLUDES_
# define BeaconSearchSensor_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif

#include <SPI.h>
#include <Servo.h>

extern const int LEFT_BEACON_SEARCH_SENSOR;
extern const int RIGHT_BEACON_SEARCH_SENSOR;
extern const int BEACON_SEARCH_SERVO_PIN;
extern volatile double BeaconSearchServoAngle;
extern void GetBeaconLuminance(void);
extern void BeaconTrace(void);

#ifndef typedef_dsp_private_ExponentialMovingAv
#define typedef_dsp_private_ExponentialMovingAv

typedef struct {
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  real_T ForgettingFactor;
  real_T pwN;
  real_T pmN;
  real_T plambda;
} dsp_private_ExponentialMovingAv;

#endif

#ifndef typedef_BeaconSearchSensor_cell_wrap
#define typedef_BeaconSearchSensor_cell_wrap

typedef struct {
  uint32_T f1[8];
} BeaconSearchSensor_cell_wrap;

#endif

#ifndef typedef_BeaconSe_dsp_simulink_MovingRMS
#define typedef_BeaconSe_dsp_simulink_MovingRMS

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  BeaconSearchSensor_cell_wrap inputVarSize;
  real_T ForgettingFactor;
  dsp_private_ExponentialMovingAv *pStatistic;
  int32_T NumChannels;
} BeaconSe_dsp_simulink_MovingRMS;

#endif

typedef struct {
  BeaconSe_dsp_simulink_MovingRMS obj;
  dsp_private_ExponentialMovingAv gobj_0;
  dsp_private_ExponentialMovingAv gobj_1;
  real_T MovingRMS1_h;
  boolean_T objisempty;
} BeaconSearchSenso_DW_MovingRMS1;

typedef struct {
  BeaconSearchSenso_DW_MovingRMS1 MovingRMS;
  BeaconSearchSenso_DW_MovingRMS1 MovingRMS1_p;
} BeaconSearchSensor_DW;

extern real_T RightBeaconLuminance;
extern real_T LeftBeaconLuminance;
extern BeaconSearchSensor_DW rtBeaconSearchSensor_DW;
extern real_T BeaconDirection;
extern real_T BeaconSearchSensorOutput;
extern real_T RightRMS;
extern real_T LeftRMS;
extern void BeaconSearchSensor_initialize(void);
extern void BeaconSearchSensor_step(void);
extern void BeaconSearchSensor_terminate(void);

#endif

