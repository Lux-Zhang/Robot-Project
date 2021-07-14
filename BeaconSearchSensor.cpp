#include "BeaconSearchSensor.h"

Servo BeaconSearchServo;
void GetBeaconLuminance(void)
{
  LeftBeaconLuminance = analogRead(LEFT_BEACON_SEARCH_SENSOR);
  RightBeaconLuminance = analogRead(RIGHT_BEACON_SEARCH_SENSOR);
}

void BeaconTrace(void)
{
  BeaconSearchServoAngle = BeaconSearchServoAngle + BeaconSearchSensorOutput;
  if (BeaconSearchServoAngle < 0) {
    BeaconSearchServoAngle = 0;
  }

  if (BeaconSearchServoAngle >180) {
    BeaconSearchServoAngle = 180;
  }

  BeaconSearchServo.write(BeaconSearchServoAngle);
}

real_T BeaconDirection;
real_T BeaconSearchSensorOutput;
real_T RightRMS;
real_T LeftRMS;
BeaconSearchSensor_DW rtBeaconSearchSensor_DW;
static void MovingRMS1_Init(BeaconSearchSenso_DW_MovingRMS1 *localDW);
static void MovingRMS1_Start(BeaconSearchSenso_DW_MovingRMS1 *localDW);
static void MovingRMS1(real_T rtu_0, BeaconSearchSenso_DW_MovingRMS1 *localDW);
static void MovingRMS1_Term(BeaconSearchSenso_DW_MovingRMS1 *localDW);
static void SystemCore_release(BeaconSe_dsp_simulink_MovingRMS *obj);
static void SystemCore_delete(BeaconSe_dsp_simulink_MovingRMS *obj);
static void matlabCodegenHandle_matlabCodeg(BeaconSe_dsp_simulink_MovingRMS *obj);
static void SystemCore_release(BeaconSe_dsp_simulink_MovingRMS *obj)
{
  dsp_private_ExponentialMovingAv *obj_0;
  if ((obj->isInitialized == 1L) && obj->isSetupComplete) {
    obj_0 = obj->pStatistic;
    if (obj_0->isInitialized == 1L) {
      obj_0->isInitialized = 2L;
    }

    obj->NumChannels = -1L;
  }
}

static void SystemCore_delete(BeaconSe_dsp_simulink_MovingRMS *obj)
{
  SystemCore_release(obj);
}

static void matlabCodegenHandle_matlabCodeg(BeaconSe_dsp_simulink_MovingRMS *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    SystemCore_delete(obj);
  }
}

static void MovingRMS1_Init(BeaconSearchSenso_DW_MovingRMS1 *localDW)
{
  if (localDW->obj.pStatistic->isInitialized == 1L) {
    localDW->obj.pStatistic->pwN = 1.0;
    localDW->obj.pStatistic->pmN = 0.0;
  }
}

static void MovingRMS1_Start(BeaconSearchSenso_DW_MovingRMS1 *localDW)
{
  boolean_T flag;
  localDW->obj.matlabCodegenIsDeleted = true;
  localDW->obj.isInitialized = 0L;
  localDW->obj.NumChannels = -1L;
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->objisempty = true;
  if (localDW->obj.isInitialized == 1L) {
    localDW->obj.TunablePropsChanged = true;
  }

  localDW->obj.ForgettingFactor = 0.9;
  localDW->obj.isSetupComplete = false;
  localDW->obj.isInitialized = 1L;
  localDW->obj.NumChannels = 1L;
  localDW->gobj_0.isInitialized = 0L;
  flag = (localDW->gobj_0.isInitialized == 1L);
  if (flag) {
    localDW->gobj_0.TunablePropsChanged = true;
  }

  if (localDW->obj.ForgettingFactor != 0.0) {
    localDW->gobj_0.ForgettingFactor = localDW->obj.ForgettingFactor;
  } else {
    localDW->gobj_0.ForgettingFactor = 2.2204460492503131E-16;
  }

  localDW->obj.pStatistic = &localDW->gobj_0;
  localDW->obj.isSetupComplete = true;
  localDW->obj.TunablePropsChanged = false;
}

static void MovingRMS1(real_T rtu_0, BeaconSearchSenso_DW_MovingRMS1 *localDW)
{
  boolean_T flag;
  real_T y;
  real_T pwLocal;
  real_T pmLocal;
  real_T lambda;
  if (localDW->obj.ForgettingFactor != 0.9) {
    if (localDW->obj.isInitialized == 1L) {
      localDW->obj.TunablePropsChanged = true;
    }

    localDW->obj.ForgettingFactor = 0.9;
  }

  if (localDW->obj.TunablePropsChanged) {
    localDW->obj.TunablePropsChanged = false;
    flag = (localDW->obj.pStatistic->isInitialized == 1L);
    if (flag) {
      localDW->obj.pStatistic->TunablePropsChanged = true;
    }

    localDW->obj.pStatistic->ForgettingFactor = localDW->obj.ForgettingFactor;
  }

  y = fabs(rtu_0);
  if (localDW->obj.pStatistic->isInitialized != 1L) {
    localDW->obj.pStatistic->isSetupComplete = false;
    localDW->obj.pStatistic->isInitialized = 1L;
    localDW->obj.pStatistic->pwN = 1.0;
    localDW->obj.pStatistic->pmN = 0.0;
    localDW->obj.pStatistic->plambda = localDW->obj.pStatistic->ForgettingFactor;
    localDW->obj.pStatistic->isSetupComplete = true;
    localDW->obj.pStatistic->TunablePropsChanged = false;
    localDW->obj.pStatistic->pwN = 1.0;
    localDW->obj.pStatistic->pmN = 0.0;
  }

  if (localDW->obj.pStatistic->TunablePropsChanged) {
    localDW->obj.pStatistic->TunablePropsChanged = false;
    localDW->obj.pStatistic->plambda = localDW->obj.pStatistic->ForgettingFactor;
  }

  pwLocal = localDW->obj.pStatistic->pwN;
  pmLocal = localDW->obj.pStatistic->pmN;
  lambda = localDW->obj.pStatistic->plambda;
  y = (1.0 - 1.0 / pwLocal) * pmLocal + 1.0 / pwLocal * (y * y);
  localDW->obj.pStatistic->pwN = lambda * pwLocal + 1.0;
  localDW->obj.pStatistic->pmN = y;
  localDW->MovingRMS1_h = sqrt(y);
}

static void MovingRMS1_Term(BeaconSearchSenso_DW_MovingRMS1 *localDW)
{
  matlabCodegenHandle_matlabCodeg(&localDW->obj);
}

void BeaconSearchSensor_step(void)
{
  real_T rtb_SignedSqrt;
  MovingRMS1(LeftBeaconLuminance, &rtBeaconSearchSensor_DW.MovingRMS);
  MovingRMS1(RightBeaconLuminance, &rtBeaconSearchSensor_DW.MovingRMS1_p);
  BeaconDirection = (rtBeaconSearchSensor_DW.MovingRMS.MovingRMS1_h -
                     rtBeaconSearchSensor_DW.MovingRMS1_p.MovingRMS1_h) /
    ((rtBeaconSearchSensor_DW.MovingRMS.MovingRMS1_h +
      rtBeaconSearchSensor_DW.MovingRMS1_p.MovingRMS1_h) * 0.5);
  if (BeaconDirection > 0.01) {
    rtb_SignedSqrt = BeaconDirection - 0.01;
  } else if (BeaconDirection >= -0.01) {
    rtb_SignedSqrt = 0.0;
  } else {
    rtb_SignedSqrt = BeaconDirection - -0.01;
  }

  if (rtb_SignedSqrt < 0.0) {
    rtb_SignedSqrt = -sqrt(fabs(rtb_SignedSqrt));
  } else {
    rtb_SignedSqrt = sqrt(rtb_SignedSqrt);
  }

  BeaconSearchSensorOutput = 6.0 * rtb_SignedSqrt;
  RightRMS = log(rtBeaconSearchSensor_DW.MovingRMS1_p.MovingRMS1_h);
  LeftRMS = log(rtBeaconSearchSensor_DW.MovingRMS.MovingRMS1_h);
}

void BeaconSearchSensor_initialize(void)
{
  MovingRMS1_Start(&rtBeaconSearchSensor_DW.MovingRMS);
  MovingRMS1_Start(&rtBeaconSearchSensor_DW.MovingRMS1_p);
  MovingRMS1_Init(&rtBeaconSearchSensor_DW.MovingRMS);
  MovingRMS1_Init(&rtBeaconSearchSensor_DW.MovingRMS1_p);
  pinMode(LEFT_BEACON_SEARCH_SENSOR, INPUT);
  pinMode(RIGHT_BEACON_SEARCH_SENSOR, INPUT);
  BeaconSearchServo.attach(BEACON_SEARCH_SERVO_PIN);
  BeaconSearchServo.write(90);
  BeaconSearchServoAngle = 90;
}

void BeaconSearchSensor_terminate(void)
{
  MovingRMS1_Term(&rtBeaconSearchSensor_DW.MovingRMS);
  MovingRMS1_Term(&rtBeaconSearchSensor_DW.MovingRMS1_p);
}
