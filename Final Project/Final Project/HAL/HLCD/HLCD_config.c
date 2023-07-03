#include "../../MCAL/MDIO/MDIO_interface.h"
#include "HLCD_config.h"
#include "HLCD_interface.h"
#include "HLCD_private.h"

HLCD HLCDArrayOfLCD [NUM_OF_LCDs] =
{
	{ HLCD_4Bit_Mode ,
		
	  .DIO_tDataPin_0    = {MDIO_PIN0, MDIO_PORTA, MDIO_Output, MDIO_High},
	  .DIO_tDataPin_1    = {MDIO_PIN1, MDIO_PORTA, MDIO_Output, MDIO_High},
	  .DIO_tDataPin_2    = {MDIO_PIN2, MDIO_PORTA, MDIO_Output, MDIO_High},
	  .DIO_tDataPin_3    = {MDIO_PIN3, MDIO_PORTA, MDIO_Output, MDIO_High},
	  .DIO_tDataPin_4    = {MDIO_PIN4, MDIO_PORTA, MDIO_Output, MDIO_High},
	  .DIO_tDataPin_5    = {MDIO_PIN5, MDIO_PORTA, MDIO_Output, MDIO_High},
	  .DIO_tDataPin_6    = {MDIO_PIN6, MDIO_PORTA, MDIO_Output, MDIO_High},
	  .DIO_tDataPin_7    = {MDIO_PIN7, MDIO_PORTA, MDIO_Output, MDIO_High},

	  .DIO_tRegSelectPin = {MDIO_PIN1, MDIO_PORTB, MDIO_Output, MDIO_High},
	  .DIO_tReadWritePin = {MDIO_PIN2, MDIO_PORTB, MDIO_Output, MDIO_High},
	  .DIO_tEnablePin    = {MDIO_PIN4, MDIO_PORTB, MDIO_Output, MDIO_High}
	}
};