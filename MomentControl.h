#ifndef RTW_HEADER_MomentControl_h_
#define RTW_HEADER_MomentControl_h_
#include <stddef.h>
#ifndef MomentControl_COMMON_INCLUDES_
# define MomentControl_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif

typedef struct {
  real_T Integrator_DSTATE;
  real_T UD_DSTATE;
  real_T Integrator_DSTATE_h;
  real_T Filter_DSTATE;
  real_T Integrator_DSTATE_c;
  real_T Filter_DSTATE_g;
} MomentControl_DW;

extern real_T Direction;
extern real_T LeftMotorSpeed;
extern real_T RightMotorSpeed;
extern real_T ExpectSpeed;
extern MomentControl_DW rtMomentControl_DW;
extern real_T LeftMotorOutput;
extern real_T RightMotorOutput;

#ifdef __cplusplus

extern "C" {

#endif

  extern void MomentControl_initialize(void);
  extern void MomentControl_step(void);
  extern void MomentControl_terminate(void);

#ifdef __cplusplus

}
#endif
#endif

