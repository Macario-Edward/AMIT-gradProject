/*
 * MDIO_interface.h
 *
 * Created: 2/4/2023 9:43:20 PM
 *  Author: DELL 5480
 */ 

#ifndef MDIO_INTERFACE_H_
#define MDIO_INTERFACE_H_

#include "../../Libraries_/LIB_STDTypes.h"


typedef enum{
	MDIO_PORTA, MDIO_PORTB, MDIO_PORTC, MDIO_PORTD
}Ports;

typedef enum{
	MDIO_PIN0, MDIO_PIN1, MDIO_PIN2, MDIO_PIN3, MDIO_PIN4, MDIO_PIN5, MDIO_PIN6, MDIO_PIN7
}Pins;

typedef enum{
	MDIO_Input, MDIO_Output = 0xff
}Pin_Mode;

typedef enum
{
	MDIO_Low, MDIO_High = 0xff
}Output_Level;

typedef enum
{
	MDIO_PullDown, MDIO_PullUp = 0xff
}Input_Level;

typedef struct{
	Pins  enumPin;
	Ports enumPort;
	Pin_Mode enumMode;
	Output_Level enumOutputLevel;
}MDIO_Pin;

typedef struct{
	Ports enumPort;
	Pin_Mode enumMode;
	Output_Level enumOutputLevel;	
}MDIO_Port;

void MDIO_enumDIOInit(void);
tenumFncErrorState MDIO_enumPortDirection(MDIO_Port* pstructCpy_port);
tenumFncErrorState MDIO_enumPortValue(MDIO_Port* pstructCpy_port);
tenumFncErrorState MDIO_enumGetPortValue(MDIO_Port* pstructCpy_port, pu8 pu8Cpy_portValue);
tenumFncErrorState MDIO_enumPinDirection(MDIO_Pin* pstructCpy_pin);
tenumFncErrorState MDIO_enumPinValue(MDIO_Pin* pstructCpy_pin);
tenumFncErrorState MDIO_enumTogglePinValue(MDIO_Pin* pstructCpy_pin);
tenumFncErrorState MDIO_enumGetPinValue(MDIO_Pin* pstructCpy_pin, pu8 pu8Cpy_pinValue);

#endif /* MDIO_INTERFACE_H_ */