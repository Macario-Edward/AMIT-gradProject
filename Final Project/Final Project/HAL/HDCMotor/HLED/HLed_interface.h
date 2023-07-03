#ifndef HAL_LED_INTERFACE_H_
#define HAL_LED_INTERFACE_H_

#include "E:\AMIT Graduation Project\Final Project\Final Project\MCAL\MDIO\MDIO_interface.h"

#include "E:\AMIT Graduation Project\Final Project\Final Project\MCAL\MTIMER\MPWM\MPWM_interface.h"

typedef enum{
	HLED_Zero_percent_Brightness,
	HLED_25_percent_Brightness,
	HLED_50_percent_Brightness, 
	HLED_75_percent_Brightness, 
	HLED_100_percent_Brightness 
}HLED_brightnessLevel;

typedef enum{
	HLED_ACTIVE_LOW, HLED_ACTIVE_HIGH
}HLed_ActiveLevel;

typedef struct{
	MDIO_Pin				structLedPin;
	HLed_ActiveLevel		enumActiveLevel;
	HLED_brightnessLevel	enumBrightnessLevel;
}HLED;

extern HLED  HLED_ArrayOfLeds[ NUM_OF_LEDS ] ;

void Hled_voidInitObj(HLED* pstructCpy_LedObj);
void Hled_voidInitArr(void);
void Hled_voidToggleLed(HLED* pstructCpy_LedObj);
void Hled_voidLedOn(HLED* pstructCpy_LedObj);
void Hled_voidLedOff(HLED* pstructCpy_LedObj);
void Hled_voidChangeBrightness(HLED* pstructCpy_LedObj);


/*Simple Application in main:
______________________________
int main(void)
{
	Hled_voidInitArr();
	
	while(1)
	{
		Hled_voidToggleLed(&HLED_ArrayOfLeds [HLED_NUM0]);
		_delay_ms(1000);
	}
}
*/

#endif /* HAL_LED_INTERFACE_H_ */
