#include "HLed_config.h"
#include "HLed_interface.h"
#include "E:\AMIT Graduation Project\Final Project\Final Project\MCAL\MDIO\MDIO_interface.h"
#include "E:\AMIT Graduation Project\Final Project\Final Project\MCAL\MTIMER\MPWM\MPWM_interface.h"
#include "E:\AMIT Graduation Project\Final Project\Final Project\MCAL\MTIMER\MTIMER_interface.h"

HLED  HLED_ArrayOfLeds [ NUM_OF_LEDS ] =
{
				[HLED_NUM0] = {
									.structLedPin = {MDIO_PIN7, MDIO_PORTD, MDIO_Output, MDIO_High},
									.enumActiveLevel = HLED_ACTIVE_HIGH,
									.enumBrightnessLevel = HLED_Zero_percent_Brightness
							  }
};


