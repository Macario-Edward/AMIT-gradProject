#include "../../../Libraries_/LIB_STDTypes.h"
#include "../../../Libraries_/LIB_BMNP.h"

#include "../MTIMER_registers.h"
#include "MPWM_config.h"
#include "MPWM_interface.h"

#include "../../MDIO/MDIO_interface.h"

void MPWM_voidInit(MPWM* pstructCpy_PWMObj)
{
	MDIO_Pin OCn;
	
	if((pstructCpy_PWMObj != NULL) &&
	(pstructCpy_PWMObj->enumObj_State == MTIMER_Free))
	{
		pstructCpy_PWMObj->enumObj_State = MTIMER_Busy;
		switch(pstructCpy_PWMObj->enumObj_Num)
		{
			case MPWM_Num0:
				if(pstructCpy_PWMObj->enumObj_PWMMode == MPWM_FastPWM)
				{
					if(pstructCpy_PWMObj->enumObj_OPFormat == MPWM_Inverted)
					{
						TCCR0 = 0x7C;//timer with prescaler 256
					}
					else if(pstructCpy_PWMObj->enumObj_OPFormat == MPWM_NonInverted)
					{
						TCCR0 = 0x6C;//timer with prescaler 256
					}
				}
				else if(pstructCpy_PWMObj->enumObj_PWMMode == MPWM_PhaseCorrect)
				{
					if(pstructCpy_PWMObj->enumObj_OPFormat == MPWM_Inverted)
					{
						TCCR0 = 0x74;//timer with prescaler 256					
					}
					else if(pstructCpy_PWMObj->enumObj_OPFormat == MPWM_NonInverted)
					{
						TCCR0 = 0x64;//timer with prescaler 256					
					}
				}
				
				OCR0 = pstructCpy_PWMObj->u16Obj_InitialDutyCycleValue;
				TCNT0 = 0x00;//reset timer/counter register
				CLR_BIT(TIMSK,0);// disable overflow interrupt for timer0 (polling)
				
				OCn.enumPin  = MDIO_PIN3;//OC0 output
				OCn.enumPort = MDIO_PORTB;
				OCn.enumMode = MDIO_Output;
				MDIO_enumPinDirection(&OCn);
				break;
			
			case MPWM_Num1:
				if(pstructCpy_PWMObj->enumObj_PWMMode == MPWM_FastPWM)
				{
					if(pstructCpy_PWMObj->enumObj_OPFormat == MPWM_Inverted)
					{
						TCCR1A = 0xC3;
					}
					else if(pstructCpy_PWMObj->enumObj_OPFormat == MPWM_NonInverted)
					{
						TCCR1A = 0x83;
					}
					TCCR1B = 0x1C;
				}
				else if(pstructCpy_PWMObj->enumObj_PWMMode == MPWM_PhaseCorrect)
				{
					if(pstructCpy_PWMObj->enumObj_OPFormat == MPWM_Inverted)
					{
						TCCR0 = 0xC3;
					}
					else if(pstructCpy_PWMObj->enumObj_OPFormat == MPWM_NonInverted)
					{
						TCCR0 = 0x83;
					}
					TCCR1B = 0x14;//timer with prescaler 256
				}
				
				OCR1AH = (u8)pstructCpy_PWMObj->u16Obj_InitialDutyCycleValue;
				OCR1AL = (u8)(pstructCpy_PWMObj->u16Obj_InitialDutyCycleValue >> 8);
				
				TCNT1H = 0x00;//To do a 16-bit write, the high byte must be written before the low byte.
				TCNT1L = 0x00;//reset timer/counter register
				CLR_BIT(TIMSK,2);// disable overflow interrupt for timer1 (polling)
				
				OCn.enumPin  = MDIO_PIN5;//OC1A output
				OCn.enumPort = MDIO_PORTD;
				OCn.enumMode = MDIO_Output;
				MDIO_enumPinDirection(&OCn);
				break;
			
			case MPWM_Num2:
				if(pstructCpy_PWMObj->enumObj_PWMMode == MPWM_FastPWM)
				{
					if(pstructCpy_PWMObj->enumObj_OPFormat == MPWM_Inverted)
					{
						TCCR2 = 0x7E;//timer with prescaler 256
					}
					else if(pstructCpy_PWMObj->enumObj_OPFormat == MPWM_NonInverted)
					{
						TCCR2 = 0x6E;//timer with prescaler 256
					}
				}
				else if(pstructCpy_PWMObj->enumObj_PWMMode == MPWM_PhaseCorrect)
				{
					if(pstructCpy_PWMObj->enumObj_OPFormat == MPWM_Inverted)
					{
						TCCR2 = 0x76;//timer with prescaler 256
					}
					else if(pstructCpy_PWMObj->enumObj_OPFormat == MPWM_NonInverted)
					{
						TCCR2 = 0x66;//timer with prescaler 256
					}
				}
				OCR2 = pstructCpy_PWMObj->u16Obj_InitialDutyCycleValue;
				TCNT2 = 0x00;//reset timer/counter register
				CLR_BIT(TIMSK,6);// disable overflow interrupt for timer2 (polling)
				
				OCn.enumPin  = MDIO_PIN7;//OC2 output
				OCn.enumPort = MDIO_PORTD;
				OCn.enumMode = MDIO_Output;
				MDIO_enumPinDirection(&OCn);
				break;
			
			default:
				break;
		}
	}
}

MPWM_voidSetDutyCycle(MPWM* pstructCpy_PWMObj, u16 u16Cpy_DutyCycleValue)
{
	if((pstructCpy_PWMObj != NULL) &&
	(pstructCpy_PWMObj->enumObj_State == MTIMER_Busy))
	{
		switch(pstructCpy_PWMObj->enumObj_Num)
		{
			case MPWM_Num0:
				OCR0 = (u8)u16Cpy_DutyCycleValue;
				break;
			
			case MPWM_Num1:
				OCR1AH = (u8)u16Cpy_DutyCycleValue;
				OCR1AL = (u8)(u16Cpy_DutyCycleValue >> 8);
				break;
			
			case MPWM_Num2:
				OCR2 = u16Cpy_DutyCycleValue;
				break;
			
			default:
				break;
		}
	}
}

void MPWM_voidStopPWM(MPWM* pstructCpy_PWMObj)
{
	if((pstructCpy_PWMObj != NULL) &&
	(pstructCpy_PWMObj->enumObj_State == MTIMER_Busy))
	{
		switch(pstructCpy_PWMObj->enumObj_Num)
		{
			case MPWM_Num0:
				TCCR0 = 0x00;//stop PWM
				break;
			
			case MPWM_Num1:
				TCCR1B = 0x00;//stop PWM
				TCCR1A = 0x00;
				break;
				
			case MPWM_Num2:
				TCCR2 = 0x00;//stop PWM
				break;
			
			default:
				break;
		}
		pstructCpy_PWMObj->enumObj_State = MTIMER_Free;
	} 
}
