#include "HDCMotor_config.h"
#include "HDCMotor_interface.h"
#include "../../MCAL/MDIO/MDIO_interface.h"

HDCMotor  HDCMotor_ArrayOfMotors[ NUM_OF_DC_MOTORS ] =
{
	[HDCMotor_NUM0] = {
		.DIO_tPosTerminal = {MDIO_PIN3, MDIO_PORTC, MDIO_Output, MDIO_High},
		.DIO_tNegTerminal = {MDIO_PIN4, MDIO_PORTC, MDIO_Output, MDIO_Low},
		.DIO_tEnable      = {MDIO_PIN4, MDIO_PORTD, MDIO_Output, MDIO_Low},
		.enumDirection    = HDCMotor_CW
		},
	[HDCMotor_NUM1] = {
		.DIO_tPosTerminal = {MDIO_PIN5, MDIO_PORTC, MDIO_Output, MDIO_High},
		.DIO_tNegTerminal = {MDIO_PIN6, MDIO_PORTC, MDIO_Output, MDIO_Low},
		.DIO_tEnable      = {MDIO_PIN5, MDIO_PORTD, MDIO_Output, MDIO_Low},
		.enumDirection    = HDCMotor_CW
		}
};
