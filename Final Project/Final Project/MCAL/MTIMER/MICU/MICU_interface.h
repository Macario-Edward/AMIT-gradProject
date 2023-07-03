#ifndef MICU_INTERFACE_H_
#define MICU_INTERFACE_H_

typedef struct{
	u16 u16Obj_Ton;
	u16 u16Obj_Toff;
	u8  u8Obj_DutyCycle;
}MICU;

void MICU_voidInit(void);
void MICU_voidFetchData(MICU* pstructCpy_ICUObj);

/*
In main:
________
int main(void)
{
	MPWM pwm;
	pwm.u16Obj_InitialDutyCycleValue = 127;
	pwm.enumObj_Num = MPWM_Num2;
	pwm.enumObj_OPFormat = MPWM_Inverted;
	pwm.enumObj_PWMMode = MPWM_FastPWM;
	pwm.enumObj_State = MTIMER_Free;
	MPWM_voidInit(&pwm);
	
	MICU_voidInit();//must be before LCD Init, so that it takes time to read data
	HLCD_enuInit();
	
	MICU g;
	MICU_voidFetchData(&g);
	
	HLCD_enuIntegerToString(g.u16Obj_Ton, &HLCDArrayOfLCD[HLCD_NUM0]);
	HLCD_enuGoToXY(HLCD_u8SecRow, HLCD_u8FirstCol, &HLCDArrayOfLCD[HLCD_NUM0]);
	HLCD_enuIntegerToString(g.u16Obj_Toff, &HLCDArrayOfLCD[HLCD_NUM0]);
	
	while (1)
	{
	}
}
*/

#endif /* MICU_INTERFACE_H_ */