#include "MomentControl.h"
#define NumBitsPerChar                 8U

real_T LeftMotorOutput;
real_T RightMotorOutput;
MomentControl_DW rtMomentControl_DW;
extern "C" {
  extern real_T rtGetNaN(void);
  extern real32_T rtGetNaNF(void);
}
  extern "C"
{
  extern real_T rtInf;
  extern real_T rtMinusInf;
  extern real_T rtNaN;
  extern real32_T rtInfF;
  extern real32_T rtMinusInfF;
  extern real32_T rtNaNF;
  extern void rt_InitInfAndNaN(size_t realSize);
  extern boolean_T rtIsInf(real_T value);
  extern boolean_T rtIsInfF(real32_T value);
  extern boolean_T rtIsNaN(real_T value);
  extern boolean_T rtIsNaNF(real32_T value);
  typedef struct {
    struct {
      uint32_T wordH;
      uint32_T wordL;
    } words;
  } BigEndianIEEEDouble;

  typedef struct {
    struct {
      uint32_T wordL;
      uint32_T wordH;
    } words;
  } LittleEndianIEEEDouble;

  typedef struct {
    union {
      real32_T wordLreal;
      uint32_T wordLuint;
    } wordL;
  } IEEESingle;
}

extern "C" {
  real_T rtInf;
  real_T rtMinusInf;
  real_T rtNaN;
  real32_T rtInfF;
  real32_T rtMinusInfF;
  real32_T rtNaNF;
}
  extern "C"
{
  extern real_T rtGetInf(void);
  extern real32_T rtGetInfF(void);
  extern real_T rtGetMinusInf(void);
  extern real32_T rtGetMinusInfF(void);
}

extern "C" {
  real_T rtGetNaN(void)
  {
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T nan = 0.0;
    if (bitsPerReal == 32U) {
      nan = rtGetNaNF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0xFFF80000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      nan = tmpVal.fltVal;
    }

    return nan;
  }

  real32_T rtGetNaNF(void)
  {
    IEEESingle nanF = { { 0 } };

    nanF.wordL.wordLuint = 0xFFC00000U;
    return nanF.wordL.wordLreal;
  }
}
  extern "C"
{
  void rt_InitInfAndNaN(size_t realSize)
  {
    (void) (realSize);
    rtNaN = rtGetNaN();
    rtNaNF = rtGetNaNF();
    rtInf = rtGetInf();
    rtInfF = rtGetInfF();
    rtMinusInf = rtGetMinusInf();
    rtMinusInfF = rtGetMinusInfF();
  }

  boolean_T rtIsInf(real_T value)
  {
    return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
  }

  boolean_T rtIsInfF(real32_T value)
  {
    return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
  }

  boolean_T rtIsNaN(real_T value)
  {
    boolean_T result = (boolean_T) 0;
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    if (bitsPerReal == 32U) {
      result = rtIsNaNF((real32_T)value);
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.fltVal = value;
      result = (boolean_T)((tmpVal.bitVal.words.wordH & 0x7FF00000) ==
                           0x7FF00000 &&
                           ( (tmpVal.bitVal.words.wordH & 0x000FFFFF) != 0 ||
                            (tmpVal.bitVal.words.wordL != 0) ));
    }

    return result;
  }

  boolean_T rtIsNaNF(real32_T value)
  {
    IEEESingle tmp;
    tmp.wordL.wordLreal = value;
    return (boolean_T)( (tmp.wordL.wordLuint & 0x7F800000) == 0x7F800000 &&
                       (tmp.wordL.wordLuint & 0x007FFFFF) != 0 );
  }
}

extern "C" {
  real_T rtGetInf(void)
  {
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T inf = 0.0;
    if (bitsPerReal == 32U) {
      inf = rtGetInfF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0x7FF00000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      inf = tmpVal.fltVal;
    }

    return inf;
  }

  real32_T rtGetInfF(void)
  {
    IEEESingle infF;
    infF.wordL.wordLuint = 0x7F800000U;
    return infF.wordL.wordLreal;
  }

  real_T rtGetMinusInf(void)
  {
    size_t bitsPerReal = sizeof(real_T) * (NumBitsPerChar);
    real_T minf = 0.0;
    if (bitsPerReal == 32U) {
      minf = rtGetMinusInfF();
    } else {
      union {
        LittleEndianIEEEDouble bitVal;
        real_T fltVal;
      } tmpVal;

      tmpVal.bitVal.words.wordH = 0xFFF00000U;
      tmpVal.bitVal.words.wordL = 0x00000000U;
      minf = tmpVal.fltVal;
    }

    return minf;
  }

  real32_T rtGetMinusInfF(void)
  {
    IEEESingle minfF;
    minfF.wordL.wordLuint = 0xFF800000U;
    return minfF.wordL.wordLreal;
  }
}
  void MomentControl_step(void)
{
  real_T rtb_Filter_c;
  real_T rtb_TSamp;
  real_T rtb_FilterCoefficient;
  real_T rtb_SignPreIntegrator;
  real_T rtb_ZeroGain;
  boolean_T rtb_NotEqual;
  int8_T rtb_DataTypeConv2;
  real_T rtb_ZeroGain_f;
  real_T rtb_FilterCoefficient_tmp;
  rtb_TSamp = 0.0088 * Direction * 20.0;
  rtb_Filter_c = (0.07 * Direction + rtMomentControl_DW.Integrator_DSTATE) +
    (rtb_TSamp - rtMomentControl_DW.UD_DSTATE);
  rtb_FilterCoefficient_tmp = (rtb_Filter_c + 1.0) * ExpectSpeed -
    LeftMotorSpeed;
  rtb_FilterCoefficient = (rtb_FilterCoefficient_tmp * 0.2 -
    rtMomentControl_DW.Filter_DSTATE) * 0.05;
  rtb_SignPreIntegrator = (rtb_FilterCoefficient_tmp * 6.0 +
    rtMomentControl_DW.Integrator_DSTATE_h) + rtb_FilterCoefficient;
  if (rtb_SignPreIntegrator > 2.3) {
    LeftMotorOutput = 2.3;
  } else if (rtb_SignPreIntegrator < -2.3) {
    LeftMotorOutput = -2.3;
  } else {
    LeftMotorOutput = rtb_SignPreIntegrator;
  }

  rtb_ZeroGain = 0.0 * rtb_SignPreIntegrator;
  if (rtb_SignPreIntegrator > 2.3) {
    rtb_SignPreIntegrator -= 2.3;
  } else if (rtb_SignPreIntegrator >= -2.3) {
    rtb_SignPreIntegrator = 0.0;
  } else {
    rtb_SignPreIntegrator -= -2.3;
  }

  rtb_NotEqual = (rtb_ZeroGain != rtb_SignPreIntegrator);
  if (rtb_SignPreIntegrator < 0.0) {
    rtb_SignPreIntegrator = -1.0;
  } else if (rtb_SignPreIntegrator > 0.0) {
    rtb_SignPreIntegrator = 1.0;
  } else if (rtb_SignPreIntegrator == 0.0) {
    rtb_SignPreIntegrator = 0.0;
  } else {
    rtb_SignPreIntegrator = (rtNaN);
  }

  rtb_DataTypeConv2 = (int8_T)rtb_SignPreIntegrator;
  rtb_SignPreIntegrator = rtb_FilterCoefficient_tmp * 0.5;
  if (rtb_SignPreIntegrator < 0.0) {
    rtb_ZeroGain = -1.0;
  } else if (rtb_SignPreIntegrator > 0.0) {
    rtb_ZeroGain = 1.0;
  } else if (rtb_SignPreIntegrator == 0.0) {
    rtb_ZeroGain = 0.0;
  } else {
    rtb_ZeroGain = (rtNaN);
  }

  if (rtb_NotEqual && (rtb_DataTypeConv2 == (int8_T)rtb_ZeroGain)) {
    rtb_SignPreIntegrator = 0.0;
  }

  rtb_FilterCoefficient_tmp = (1.0 - rtb_Filter_c) * ExpectSpeed -
    RightMotorSpeed;
  rtb_Filter_c = (rtb_FilterCoefficient_tmp * 0.2 -
                  rtMomentControl_DW.Filter_DSTATE_g) * 0.05;
  rtb_ZeroGain = (rtb_FilterCoefficient_tmp * 6.0 +
                  rtMomentControl_DW.Integrator_DSTATE_c) + rtb_Filter_c;
  if (rtb_ZeroGain > 2.3) {
    RightMotorOutput = 2.3;
  } else if (rtb_ZeroGain < -2.3) {
    RightMotorOutput = -2.3;
  } else {
    RightMotorOutput = rtb_ZeroGain;
  }

  rtb_ZeroGain_f = 0.0 * rtb_ZeroGain;
  if (rtb_ZeroGain > 2.3) {
    rtb_ZeroGain -= 2.3;
  } else if (rtb_ZeroGain >= -2.3) {
    rtb_ZeroGain = 0.0;
  } else {
    rtb_ZeroGain -= -2.3;
  }

  rtb_NotEqual = (rtb_ZeroGain_f != rtb_ZeroGain);
  if (rtb_ZeroGain < 0.0) {
    rtb_ZeroGain = -1.0;
  } else if (rtb_ZeroGain > 0.0) {
    rtb_ZeroGain = 1.0;
  } else if (rtb_ZeroGain == 0.0) {
    rtb_ZeroGain = 0.0;
  } else {
    rtb_ZeroGain = (rtNaN);
  }

  rtb_DataTypeConv2 = (int8_T)rtb_ZeroGain;
  rtb_ZeroGain = rtb_FilterCoefficient_tmp * 0.5;
  rtMomentControl_DW.Integrator_DSTATE += 0.0 * Direction * 0.05;
  rtMomentControl_DW.UD_DSTATE = rtb_TSamp;
  rtMomentControl_DW.Integrator_DSTATE_h += 0.05 * rtb_SignPreIntegrator;
  rtMomentControl_DW.Filter_DSTATE += 0.05 * rtb_FilterCoefficient;
  if (rtb_ZeroGain < 0.0) {
    rtb_TSamp = -1.0;
  } else if (rtb_ZeroGain > 0.0) {
    rtb_TSamp = 1.0;
  } else if (rtb_ZeroGain == 0.0) {
    rtb_TSamp = 0.0;
  } else {
    rtb_TSamp = (rtNaN);
  }

  if (rtb_NotEqual && (rtb_DataTypeConv2 == (int8_T)rtb_TSamp)) {
    rtb_ZeroGain = 0.0;
  }

  rtMomentControl_DW.Integrator_DSTATE_c += 0.05 * rtb_ZeroGain;
  rtMomentControl_DW.Filter_DSTATE_g += 0.05 * rtb_Filter_c;
}

void MomentControl_initialize(void)
{
  rt_InitInfAndNaN(sizeof(real_T));
}

void MomentControl_terminate(void)
{
}
