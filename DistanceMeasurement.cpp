#include "DistanceMeasurement.h"

real_T Distance;
DistanceMeasurement_DW rtDistanceMeasurement_DW;
void DistanceMeasurement_step(void)
{
  Distance = rtDistanceMeasurement_DW.Integrator1_DSTATE;
  rtDistanceMeasurement_DW.Integrator1_DSTATE += (LeftMotorSpeed +
    RightMotorSpeed) * 0.5 * 0.05;
}

void DistanceMeasurement_initialize(void)
{
}

void DistanceMeasurement_terminate(void)
{
}
