#include "main.h"
#include "E:\AMIT Graduation Project\Final Project\Final Project\Libraries_\LIB_STDTypes.h"
#include "E:\AMIT Graduation Project\Final Project\Final Project\Libraries_\LIB_BMNP.h"

#include "E:\AMIT Graduation Project\Final Project\Final Project\MCAL\MDIO\MDIO_interface.h"
#include "E:\AMIT Graduation Project\Final Project\Final Project\MCAL\MDIO\MDIO_Registers.h"

#define		Left	31
#define		Center	46
#define		Right	61

enum
{
	NO_OBJ_DETECTED, OBJ_DETECTED
}FLAG;

int main(void)
{	
	u8 MaxDist[3];
	
	MDIO_enumDIOInit();				
	HDCMotor_voidInit();
	
    while(1)
    {		
		if(FLAG == NO_OBJ_DETECTED)
		{
			Forward();
		}
		if (FLAG == OBJ_DETECTED)
		{
			Stop();
			while (FLAG == OBJ_DETECTED)
			{
				Scan();
				Steer();
			}
		}			
	}
}

void Forward()
{
	while(FLAG == NO_OBJ_DETECTED){
	//Set ultrasonic to the center
	MPWM Servo = {MPWM_Num0, MPWM_FastPWM, MPWM_NonInverted, MTIMER_Free, Center};
	MPWM_voidInit(&Servo);
	_delay_ms(200);									//short Delay for Servo motor to take position
	
	// Display Direction on LCD
	HLCD_enuClearScreen(&HLCDArrayOfLCD [HLCD_NUM0]);				
	u8 arr[7] = "Forward";
	HLCD_enuDisplayString(arr, 7, &HLCDArrayOfLCD [HLCD_NUM0]);
	
	//Start DC motors	
	HDCMotor_voidStartMotor(&HDCMotor_ArrayOfMotors[HDCMotor_NUM0]);
	HDCMotor_voidStartMotor(&HDCMotor_ArrayOfMotors[HDCMotor_NUM1]);
	
	//Sending Trigger to ultrasonic
	MICU_voidInit();
	SET_BIT(DDRC,0);
	CLR_BIT(DDRD,6);
	SET_BIT(PORTC,0);
	_delay_ms(10);
	CLR_BIT(PORTC,0);
	
	//displaying distance to LCD
	MICU Dist;
	MICU_voidFetchData(&Dist);									//getting pulse from ICU pin
	HLCD_enuIntegerToString(Dist.u16Obj_Ton, &HLCDArrayOfLCD[HLCD_NUM0]);
	HLCD_enuGoToXY(HLCD_u8SecRow, HLCD_u8FirstCol, &HLCDArrayOfLCD[HLCD_NUM0]);
	HLCD_enuIntegerToString(Dist.u16Obj_Toff, &HLCDArrayOfLCD[HLCD_NUM0]);
	}
}

void Stop()
{
	//Stop DC Motors
	HDCMotor_voidStopMotor(&HDCMotor_ArrayOfMotors[HDCMotor_NUM0]);	
	HDCMotor_voidStopMotor(&HDCMotor_ArrayOfMotors[HDCMotor_NUM1]);
	
	//Displaying direction
	HLCD_enuClearScreen(&HLCDArrayOfLCD [HLCD_NUM0]);
	u8 arr[4] = "Stop";
	HLCD_enuDisplayString(arr, 4, &HLCDArrayOfLCD [HLCD_NUM0]);
}

void Scan()
{
	HLCD_enuClearScreen(&HLCDArrayOfLCD [HLCD_NUM0]);
	u8 arr[7] = "Scanning";
	HLCD_enuDisplayString(arr, 8, &HLCDArrayOfLCD [HLCD_NUM0]);
	
	u16 Pos[] = {Left,Center,Right};							//Servo Motor Positions
	for (u16 x=0 ; x<4 ; x++)
	{
		MPWM Servo = {MPWM_Num0, MPWM_FastPWM, MPWM_NonInverted, MTIMER_Free, Pos[x]};
		MPWM_voidInit(&Servo);
		_delay_ms(1000);
	}
}

void Steer()
{
	u8 MaxDistPos;
	switch(MaxDistPos)
	{
		case Left:
		HLCD_enuClearScreen(&HLCDArrayOfLCD [HLCD_NUM0]);
		u8 arr[13] = "Steering Left";
		HLCD_enuDisplayString(arr, 13, &HLCDArrayOfLCD [HLCD_NUM0]);
		HDCMotor_voidStartMotor(&HDCMotor_ArrayOfMotors[HDCMotor_NUM0]);
		_delay_ms(300);
		break;
		
		case Center:
		Forward();
		break;
		
		case Right:
		HLCD_enuClearScreen(&HLCDArrayOfLCD [HLCD_NUM0]);
		arr[14] = "Steering Right";
		HLCD_enuDisplayString(arr, 14, &HLCDArrayOfLCD [HLCD_NUM0]);
		HDCMotor_voidStartMotor(&HDCMotor_ArrayOfMotors[HDCMotor_NUM1]);
		_delay_ms(300);
		break;
	}
	FLAG = NO_OBJ_DETECTED;
}