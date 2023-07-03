#ifndef HSERVOMOTOR_INTERFACE_H_
#define HSERVOMOTOR_INTERFACE_H_

void HServoMotor_voidInit(void);
void HServo_voidStopMotor(void);
void HServo_voidSetAngle(u8 u8Cpy_Angle);

/*example :
 ----------
 * int main(void)
{
	HServoMotor_voidInit();
	
	MADC y;
	y.enumObj_Channel = MADC_Ch1;
	y.enumObj_VRef = MADC_AVCC;
	y.enumObj_ConvMode = MADC_AUTO_TRIG_CONV;
	y.enumObj_RegJus = MADC_8BIT;
	y.enumObj_OPFormat = MADC_Digital;
	y.enumObj_Pres = MADC_PS_128;
	y.enumObj_AutoTrigMode = MADC_FreeRunning;
	y.enumObj_OPMode = MADC_POLLING;
	MADC_enuInit(&y);
	MADC_enuStartConv();
	
	u16 z;
	
	while(1)
	{
		MADC_enuGetConvResult(&z);
		HServo_voidSetAngle((u8)z);
	}
}*/

#endif /* HSERVOMOTOR_INTERFACE_H_ */
