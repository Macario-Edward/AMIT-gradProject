#ifndef _MADC_INTERFACE_H_
#define _MADC_INTERFACE_H_

#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"

typedef enum{
	MADC_Ch0, MADC_Ch1, MADC_Ch2, MADC_Ch3, MADC_Ch4, MADC_Ch5, MADC_Ch6, MADC_Ch7
}MADC_Channel;

typedef enum{
	MADC_8BIT, MADC_10BIT
}MADC_RegJus;

typedef enum{
	MADC_AREF, MADC_AVCC, MADC_IREF
}MADC_VRef;

typedef enum{
	MADC_PS_2 = 2, MADC_PS_4 = 4, MADC_PS_8 = 8, MADC_PS_16 = 16, MADC_PS_32 = 32, MADC_PS_64 = 64, MADC_PS_128 = 128
}MADC_Prescaler;

typedef enum{
	MADC_SINGLE_CONV, MADC_AUTO_TRIG_CONV
}MADC_ConvMode;

typedef enum{
	MADC_FreeRunning, MADC_AnalogComp, MADC_ExInt0, MADC_TimCouCompMatch0, MADC_TimCouOverflow0, MADC_TimCouCompMatchB, MADC_TimCouOverflow1, MADC_TimCouCaptureEvent1
}MADC_AutoTrigMode;

typedef enum{
	MADC_INT, MADC_POLLING
}MADC_OPMode;

typedef enum{
	MADC_Analog, MADC_Digital
}MADC_OPFormat;

typedef struct{
	MADC_Channel		enumObj_Channel;
	MADC_RegJus			enumObj_RegJus;
	MADC_VRef			enumObj_VRef;
	u16					u16_ARefValue;//user enters the voltage applied to AREF pin
	MADC_Prescaler		enumObj_Pres;
	MADC_ConvMode		enumObj_ConvMode;
	MADC_AutoTrigMode	enumObj_AutoTrigMode;
	MADC_OPMode			enumObj_OPMode;
	MADC_OPFormat		enumObj_OPFormat;
}MADC;

tenumFncErrorState MADC_enuInit(MADC* pstructCpy_ADCObj);
tenumFncErrorState MADC_voidSetCallBack(void (*ptrFuncCpy) (u16));
void MADC_voidActivateChannel(MADC* pstructCpy_ADCObj);
tenumFncErrorState MADC_enuGetConvResult(pu16 pu16Cpy_ADCResult);
void MADC_enuStartConv(void);
MADC MADC_voidGetCurrentActiveCh(void);

/*in main :
==================================
void func(u16 data)
{
	HLCD_enuClearScreen(HLCD_NUM0);
	HLCD_enuIntegerToString(data,HLCD_NUM0);
	_delay_ms(500);
}

int main(void)
{
	MADC x;
	x.enumObj_Channel		= MADC_Ch1;
	x.enumObj_ConvMode		= MADC_AUTO_TRIG_CONV;
	x.enumObj_AutoTrigMode  = MADC_FreeRunning;
	x.enumObj_OPMode		= MADC_INT;
	x.enumObj_Pres			= MADC_PS_128;
	x.enumObj_RegJus		= MADC_10BIT;
	x.enumObj_VRef			= MADC_AVCC;
	x.enumObj_OPFormat		= MADC_Digital;
	
	HLCD_enuInit();
	MADC_enuInit(&x);
	MADC_voidSetCallBack(func);
	MADC_enuStartConv(); //start free running mode
	
	while(1)
	{
		//MADC_enuStartConv();
		//_delay_ms(1000);
	}
	
	return 0;
}
*/

#endif /* _MADC_INTERFACE_H_ */
