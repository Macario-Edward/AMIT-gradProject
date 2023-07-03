#include "../../../Libraries_/LIB_STDTypes.h"
#include "../../../Libraries_/LIB_BMNP.h"

#include <avr/interrupt.h>

#include "../MTIMER_registers.h"
#include "../MTIMER_interface.h"
#include "MTimerCounter_config.h"
#include "MTimerCounter_interface.h"

static u32 MTimerCounter_u32Tim0OVFCounter = 0;
static u32 MTimerCounter_u32Tim1OVFCounter = 0;
static u32 MTimerCounter_u32Tim2OVFCounter = 0;

/*******************************************************************************/

static void MTimerCounter_voidIncTim0OVFCounter(void)
{
	MTimerCounter_u32Tim0OVFCounter++;
}

static void MTimerCounter_voidIncTim1OVFCounter(void)
{
	MTimerCounter_u32Tim1OVFCounter++;
}

static void MTimerCounter_voidIncTim2OVFCounter(void)
{
	MTimerCounter_u32Tim2OVFCounter++;
}

/*******************************************************************************/

void MTimerCounter_voidDelay(u32 u32Cpy_DelayTime, MTimerCounter* pstructCpy_TimerObj)
{
	f32 f32Local_TimeTillOVF = 0;
	if(pstructCpy_TimerObj->enumObj_TimeFormat == MTimerCounter_Ms)
		f32Local_TimeTillOVF  = 4.096;/*time till overflow (0 -> 2^n) in millisecond =
									timer tick time in seconds (prescaler/system clock) [256 for timer0 & timer2, and 1 for timer1] / 16 MHz sys clock*
									how many ticks till overflow (256 for timer0  & timer2, and 65536 for timer1) *
									1000 (to convert second to millisecond)*/
	else if(pstructCpy_TimerObj->enumObj_TimeFormat == MTimerCounter_Us)
		f32Local_TimeTillOVF = 4096;/*time till overflow (0 -> 2^n) in microsecond =
									timer tick time in seconds (prescaler/system clock) [256 for timer0 & timer2, and 1 for timer1] / 16 MHz sys clock*
									how many ticks till overflow (256 for timer0  & timer2, and 65536 for timer1) *
									1000000 (to convert second to microsecond)*/
	f32 f32Local_OVFLoops = 0;
	u32 u32Local_OVFLoops = 0;
	
	if((pstructCpy_TimerObj != NULL) && 
	   (pstructCpy_TimerObj->enumObj_State == MTIMER_Free))
	{
		switch(pstructCpy_TimerObj->enumObj_Num)
		{
			case MTimerCounter_Num0:
				TCCR0 = 0x04;//timer with prescaler 256
				TCNT0 = 0x00;//reset timer/counter register
				CLR_BIT(TIMSK,0);// disable overflow interrupt for timer0 (polling)					
				break;
				
			case MTimerCounter_Num1:
				TCCR1B = 0x01;//timer with prescaler 1
				TCCR1A = 0x00;
				TCNT1H = 0x00;//To do a 16-bit write, the high byte must be written before the low byte.
				TCNT1L = 0x00;//reset timer/counter register
				CLR_BIT(TIMSK,2);// disable overflow interrupt for timer1 (polling)	
				break;
				
			case MTimerCounter_Num2:
				TCCR2 = 0x06;//timer with prescaler 256
				TCNT2 = 0x00;//reset timer/counter register
				CLR_BIT(TIMSK,6);// disable overflow interrupt for timer2 (polling)	
				break;
			
			default:
				break;
		}
		
		u32Local_OVFLoops = (u32)(u32Cpy_DelayTime/f32Local_TimeTillOVF);
		f32Local_OVFLoops = (f32)u32Cpy_DelayTime/f32Local_TimeTillOVF;	
		f32Local_OVFLoops = f32Local_OVFLoops - u32Local_OVFLoops;
		
		if(f32Local_OVFLoops != 0)//take care of fraction part if exists
		{
			//f32Local_OVFLoops = (f32)u32Cpy_DelayMs/f32Local_OVFInMs;
			
			//f32Local_OVFLoops = f32Local_OVFLoops - u32Local_OVFLoops;//get the fraction part only
			f32Local_OVFLoops = 1 - f32Local_OVFLoops;
			
			if(pstructCpy_TimerObj->enumObj_Num == MTimerCounter_Num1)
			{
				u32Local_OVFLoops = (u16)(f32Local_OVFLoops* 65536);
				TCNT1H = u32Local_OVFLoops >> 16;
				TCNT1L = u32Local_OVFLoops;
			}
			else if(pstructCpy_TimerObj->enumObj_Num == MTimerCounter_Num0)
			{
				TCNT0 = (u8)(f32Local_OVFLoops* 256);
			}
			else if(pstructCpy_TimerObj->enumObj_Num == MTimerCounter_Num2)
			{
				TCNT2 = (u8)(f32Local_OVFLoops* 256);
			}
			
			u32Local_OVFLoops = (u32)(u32Cpy_DelayTime/f32Local_TimeTillOVF);
			u32Local_OVFLoops++;//due to the fraction part
		}
		
		while(u32Local_OVFLoops != 0)
		{
			switch(pstructCpy_TimerObj->enumObj_Num)
			{
				case MTimerCounter_Num0:
					while(!GET_BIT(TIFR,0));
					SET_BIT(TIFR,0);//clear TOV0 flag
					break;
					
				case MTimerCounter_Num1:
					while(!GET_BIT(TIFR,2));
					SET_BIT(TIFR,2);//clear TOV1 flag
					break;
					
				case MTimerCounter_Num2:
					while(!GET_BIT(TIFR,6));
					SET_BIT(TIFR,6);//clear TOV2 flag
					break;
					
				default:
					break;
			}
				
			u32Local_OVFLoops--;
		}
	}
}

/******************************************************************/

void MTimerCounter_voidStartTimer(MTimerCounter* pstructCpy_TimerObj)
{
	if((pstructCpy_TimerObj != NULL) &&
	   (pstructCpy_TimerObj->enumObj_State == MTIMER_Free))
	{
		pstructCpy_TimerObj->enumObj_State = MTIMER_Busy;
		switch(pstructCpy_TimerObj->enumObj_Num)
		{
			case MTimerCounter_Num0:
				MTimerCounter_u32Tim0OVFCounter = 0;
				MTIMER_voidTIM0OVFSetCallBack(MTimerCounter_voidIncTim0OVFCounter);
				TCCR0 = 0x05;//timer with prescaler 1024
				TCNT0 = 0x00;//reset timer/counter register
				SET_BIT(TIMSK,0);// enable overflow interrupt for timer0 (polling)
				break;
			
			case MTimerCounter_Num1:
				MTimerCounter_u32Tim1OVFCounter = 0;
				MTIMER_voidTIM1OVFSetCallBack(MTimerCounter_voidIncTim1OVFCounter);
				TCCR1B = 0x05;//timer with prescaler 1024
				TCCR1A = 0x00;
				TCNT1H = 0x00;//To do a 16-bit write, the high byte must be written before the low byte.
				TCNT1L = 0x00;//reset timer/counter register
				SET_BIT(TIMSK,2);// enable overflow interrupt for timer1 (polling)
				break;
			
			case MTimerCounter_Num2:
				MTimerCounter_u32Tim2OVFCounter = 0;
				MTIMER_voidTIM2OVFSetCallBack(MTimerCounter_voidIncTim2OVFCounter);
				TCCR2 = 0x07;//timer with prescaler 1024
				TCNT2 = 0x00;//reset timer/counter register
				SET_BIT(TIMSK,6);// enable overflow interrupt for timer2 (polling)
				break;
			
			default:
				break;
		}
	}
}

void MTimerCounter_voidStopTimer(MTimerCounter* pstructCpy_TimerObj)
{
	if((pstructCpy_TimerObj != NULL) &&
	(pstructCpy_TimerObj->enumObj_State == MTIMER_Busy))
	{
		switch(pstructCpy_TimerObj->enumObj_Num)
		{
			case MTimerCounter_Num0:
				TCCR0 = 0x00;
				break;
			
			case MTimerCounter_Num1:
				TCCR1B = 0x00;
				TCCR1A = 0x00;
				break;
			
			case MTimerCounter_Num2:
				TCCR2 = 0x00;
				break;
			
			default:
				break;
		}
	}
}

void MTimerCounter_voidContinueTimer(MTimerCounter* pstructCpy_TimerObj)
{
	if((pstructCpy_TimerObj != NULL) &&
	(pstructCpy_TimerObj->enumObj_State == MTIMER_Busy))
	{
		switch(pstructCpy_TimerObj->enumObj_Num)
		{
			case MTimerCounter_Num0:
				TCCR0 = 0x05;//timer with prescaler 1024
				break;
			
			case MTimerCounter_Num1:
				TCCR1B = 0x05;//timer with prescaler 1024
				TCCR1A = 0x00;
				break;
			
			case MTimerCounter_Num2:
				TCCR2 = 0x07;//timer with prescaler 1024
				break;
			
			default:
				break;
		}
	}
}

f32  MTimerCounter_f32GetTimerValue(MTimerCounter* pstructCpy_TimerObj)
{
	u16 u16Local_Counts = 0;
	f32 f32Local_Time = 0;
	u8 u8Local_Temp;
	f32 f32Local_OVFTime = 0;
	
	if((pstructCpy_TimerObj != NULL) &&
	(pstructCpy_TimerObj->enumObj_State == MTIMER_Busy))
	{
		switch(pstructCpy_TimerObj->enumObj_Num)
		{
			case MTimerCounter_Num0:
				TCCR0 = 0x00;//stop the timer0
				u16Local_Counts = TCNT0;
				f32Local_OVFTime = OVF_TIME_8BIT_MS * MTimerCounter_u32Tim0OVFCounter;
				break;
			
			case MTimerCounter_Num1:
				TCCR1B = 0x00;//stop the timer1
				TCCR1A = 0x00;
				u8Local_Temp    = TCNT1L;//for 16 bit registers, you must read the low byte first then the high byte, according to the data sheet
				u16Local_Counts = TCNT1H;
				u16Local_Counts = (u16Local_Counts << 8) | u8Local_Temp;
				f32Local_OVFTime = OVF_TIME_16BIT_MS * MTimerCounter_u32Tim1OVFCounter;
				break;
			
			case MTimerCounter_Num2:
				TCCR2 = 0x00;//stop the timer2
				u16Local_Counts = TCNT2;
				f32Local_OVFTime = OVF_TIME_8BIT_MS * MTimerCounter_u32Tim2OVFCounter;
				break;
			
			default:
				break;
		}
	}
	
	if(pstructCpy_TimerObj->enumObj_TimeFormat == MTimerCounter_Ms)
		f32Local_Time     = (u16Local_Counts * 1.024)/SYS_CLK;//time in milliseconds
	else if(pstructCpy_TimerObj->enumObj_TimeFormat == MTimerCounter_Us)
		f32Local_Time     = (u16Local_Counts * 1024)/SYS_CLK;//time in microseconds
	
	f32Local_Time+= f32Local_OVFTime;
	
	pstructCpy_TimerObj->enumObj_State = MTIMER_Free;
	
	return f32Local_Time;
}

/******************************************************************/

void MTimerCounter_voidStartCounter(MTimerCounter* pstructCpy_CounterObj)
{
	if((pstructCpy_CounterObj != NULL) &&
	(pstructCpy_CounterObj->enumObj_State == MTIMER_Free))
	{
		pstructCpy_CounterObj->enumObj_State = MTIMER_Busy;
		switch(pstructCpy_CounterObj->enumObj_Num)
		{
			case MTimerCounter_Num0:
				if(pstructCpy_CounterObj->enumObj_CounterMode == MTimerCounter_FallingEdge)
					TCCR0 = 0x06;//Counting on falling edge
				else if(pstructCpy_CounterObj->enumObj_CounterMode == MTimerCounter_RisingEdge)
					TCCR0 = 0x07;//Counting on rising edge	
					
				TCNT0 = 0x00;//reset timer/counter register
				CLR_BIT(TIMSK,0);// disable overflow interrupt for timer0 (polling)
				break;
			
			case MTimerCounter_Num1:
				if(pstructCpy_CounterObj->enumObj_CounterMode == MTimerCounter_FallingEdge)
					TCCR1B = 0x06;//Counting on falling edge
				else if(pstructCpy_CounterObj->enumObj_CounterMode == MTimerCounter_RisingEdge)
					TCCR1B = 0x07;//Counting on rising edge
				TCCR1A = 0x00;
				TCNT1H = 0x00;//To do a 16-bit write, the high byte must be written before the low byte.
				TCNT1L = 0x00;//reset timer/counter register
				CLR_BIT(TIMSK,2);// disable overflow interrupt for timer1 (polling)
				break;
			
			default:
				break;
		}
	}
}

void MTimerCounter_voidStopCounter(MTimerCounter* pstructCpy_CounterObj)
{
	if((pstructCpy_CounterObj != NULL) &&
	(pstructCpy_CounterObj->enumObj_State == MTIMER_Busy))
	{
		switch(pstructCpy_CounterObj->enumObj_Num)
		{
			case MTimerCounter_Num0:
				TCCR0 = 0x00;//stop counter
				break;
			
			case MTimerCounter_Num1:
				TCCR1B = 0x00;//stop counter
				TCCR1A = 0x00;
				break;
			
			default:
				break;
		}
		pstructCpy_CounterObj->enumObj_State = MTIMER_Free;
	}
}

u16  MTimerCounter_u16GetCounterValue(MTimerCounter* pstructCpy_CounterObj)
{
	u16 u16Local_Counts = 0;
	u8 u8Local_Temp;
	
	if((pstructCpy_CounterObj != NULL) &&
	(pstructCpy_CounterObj->enumObj_State == MTIMER_Busy))
	{
		switch(pstructCpy_CounterObj->enumObj_Num)
		{
			case MTimerCounter_Num0:
				u16Local_Counts = TCNT0;
				break;
			
			case MTimerCounter_Num1:
				u8Local_Temp    = TCNT1L;//for 16 bit registers, you must read the low byte first then the high byte, according to the data sheet
				u16Local_Counts = TCNT1H;
				u16Local_Counts = (u16Local_Counts << 8) | u8Local_Temp;
				break;
			
			default:
				break;
		}
	}
	
	return u16Local_Counts;
}

/******************************************************************/

/*
ISR(TIMER0_OVF_vect)
{
	MTimerCounter_u32Tim0OVFCounter++;
}

ISR(TIMER1_OVF_vect)
{
	MTimerCounter_u32Tim1OVFCounter++;
}

ISR(TIMER2_OVF_vect)
{
	MTimerCounter_u32Tim2OVFCounter++;
}
*/
