#define F_CPU 16000000UL
#include <util/delay.h>

#include "E:\AMIT Graduation Project\Final Project\Final Project\Libraries_\LIB_STDTypes.h"
#include "E:\AMIT Graduation Project\Final Project\Final Project\MCAL\MDIO\MDIO_interface.h"

#include "E:\AMIT Graduation Project\Final Project\Final Project\MCAL\MTIMER\MPWM\MPWM_interface.h"
#include "E:\AMIT Graduation Project\Final Project\Final Project\MCAL\MTIMER\MTIMER_interface.h"

#include "HLed_config.h"
#include "HLed_interface.h"

static MDIO_Pin  HLED_PWMPins[NUM_OF_PWMs] = {{MDIO_PIN3, MDIO_PORTB, MDIO_Output, MDIO_High},
											 {MDIO_PIN5, MDIO_PORTD, MDIO_Output, MDIO_High},
											 {MDIO_PIN7, MDIO_PORTD, MDIO_Output, MDIO_High}};

static MPWM HLED_PWM0_Obj;
static MPWM HLED_PWM1_Obj;
static MPWM HLED_PWM2_Obj;

void Hled_voidInitObj(HLED* pstructCpy_LedObj)
{
	MDIO_enumPinDirection(&pstructCpy_LedObj->structLedPin); 
}

void Hled_voidInitArr(void)
{
	u8 u8Local_Iterator ;
	
	for(u8Local_Iterator = 0 ; u8Local_Iterator < NUM_OF_LEDS ; u8Local_Iterator++)
	{
		Hled_voidInitObj(&HLED_ArrayOfLeds[u8Local_Iterator]);
	}
}

void Hled_voidToggleLed(HLED* pstructCpy_LedObj)
{
	MDIO_enumTogglePinValue(&pstructCpy_LedObj->structLedPin);
}

void Hled_voidLedOn(HLED* pstructCpy_LedObj)
{
	if(pstructCpy_LedObj->enumActiveLevel == HLED_ACTIVE_LOW)
	{
		pstructCpy_LedObj->structLedPin.enumOutputLevel = MDIO_Low;
	}
	else
	{
		pstructCpy_LedObj->structLedPin.enumOutputLevel = MDIO_High;
	}
	
	MDIO_enumPinValue(&pstructCpy_LedObj->structLedPin);
}

void Hled_voidLedOff(HLED* pstructCpy_LedObj)
{
	if(pstructCpy_LedObj->enumActiveLevel == HLED_ACTIVE_LOW)
	{
		pstructCpy_LedObj->structLedPin.enumOutputLevel = MDIO_High;
	}
	else
	{
		pstructCpy_LedObj->structLedPin.enumOutputLevel = MDIO_Low;
	}
	
	MDIO_enumPinValue(&pstructCpy_LedObj->structLedPin);	
}




