#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"

#include "../../MCAL/MTIMER/MPWM/MPWM_interface.h"

#include "HServoMotor_interface.h"

static MPWM HServoMotor_Obj;

void HServoMotor_voidInit(void)
{
	HServoMotor_Obj.u16Obj_InitialDutyCycleValue = 20;
	HServoMotor_Obj.enumObj_Num = MPWM_Num2;
	HServoMotor_Obj.enumObj_OPFormat = MPWM_Inverted;
	HServoMotor_Obj.enumObj_PWMMode = MPWM_FastPWM;
	HServoMotor_Obj.enumObj_State = MTIMER_Free;
	
	MPWM_voidInit(&HServoMotor_Obj);
}

void HServo_voidSetAngle(u8 u8Cpy_Angle)
{
	MPWM_voidSetDutyCycle(&HServoMotor_Obj,u8Cpy_Angle);
}

void HServo_voidStopMotor(void)
{
	MPWM_voidStopPWM(&HServoMotor_Obj);
}

