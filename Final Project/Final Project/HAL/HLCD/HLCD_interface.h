#ifndef HLCD_INTERFACE_H_
#define HLCD_INTERFACE_H_

#include "../../Libraries_/LIB_STDTypes.h"
#include "../../MCAL/MDIO/MDIO_interface.h"
#include "HLCD_config.h"

//list of all commands in LCD module
#define LCD_4BitMode1					((u8)0x33)
#define LCD_4BitMode2					((u8)0x32)
#define LCD_2Lines5X8_4BitMode			((u8)0x28)
#define CLEAR_DISPLAY         			((u8)0b00000001)
#define RETURN_HOME    		 			((u8)0b00000010)
#define ENTRY_MODE_INC 		 			((u8)0b00000111)
#define ENTRY_MODE_DEC  		 		((u8)0b00000101)
#define DISPLAY_ON_ONLY		 			((u8)0b00001100)
#define DISPLAY_ON_WITH_CURSOR  		((u8)0b00001110)
#define DISPLAY_ON_WITH_CURSOR_BLINKING ((u8)0b00001111)
#define CURSOR_SHIFT_RIGHT  			((u8)0b00010100)
#define CURSOR_SHIFT_LEFT  		 		((u8)0b00010000)
#define DISPLAY_SHIFT_RIGHT  			((u8)0b00011100)
#define DISPLAY_SHIFT_LEFT  			((u8)0b00011000)
#define FUNCTION_SET  		 			((u8)0b00111100)

typedef enum{
	Command, Data
}HLCD_DataType;

//LCD 2 MODES of operations
typedef enum{
	HLCD_4Bit_Mode, HLCD_8Bit_Mode
}HLCD_Mode;

typedef struct Hlcd{
	HLCD_Mode HLCD_enumMODE;

	MDIO_Pin DIO_tDataPin_0;
	MDIO_Pin DIO_tDataPin_1;
	MDIO_Pin DIO_tDataPin_2;
	MDIO_Pin DIO_tDataPin_3;
	MDIO_Pin DIO_tDataPin_4;
	MDIO_Pin DIO_tDataPin_5;
	MDIO_Pin DIO_tDataPin_6;
	MDIO_Pin DIO_tDataPin_7;

	MDIO_Pin DIO_tRegSelectPin;
	MDIO_Pin DIO_tReadWritePin;
	MDIO_Pin DIO_tEnablePin;
}HLCD;

extern HLCD HLCDArrayOfLCD [NUM_OF_LCDs];

tenumFncErrorState HLCD_enuInit(void);
tenumFncErrorState HLCD_enuWriteData(HLCD_DataType enumCpy_LCDDatatype, u8 u8Cpy_LCDData, HLCD* pstructCpy_HLCDObj);
tenumFncErrorState HLCD_enuIntegerToString(u32 u32Cpy_Number, HLCD* pstructCpy_HLCDObj);
tenumFncErrorState HLCD_enuFloatToString(f32 f32Cpy_Number, HLCD* pstructCpy_HLCDObj);
tenumFncErrorState HLCD_enuDisplayString(u8 u8String[], u8 u8Cpy_size, HLCD* pstructCpy_HLCDObj);
tenumFncErrorState HLCD_enuClearScreen(HLCD* pstructCpy_HLCDObj); 
tenumFncErrorState HLCD_enuGoToXY(u8 u8Cpy_Row, u8 u8Cpy_Col, HLCD* pstructCpy_HLCDObj);

/*simple application example (in main):
____________________

int main(void)
{
	HLCD_enuInit();
	u8 arr[5] = "hello";
	HLCD_enuDisplayString(arr, 5, &HLCDArrayOfLCD [HLCD_NUM0]);
	_delay_ms(2000);
	HLCD_enuClearScreen(&HLCDArrayOfLCD [HLCD_NUM0]);
	
	while(1)
	{
		
	}
}
*/

#endif /* HLCD_INTERFACE_H_ */
