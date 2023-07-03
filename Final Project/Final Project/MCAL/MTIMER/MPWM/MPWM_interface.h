#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_

#include "../MTIMER_interface.h"

typedef enum{
	MPWM_Num0, MPWM_Num1, MPWM_Num2
}MPWM_Num;

typedef enum{
	MPWM_FastPWM, MPWM_PhaseCorrect
}MPWM_PWMMode;

typedef enum{
	MPWM_Inverted, MPWM_NonInverted
}MPWM_OPFormat;

typedef struct{
	MPWM_Num			enumObj_Num;
	MPWM_PWMMode		enumObj_PWMMode;
	MPWM_OPFormat	    enumObj_OPFormat;
	MTIMER_State		enumObj_State;
	u16					u16Obj_InitialDutyCycleValue;
}MPWM;

void MPWM_voidInit(MPWM* pstructCpy_PWMObj);
void MPWM_voidSetDutyCycle(MPWM* pstructCpy_PWMObj, u16 u16Cpy_DutyCycleValue);
void MPWM_voidStopPWM(MPWM* pstructCpy_PWMObj);

/*In main:
__________________
void main(void)
{
	MPWM x;
	x.u16Obj_InitialDutyCycleValue = 20;
	x.enumObj_Num = MPWM_Num2;
	x.enumObj_OPFormat = MPWM_Inverted;
	x.enumObj_PWMMode = MPWM_FastPWM;
	x.enumObj_State = MTIMER_Free;
	MPWM_voidInit(&x);
	
	MADC y;
	y.enumObj_Channel = MADC_Ch1;
	y.enumObj_VRef = MADC_AVCC;
	y.enumObj_ConvMode = MADC_AUTO_TRIG_CONV;
	y.enumObj_RegJus = MADC_8BIT;
	y.enumObj_OPFormat = MADC_Digital;
	y.enumObj_Pres = MADC_PS_128;
	y.enumObj_AutoTrigMode = MADC_FreeRunning;
	y.enumObj_OPMode = MADC_POLLING;
	MADC_enuInit(&y);
	MADC_enuStartConv();
	
	HLCD_enuInit();
	HLCD_enuIntegerToString(212,0);
	
	u16 z;
	
	while(1)
	{
		MADC_enuGetConvResult(&z);
		MPWM_voidSetDutyCycle(&x,z);
	}
}*/

#endif /* PWM_INTERFACE_H_ */