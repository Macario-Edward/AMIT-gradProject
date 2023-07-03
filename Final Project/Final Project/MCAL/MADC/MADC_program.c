//main avr libraries
#include "avr/interrupt.h"

//used libraries
#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"
 
//MADC
#include "MADC_interface.h"
#include "MADC_registers.h"
#include "../MINT/MINT_registers.h"

static void (* ADCINT_CallBack) (u16 u16Cpy_ADCResult) ;

static MADC MADC_enumGlobalCurrentChannel;

static void MADC_voidSetCurrentActiveCh(MADC* pstructCpy_ADCObj)
{
	MADC_enumGlobalCurrentChannel = *pstructCpy_ADCObj;
}

MADC MADC_voidGetCurrentActiveCh(void)
{
	return MADC_enumGlobalCurrentChannel;
}

void MADC_voidActivateChannel(MADC* pstructCpy_ADCObj)
{
	// Set ADC channel
	switch(pstructCpy_ADCObj->enumObj_Channel)
	{
		case MADC_Ch0:
			CLR_BIT(ADMUX,MUX0);
			CLR_BIT(ADMUX,MUX1);
			CLR_BIT(ADMUX,MUX2);
			break;
		
		case MADC_Ch1:
			SET_BIT(ADMUX,MUX0);
			CLR_BIT(ADMUX,MUX1);
			CLR_BIT(ADMUX,MUX2);
			break;
		
		case MADC_Ch2:
			CLR_BIT(ADMUX,MUX0);
			SET_BIT(ADMUX,MUX1);
			CLR_BIT(ADMUX,MUX2);
			break;
		
		case MADC_Ch3:
			SET_BIT(ADMUX,MUX0);
			SET_BIT(ADMUX,MUX1);
			CLR_BIT(ADMUX,MUX2);
			break;
		
		case MADC_Ch4:
			CLR_BIT(ADMUX,MUX0);
			CLR_BIT(ADMUX,MUX1);
			SET_BIT(ADMUX,MUX2);
			break;
		
		case MADC_Ch5:
			SET_BIT(ADMUX,MUX0);
			CLR_BIT(ADMUX,MUX1);
			SET_BIT(ADMUX,MUX2);
			break;
		
		case MADC_Ch6:
			CLR_BIT(ADMUX,MUX0);
			SET_BIT(ADMUX,MUX1);
			SET_BIT(ADMUX,MUX2);
			break;
		
		case MADC_Ch7:
			SET_BIT(ADMUX,MUX0);
			SET_BIT(ADMUX,MUX1);
			SET_BIT(ADMUX,MUX2);
			break;
		
		default:
			break;
	}
	
	MADC_voidSetCurrentActiveCh(pstructCpy_ADCObj);
}

tenumFncErrorState MADC_enuInit(MADC* pstructCpy_ADCObj)
{
	tenumFncErrorState ReturnFncState = LSTY_EXECUTED_SUCCESSFULLY;

	// Set ADC channel
	switch(pstructCpy_ADCObj->enumObj_Channel)
	{
		case MADC_Ch0:
			CLR_BIT(ADMUX,MUX0);
			CLR_BIT(ADMUX,MUX1);
			CLR_BIT(ADMUX,MUX2);
			break;
			
		case MADC_Ch1:
			SET_BIT(ADMUX,MUX0);
			CLR_BIT(ADMUX,MUX1);
			CLR_BIT(ADMUX,MUX2);
			break;	
			
		case MADC_Ch2:
			CLR_BIT(ADMUX,MUX0);
			SET_BIT(ADMUX,MUX1);
			CLR_BIT(ADMUX,MUX2);
			break;
			
		case MADC_Ch3:
			SET_BIT(ADMUX,MUX0);
			SET_BIT(ADMUX,MUX1);
			CLR_BIT(ADMUX,MUX2);
			break;
			
		case MADC_Ch4:
			CLR_BIT(ADMUX,MUX0);
			CLR_BIT(ADMUX,MUX1);
			SET_BIT(ADMUX,MUX2);
			break;
			
		case MADC_Ch5:
			SET_BIT(ADMUX,MUX0);
			CLR_BIT(ADMUX,MUX1);
			SET_BIT(ADMUX,MUX2);
			break;
			
		case MADC_Ch6:
			CLR_BIT(ADMUX,MUX0);
			SET_BIT(ADMUX,MUX1);
			SET_BIT(ADMUX,MUX2);
			break;
			
		case MADC_Ch7:
			SET_BIT(ADMUX,MUX0);
			SET_BIT(ADMUX,MUX1);
			SET_BIT(ADMUX,MUX2);
			break;
		
		default:
			break;		
	}

	switch(pstructCpy_ADCObj->enumObj_VRef)
	{
		case MADC_AREF:
			CLR_BIT(ADMUX,REFS0);
			CLR_BIT(ADMUX,REFS1);
			break;
			
		case MADC_AVCC:
			SET_BIT(ADMUX,REFS0);
			CLR_BIT(ADMUX,REFS1);
			break;
			
		case MADC_IREF:
			SET_BIT(ADMUX,REFS0);
			SET_BIT(ADMUX,REFS1);
			break;
			
		default:
			break;
	}
	// Set ADC prescalar
	switch(pstructCpy_ADCObj->enumObj_Pres)
	{
		case MADC_PS_2:
			CLR_BIT(ADCSRA,ADPS0);
			CLR_BIT(ADCSRA,ADPS1);
			CLR_BIT(ADCSRA,ADPS2);
			break;
		
		case MADC_PS_4:
			CLR_BIT(ADCSRA,ADPS0);
			SET_BIT(ADCSRA,ADPS1);
			CLR_BIT(ADCSRA,ADPS2);
			break;
		
		case MADC_PS_8:
			SET_BIT(ADCSRA,ADPS0);
			SET_BIT(ADCSRA,ADPS1);
			CLR_BIT(ADCSRA,ADPS2);
			break;
		
		case MADC_PS_16:
			CLR_BIT(ADCSRA,ADPS0);
			CLR_BIT(ADCSRA,ADPS1);
			SET_BIT(ADCSRA,ADPS2);
			break;
		
		case MADC_PS_32:
			SET_BIT(ADCSRA,ADPS0);
			CLR_BIT(ADCSRA,ADPS1);
			SET_BIT(ADCSRA,ADPS2);
			break;
		
		case MADC_PS_64:
			CLR_BIT(ADCSRA,ADPS0);
			SET_BIT(ADCSRA,ADPS1);
			SET_BIT(ADCSRA,ADPS2);
			break;
		
		case MADC_PS_128:
			SET_BIT(ADCSRA,ADPS0);
			SET_BIT(ADCSRA,ADPS1);
			SET_BIT(ADCSRA,ADPS2);
			break;
		
		default:
			break;
	}

	// Set ADC justify
	if(pstructCpy_ADCObj->enumObj_RegJus == MADC_8BIT)
	{
		// Left adjust ADC result to allow easy 8 bit reading
		SET_BIT(ADMUX,ADLAR);
	}
	else if(pstructCpy_ADCObj->enumObj_RegJus == MADC_10BIT)
	{
		// Right adjust ADC result to allow easy 10 bit reading
		CLR_BIT(ADMUX,ADLAR);
	}
	
	if(pstructCpy_ADCObj->enumObj_ConvMode == MADC_SINGLE_CONV)
	{
		CLR_BIT(ADCSRA, ADATE);//ADC Single Conv
	}
	else if(pstructCpy_ADCObj->enumObj_ConvMode == MADC_AUTO_TRIG_CONV)
	{
		SET_BIT(ADCSRA, ADATE);//ADC Auto Trigger Enable
		
		CLR_BIT(SFIOR,4);//this bit must be written zero when SFIOR is written.
		
		switch(pstructCpy_ADCObj->enumObj_AutoTrigMode)
		{
			case MADC_FreeRunning:
				CLR_BIT(SFIOR,ADTS0);
				CLR_BIT(SFIOR,ADTS1);
				CLR_BIT(SFIOR,ADTS2);
				
				break;
				
			case MADC_AnalogComp:
				SET_BIT(SFIOR,ADTS0);
				CLR_BIT(SFIOR,ADTS1);
				CLR_BIT(SFIOR,ADTS2);
				break;
			
			case MADC_ExInt0:
				CLR_BIT(SFIOR,ADTS0);
				SET_BIT(SFIOR,ADTS1);
				CLR_BIT(SFIOR,ADTS2);
				break;
				
			case MADC_TimCouCompMatch0:
				SET_BIT(SFIOR,ADTS0);
				SET_BIT(SFIOR,ADTS1);
				CLR_BIT(SFIOR,ADTS2);
				break;
				
			case MADC_TimCouOverflow0:
				CLR_BIT(SFIOR,ADTS0);
				CLR_BIT(SFIOR,ADTS1);
				SET_BIT(SFIOR,ADTS2);
				break;
				
			case MADC_TimCouCompMatchB:
				SET_BIT(SFIOR,ADTS0);
				CLR_BIT(SFIOR,ADTS1);
				SET_BIT(SFIOR,ADTS2);
				break;
				
			case MADC_TimCouOverflow1:
				CLR_BIT(SFIOR,ADTS0);
				SET_BIT(SFIOR,ADTS1);
				SET_BIT(SFIOR,ADTS2);
				break;
				
			case MADC_TimCouCaptureEvent1:
				SET_BIT(SFIOR,ADTS0);
				SET_BIT(SFIOR,ADTS1);
				SET_BIT(SFIOR,ADTS2);
				break;
				
			default:
				break;
		}
	}
	
	if(pstructCpy_ADCObj->enumObj_OPMode == MADC_POLLING)
	{
		CLR_BIT(ADCSRA, ADIE); //disable interrupt
	}
	else if(pstructCpy_ADCObj->enumObj_OPMode == MADC_INT)
	{
		SET_BIT(ADCSRA, ADIE); //enable interrupt
		SET_BIT(SREG,I); // Global Interrupt Enable
	}
	
	// Clear ADIF by writing one to it, for next conversion
	SET_BIT(ADCSRA, ADIF);
	
	// Enable ADC
	SET_BIT(ADCSRA,ADEN);
	
	MADC_voidSetCurrentActiveCh(pstructCpy_ADCObj);

	return ReturnFncState;
}

tenumFncErrorState MADC_enuGetConvResult(pu16 pu16Cpy_ADCResult)
{
	tenumFncErrorState ReturnFncState = LSTY_EXECUTED_SUCCESSFULLY;
	MADC MADCLocal_CurrentCh;
	u16 u16Local_ADCResult = 0;
	u16 u16Local_DivValue = 0;

	if ((NULL != pu16Cpy_ADCResult))
	{
		while(!GET_BIT(ADCSRA, ADIF)); // Wait for conversion to complete (polling)

		SET_BIT(ADCSRA,ADIF); // Clear ADIF by writing one to it, for next conversion

		MADCLocal_CurrentCh = MADC_voidGetCurrentActiveCh();
	
		if(MADCLocal_CurrentCh.enumObj_RegJus == MADC_8BIT)
		{
			u16Local_ADCResult = ADCH; // Left adjust ADC result to allow easy 8 bit reading
			u16Local_DivValue  = 255;  // 2^8 -1 (because it is 8 bit register)
		}
		else if(MADCLocal_CurrentCh.enumObj_RegJus == MADC_10BIT)
		{
			u16Local_ADCResult = ADCW; // Right adjust ADC result to allow easy 10 bit reading
			u16Local_DivValue  = 1023;	//2^10 -1 (because it is 10 bit register)
		}
		
		if(MADCLocal_CurrentCh.enumObj_OPFormat == MADC_Digital)
		{
			*pu16Cpy_ADCResult = u16Local_ADCResult;
		}
		else if(MADCLocal_CurrentCh.enumObj_OPFormat == MADC_Analog)
		{
			switch(MADCLocal_CurrentCh.enumObj_VRef)
			{
				case MADC_AVCC:
					*pu16Cpy_ADCResult = (u16Local_ADCResult * 5) / u16Local_DivValue;
					break;
			
				case MADC_IREF:
					*pu16Cpy_ADCResult = (u16Local_ADCResult * 256) / (u16Local_DivValue*100);
					break;
			
				case MADC_AREF:
					*pu16Cpy_ADCResult = (u16Local_ADCResult * MADCLocal_CurrentCh.u16_ARefValue) / (u16Local_DivValue*100);
					break;
			
				default:
					break;
			}
		}
	}
	else
	{
		ReturnFncState = LSTY_NULL_POINTER;
	}
	
	return ReturnFncState;
}

void MADC_enuStartConv(void)
{
	SET_BIT(ADCSRA,ADSC);// Start conversion
}

/* This function is being called in main.c to hold an address of another function that have the ISR written by user */
tenumFncErrorState MADC_voidSetCallBack(void (*ptrFuncCpy) (u16))
{
	tenumFncErrorState ReturnFncState = LSTY_EXECUTED_SUCCESSFULLY;
		
	if(NULL != ptrFuncCpy)
	{
		ADCINT_CallBack = ptrFuncCpy;
	}
	else
	{
		ReturnFncState = LSTY_NULL_POINTER;
	}
	
	return ReturnFncState;
}

ISR(ADC_vect)
{
	MADC MADCLocal_CurrentCh;
	u16 u16Local_ADCResult = 0;
	u16 u16Local_DivValue = 0;
	
	MADCLocal_CurrentCh = MADC_voidGetCurrentActiveCh();
	
	if(MADCLocal_CurrentCh.enumObj_RegJus == MADC_8BIT)
	{
		u16Local_ADCResult = ADCH; // Left adjust ADC result to allow easy 8 bit reading
		u16Local_DivValue  = 255;  // 2^8 -1 (because it is 8 bit register)
	}
	else if(MADCLocal_CurrentCh.enumObj_RegJus == MADC_10BIT)
	{
		u16Local_ADCResult = ADCW; // Right adjust ADC result to allow easy 10 bit reading
		u16Local_DivValue  = 1023;	//2^10 -1 (because it is 10 bit register)
	} 
	
	if(MADCLocal_CurrentCh.enumObj_OPFormat == MADC_Digital)
	{
		ADCINT_CallBack(u16Local_ADCResult);
	}
	else if(MADCLocal_CurrentCh.enumObj_OPFormat == MADC_Analog)
	{
		switch(MADCLocal_CurrentCh.enumObj_VRef)
		{
			case MADC_AVCC:
				u16Local_ADCResult = (u16Local_ADCResult * 5) / u16Local_DivValue;
				break;
				
			case MADC_IREF:
				u16Local_ADCResult = (u16Local_ADCResult * 256) / (u16Local_DivValue*100); 
				break;
				
			case MADC_AREF:
				u16Local_ADCResult = (u16Local_ADCResult * MADCLocal_CurrentCh.u16_ARefValue) / (u16Local_DivValue*100);
				break;
				
			default:
				break;
		}
		
		ADCINT_CallBack(u16Local_ADCResult);
	}
}