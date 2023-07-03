#define F_CPU 16000000UL
#include <util/delay.h>

//used libraries
#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"

//DIO
#include "../../MCAL/MDIO/MDIO_interface.h"
#include "../../MCAL/MDIO/MDIO_Registers.h"

//LCD
#include "HLCD_config.h"
#include "HLCD_interface.h"
#include "HLCD_private.h"

tenumFncErrorState HLCD_enuInit(void)
{
	tenumFncErrorState ReturnFunState = LSTY_EXECUTED_SUCCESSFULLY ;
	u8 u8Local_Iter;

	for(u8Local_Iter = 0 ; u8Local_Iter < NUM_OF_LCDs ; u8Local_Iter++ )
	{
		MDIO_enumPinDirection(&HLCDArrayOfLCD[u8Local_Iter].DIO_tEnablePin);
		MDIO_enumPinDirection(&HLCDArrayOfLCD[u8Local_Iter].DIO_tReadWritePin);
		MDIO_enumPinDirection(&HLCDArrayOfLCD[u8Local_Iter].DIO_tRegSelectPin);
					
		if(HLCDArrayOfLCD[u8Local_Iter].HLCD_enumMODE == HLCD_8Bit_Mode)
		{
			MDIO_enumPinDirection(&HLCDArrayOfLCD[u8Local_Iter].DIO_tDataPin_0);
			MDIO_enumPinDirection(&HLCDArrayOfLCD[u8Local_Iter].DIO_tDataPin_1);
			MDIO_enumPinDirection(&HLCDArrayOfLCD[u8Local_Iter].DIO_tDataPin_2);
			MDIO_enumPinDirection(&HLCDArrayOfLCD[u8Local_Iter].DIO_tDataPin_3);
			MDIO_enumPinDirection(&HLCDArrayOfLCD[u8Local_Iter].DIO_tDataPin_4);
			MDIO_enumPinDirection(&HLCDArrayOfLCD[u8Local_Iter].DIO_tDataPin_5);
			MDIO_enumPinDirection(&HLCDArrayOfLCD[u8Local_Iter].DIO_tDataPin_6);
			MDIO_enumPinDirection(&HLCDArrayOfLCD[u8Local_Iter].DIO_tDataPin_7);
		}
		else if(HLCDArrayOfLCD[u8Local_Iter].HLCD_enumMODE == HLCD_4Bit_Mode)
		{
			MDIO_enumPinDirection(&HLCDArrayOfLCD[u8Local_Iter].DIO_tDataPin_4);
			MDIO_enumPinDirection(&HLCDArrayOfLCD[u8Local_Iter].DIO_tDataPin_5);
			MDIO_enumPinDirection(&HLCDArrayOfLCD[u8Local_Iter].DIO_tDataPin_6);
			MDIO_enumPinDirection(&HLCDArrayOfLCD[u8Local_Iter].DIO_tDataPin_7);
		}
		_delay_ms(30);
		
		if(HLCDArrayOfLCD[u8Local_Iter].HLCD_enumMODE == HLCD_8Bit_Mode)
		{
			HLCD_enuWriteData(Command, FUNCTION_SET, &HLCDArrayOfLCD[u8Local_Iter]);
		}
		else if (HLCDArrayOfLCD[u8Local_Iter].HLCD_enumMODE == HLCD_4Bit_Mode)
		{
			HLCD_enuWriteData(Command, LCD_4BitMode1, &HLCDArrayOfLCD[u8Local_Iter]);
			HLCD_enuWriteData(Command, LCD_4BitMode2, &HLCDArrayOfLCD[u8Local_Iter]);
			HLCD_enuWriteData(Command, LCD_2Lines5X8_4BitMode, &HLCDArrayOfLCD[u8Local_Iter]);
		}
		else
		{
			ReturnFunState = LSTY_READ_ERROR;
			return ReturnFunState;
		}
		
		_delay_ms(1);
		HLCD_enuWriteData(Command, DISPLAY_ON_WITH_CURSOR, &HLCDArrayOfLCD[u8Local_Iter]);
		_delay_ms(1);
		HLCD_enuWriteData(Command, CLEAR_DISPLAY, &HLCDArrayOfLCD[u8Local_Iter]);
		_delay_ms(2);
	}

	return ReturnFunState;
}

tenumFncErrorState HLCD_enuWriteData(HLCD_DataType enumCpy_LCDDatatype, u8 u8Cpy_LCDData, HLCD* pstructCpy_HLCDObj)
{
	tenumFncErrorState enumLocal_errState = LSTY_EXECUTED_SUCCESSFULLY;
	Register RegLocal_data;

	if(pstructCpy_HLCDObj != NULL)
	{
		if(enumCpy_LCDDatatype == Data)
		{
			pstructCpy_HLCDObj->DIO_tRegSelectPin.enumOutputLevel = MDIO_High;
		}
		else if(enumCpy_LCDDatatype == Command)
		{
			pstructCpy_HLCDObj->DIO_tRegSelectPin.enumOutputLevel = MDIO_Low;
		}
			
		pstructCpy_HLCDObj->DIO_tReadWritePin.enumOutputLevel = MDIO_Low;
		MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tRegSelectPin);
		MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tReadWritePin);

		if(pstructCpy_HLCDObj->HLCD_enumMODE == HLCD_4Bit_Mode)
		{
			RegLocal_data.Byte = u8Cpy_LCDData & 0xf0; // sending high nibble first
			
			pstructCpy_HLCDObj->DIO_tDataPin_4.enumOutputLevel = RegLocal_data.Bit.B4;
			pstructCpy_HLCDObj->DIO_tDataPin_5.enumOutputLevel = RegLocal_data.Bit.B5;
			pstructCpy_HLCDObj->DIO_tDataPin_6.enumOutputLevel = RegLocal_data.Bit.B6;
			pstructCpy_HLCDObj->DIO_tDataPin_7.enumOutputLevel = RegLocal_data.Bit.B7;
			
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tDataPin_4);
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tDataPin_5);
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tDataPin_6);
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tDataPin_7);

			pstructCpy_HLCDObj->DIO_tEnablePin.enumOutputLevel = MDIO_High;
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tEnablePin);
			_delay_ms(10);
			pstructCpy_HLCDObj->DIO_tEnablePin.enumOutputLevel = MDIO_Low;
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tEnablePin);

			RegLocal_data.Byte = u8Cpy_LCDData << 4; // sending low nibble second
			
			pstructCpy_HLCDObj->DIO_tDataPin_4.enumOutputLevel = RegLocal_data.Bit.B4;
			pstructCpy_HLCDObj->DIO_tDataPin_5.enumOutputLevel = RegLocal_data.Bit.B5;
			pstructCpy_HLCDObj->DIO_tDataPin_6.enumOutputLevel = RegLocal_data.Bit.B6;
			pstructCpy_HLCDObj->DIO_tDataPin_7.enumOutputLevel = RegLocal_data.Bit.B7;
			
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tDataPin_4);
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tDataPin_5);
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tDataPin_6);
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tDataPin_7);

			pstructCpy_HLCDObj->DIO_tEnablePin.enumOutputLevel = MDIO_High;
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tEnablePin);
			_delay_ms(10);
			pstructCpy_HLCDObj->DIO_tEnablePin.enumOutputLevel = MDIO_Low;
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tEnablePin);
		}
		else if(pstructCpy_HLCDObj->HLCD_enumMODE == HLCD_8Bit_Mode)
		{
			RegLocal_data.Byte = u8Cpy_LCDData; 

			pstructCpy_HLCDObj->DIO_tDataPin_0.enumOutputLevel = RegLocal_data.Bit.B0;
			pstructCpy_HLCDObj->DIO_tDataPin_1.enumOutputLevel = RegLocal_data.Bit.B1;
			pstructCpy_HLCDObj->DIO_tDataPin_2.enumOutputLevel = RegLocal_data.Bit.B2;
			pstructCpy_HLCDObj->DIO_tDataPin_3.enumOutputLevel = RegLocal_data.Bit.B3;				
			pstructCpy_HLCDObj->DIO_tDataPin_4.enumOutputLevel = RegLocal_data.Bit.B4;
			pstructCpy_HLCDObj->DIO_tDataPin_5.enumOutputLevel = RegLocal_data.Bit.B5;
			pstructCpy_HLCDObj->DIO_tDataPin_6.enumOutputLevel = RegLocal_data.Bit.B6;
			pstructCpy_HLCDObj->DIO_tDataPin_7.enumOutputLevel = RegLocal_data.Bit.B7;

			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tDataPin_0);
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tDataPin_1);
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tDataPin_2);
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tDataPin_3);						
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tDataPin_4);
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tDataPin_5);
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tDataPin_6);
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tDataPin_7);
						
			pstructCpy_HLCDObj->DIO_tEnablePin.enumOutputLevel = MDIO_High;
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tEnablePin);
			_delay_ms(10);
			pstructCpy_HLCDObj->DIO_tEnablePin.enumOutputLevel = MDIO_Low;
			MDIO_enumPinValue(&pstructCpy_HLCDObj->DIO_tEnablePin);
		}
		else
		{
			enumLocal_errState = LSTY_READ_ERROR;
		}
	}
	else
	{
		enumLocal_errState = LSTY_NULL_POINTER;
	}

	return enumLocal_errState;
}

tenumFncErrorState HLCD_enuIntegerToString(u32 u32Cpy_Number, HLCD* pstructCpy_HLCDObj)
{
	tenumFncErrorState enumLocal_errState = LSTY_EXECUTED_SUCCESSFULLY;

	if(pstructCpy_HLCDObj != NULL)
	{
		u32 u32Local_Reverse = 1; //to hold zeros

		while(u32Cpy_Number >= 1) //reverse : 1000 -> 10001
		{
			u32Local_Reverse = u32Local_Reverse*10 + u32Cpy_Number%10;
			u32Cpy_Number = u32Cpy_Number / 10;
		}

		while(u32Local_Reverse != 1)
		{
			HLCD_enuWriteData(Data, u32Local_Reverse%10 +'0',pstructCpy_HLCDObj);
			u32Local_Reverse = u32Local_Reverse / 10;
		}
	}
	else
	{
		enumLocal_errState = LSTY_NULL_POINTER;
	}
	return enumLocal_errState;
}

tenumFncErrorState HLCD_enuFloatToString(f32 f32Cpy_Number, HLCD* pstructCpy_HLCDObj)
{
	tenumFncErrorState enumLocal_errState = LSTY_EXECUTED_SUCCESSFULLY;

	if(pstructCpy_HLCDObj != NULL)
	{
		u32 u32Local_WholeNum = f32Cpy_Number;
		HLCD_enuIntegerToString(u32Local_WholeNum, pstructCpy_HLCDObj);
		HLCD_enuWriteData(Data,'.',pstructCpy_HLCDObj);
		u64 u64Local_FracNum = (f32Cpy_Number * 100000);
		u64Local_FracNum = u64Local_FracNum % 100000;
		HLCD_enuIntegerToString((u32)u64Local_FracNum,pstructCpy_HLCDObj);
	}
	else
	{
		enumLocal_errState = LSTY_NULL_POINTER;
	}
	return enumLocal_errState;
}

tenumFncErrorState HLCD_enuDisplayString(u8 u8String[], u8 u8Cpy_size, HLCD* pstructCpy_HLCDObj)
{
	tenumFncErrorState enumLocal_errState = LSTY_EXECUTED_SUCCESSFULLY;

	if(pstructCpy_HLCDObj != NULL)
	{
		u8 u8Local_Iter;
		for(u8Local_Iter = 0 ; u8Local_Iter < u8Cpy_size ; u8Local_Iter++)
		{
			HLCD_enuWriteData(Data, u8String[u8Local_Iter] , pstructCpy_HLCDObj);
		}
	}
	else
	{
		enumLocal_errState = LSTY_NULL_POINTER;
	}
	return enumLocal_errState;
}

tenumFncErrorState HLCD_enuClearScreen(HLCD* pstructCpy_HLCDObj)
{
	tenumFncErrorState enumLocal_errState = LSTY_EXECUTED_SUCCESSFULLY;

	if(pstructCpy_HLCDObj != NULL)
	{

		//_delay_ms(1);
		HLCD_enuWriteData(Command, CLEAR_DISPLAY, pstructCpy_HLCDObj);
		//_delay_ms(2);
	}
	else
	{
		enumLocal_errState = LSTY_NULL_POINTER;
	}
	return enumLocal_errState;
}

tenumFncErrorState HLCD_enuGoToXY(u8 u8Cpy_Row, u8 u8Cpy_Col, HLCD* pstructCpy_HLCDObj)
{
	tenumFncErrorState ReturnFunState = LSTY_EXECUTED_SUCCESSFULLY;
	
	if(((HLCD_u8FirstCol <= u8Cpy_Col) && (HLCD_u8LastCol >= u8Cpy_Col)) &&
	   ((HLCD_u8FirstRow <= u8Cpy_Row) && (HLCD_u8SecRow >= u8Cpy_Row)))
	{
		if(pstructCpy_HLCDObj != NULL)
		{
			switch (u8Cpy_Row)
			{
				case HLCD_u8FirstRow:
					HLCD_enuWriteData(Command, HLCD_u8FirstRowStart+u8Cpy_Col ,pstructCpy_HLCDObj);
					break;
			
				case HLCD_u8SecRow:
					HLCD_enuWriteData(Command, HLCD_u8SecondRowStart+u8Cpy_Col ,pstructCpy_HLCDObj);
					break;
			
				default:
					ReturnFunState = LSTY_OUT_OF_RANGE;
			}
		}
		else
		{
			ReturnFunState = LSTY_NULL_POINTER;
		}

	}
	else
	{
		ReturnFunState = LSTY_OUT_OF_RANGE;
	}
	
	return ReturnFunState;
}
