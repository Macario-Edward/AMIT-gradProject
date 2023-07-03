#ifndef HDCMOTOR_INTERFACE_H_
#define HDCMOTOR_INTERFACE_H_

#include "HDCMotor_config.h"
#include "../../MCAL/MDIO/MDIO_interface.h"

typedef enum{
	HDCMotor_CCW, // counter clock-wise: +ve: low & -ve: high
	HDCMotor_CW   // clock-wise:         +ve: high & -ve: low
}HDCMotor_Direction;

typedef struct{
	MDIO_Pin			DIO_tPosTerminal;
	MDIO_Pin			DIO_tNegTerminal;
	MDIO_Pin			DIO_tEnable;
	HDCMotor_Direction  enumDirection;
}HDCMotor;

extern HDCMotor  HDCMotor_ArrayOfMotors[ NUM_OF_DC_MOTORS ] ;

void HDCMotor_voidInit(void);
void HDCMotor_voidStartMotor(HDCMotor* pstructCpy_DCMotorObj);
void HDCMotor_voidStopMotor(HDCMotor* pstructCpy_DCMotorObj);
void HDCMotor_voidReverseDirection(HDCMotor* pstructCpy_DCMotorObj);
void HDCMotor_voidChangeSpeed(HDCMotor* pstructCpy_DCMotorObj);

#endif /* HDCMOTOR_INTERFACE_H_ */