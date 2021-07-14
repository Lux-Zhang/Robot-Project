#ifndef RTW_HEADER_DistanceMeasurement_h_
#define RTW_HEADER_DistanceMeasurement_h_
#ifndef DistanceMeasurement_COMMON_INCLUDES_
# define DistanceMeasurement_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif

typedef struct {
  real_T Integrator1_DSTATE;
} DistanceMeasurement_DW;

extern real_T LeftMotorSpeed;
extern real_T RightMotorSpeed;
extern DistanceMeasurement_DW rtDistanceMeasurement_DW;
extern real_T Distance;

#ifdef __cplusplus

extern "C" {

#endif

  extern void DistanceMeasurement_initialize(void);
  extern void DistanceMeasurement_step(void);
  extern void DistanceMeasurement_terminate(void);

#ifdef __cplusplus

}
#endif
#endif

