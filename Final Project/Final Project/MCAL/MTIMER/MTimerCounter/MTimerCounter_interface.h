#ifndef TIMERCOUNTER_INTERFACE_H_
#define TIMERCOUNTER_INTERFACE_H_

#include "../MTIMER_interface.h"

typedef enum{
	MTimerCounter_Num0, MTimerCounter_Num1, MTimerCounter_Num2	
}MTimerCounter_Num;

typedef enum{
	MTimerCounter_Ms, MTimerCounter_Us
}MTimerCounter_TimeFormat;

typedef enum{
	MTimerCounter_FallingEdge, MTimerCounter_RisingEdge
}MTimerCounter_CounterMode;

typedef struct{
	MTimerCounter_Num			enumObj_Num;
	MTIMER_State				enumObj_State;
	MTimerCounter_TimeFormat    enumObj_TimeFormat;
	MTimerCounter_CounterMode	enumObj_CounterMode;
}MTimerCounter;

void MTimerCounter_voidDelay(u32 u32Cpy_DelayMs, MTimerCounter* pstructCpy_TimerObj);

void MTimerCounter_voidStartTimer(MTimerCounter* pstructCpy_TimerObj);
void MTimerCounter_voidStopTimer(MTimerCounter* pstructCpy_TimerObj);
void MTimerCounter_voidContinueTimer(MTimerCounter* pstructCpy_TimerObj);
f32  MTimerCounter_f32GetTimerValue(MTimerCounter* pstructCpy_TimerObj);

void MTimerCounter_voidStartCounter(MTimerCounter* pstructCpy_CounterObj);
void MTimerCounter_voidStopCounter(MTimerCounter* pstructCpy_CounterObj);
u16  MTimerCounter_u16GetCounterValue(MTimerCounter* pstructCpy_CounterObj);

/*Simple Application in main:
______________________________
void main(void)
{
	Hled_voidInitArr();
	
	MTimerCounter x;
	x.enumObj_Num	= MTimerCounter_Num2;
	x.enumObj_State = MTIMER_Free;
	x.enumObj_TimeFormat = MTimerCounter_Ms;
	
	while(1)
	{
		MTimerCounter_voidDelay(1000, &x);
		Hled_voidToggleLed(&HLED_ArrayOfLeds [0]);
	}
}
*/

#endif /* TIMERCOUNTER_INTERFACE_H_ */