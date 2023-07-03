#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"

#include "HDCMotor_config.h"
#include "HDCMotor_interface.h"
#include "../../MCAL/MDIO/MDIO_interface.h"

void HDCMotor_voidInit(void)
{
	u8 u8Local_Iterator ;
	
	for(u8Local_Iterator = 0 ; u8Local_Iterator < NUM_OF_DC_MOTORS ; u8Local_Iterator++)
	{
		MDIO_enumPinDirection(&HDCMotor_ArrayOfMotors[u8Local_Iterator].DIO_tPosTerminal);
		MDIO_enumPinDirection(&HDCMotor_ArrayOfMotors[u8Local_Iterator].DIO_tNegTerminal);
		MDIO_enumPinDirection(&HDCMotor_ArrayOfMotors[u8Local_Iterator].DIO_tEnable);
		
		if(HDCMotor_ArrayOfMotors[u8Local_Iterator].enumDirection == HDCMotor_CW)
		{
			HDCMotor_ArrayOfMotors[u8Local_Iterator].DIO_tPosTerminal.enumOutputLevel = MDIO_High;
			HDCMotor_ArrayOfMotors[u8Local_Iterator].DIO_tNegTerminal.enumOutputLevel = MDIO_Low;
		}
		else if(HDCMotor_ArrayOfMotors[u8Local_Iterator].enumDirection == HDCMotor_CCW)
		{
			HDCMotor_ArrayOfMotors[u8Local_Iterator].DIO_tPosTerminal.enumOutputLevel = MDIO_Low;
			HDCMotor_ArrayOfMotors[u8Local_Iterator].DIO_tNegTerminal.enumOutputLevel = MDIO_High;	
		}
	}
}

void HDCMotor_voidStartMotor(HDCMotor* pstructCpy_DCMotorObj)
{
	if(pstructCpy_DCMotorObj != NULL)
	{
		pstructCpy_DCMotorObj->DIO_tEnable.enumOutputLevel      = MDIO_High;
	
		MDIO_enumPinValue(&pstructCpy_DCMotorObj->DIO_tNegTerminal);
		MDIO_enumPinValue(&pstructCpy_DCMotorObj->DIO_tPosTerminal);
		MDIO_enumPinValue(&pstructCpy_DCMotorObj->DIO_tEnable);	
	}
}

void HDCMotor_voidStopMotor(HDCMotor* pstructCpy_DCMotorObj)
{
	if(pstructCpy_DCMotorObj != NULL)
	{
		pstructCpy_DCMotorObj->DIO_tEnable.enumOutputLevel      = MDIO_Low;

		MDIO_enumPinValue(&pstructCpy_DCMotorObj->DIO_tEnable);
	}
}

void HDCMotor_voidReverseDirection(HDCMotor* pstructCpy_DCMotorObj)
{
	if(pstructCpy_DCMotorObj != NULL)
	{
		if(pstructCpy_DCMotorObj->enumDirection == HDCMotor_CW)
		{
			pstructCpy_DCMotorObj->DIO_tPosTerminal.enumOutputLevel = MDIO_High;
			pstructCpy_DCMotorObj->DIO_tNegTerminal.enumOutputLevel = MDIO_Low;
		}
		else if(pstructCpy_DCMotorObj->enumDirection == HDCMotor_CCW)
		{
			pstructCpy_DCMotorObj->DIO_tPosTerminal.enumOutputLevel = MDIO_Low;
			pstructCpy_DCMotorObj->DIO_tNegTerminal.enumOutputLevel = MDIO_High;
		}
	}
}

void HDCMotor_voidChangeSpeed(HDCMotor* pstructCpy_DCMotorObj);