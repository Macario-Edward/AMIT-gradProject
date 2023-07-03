/*
 * MDIO_program.c
 *
 * Created: 2/4/2023 9:42:42 PM
 * Author: DELL 5480
 */ 

#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"

#include "MDIO_interface.h"
#include "MDIO_config.h"
#include "MDIO_Registers.h"

void MDIO_enumDIOInit(void)
{
	/*MDIO_enumPortDirection(MDIO_PORTA, PORTA_INIT_DIR);
	MDIO_enumPortDirection(MDIO_PORTB, PORTB_INIT_DIR);
	MDIO_enumPortDirection(MDIO_PORTC, PORTC_INIT_DIR);
	MDIO_enumPortDirection(MDIO_PORTD, PORTD_INIT_DIR);
	
	MDIO_enumPortValue(MDIO_PORTA, PORTA_INIT_VALUE);
	MDIO_enumPortValue(MDIO_PORTB, PORTB_INIT_VALUE);
	MDIO_enumPortValue(MDIO_PORTC, PORTC_INIT_VALUE);
	MDIO_enumPortValue(MDIO_PORTD, PORTD_INIT_VALUE);*/
}

tenumFncErrorState MDIO_enumPortDirection(MDIO_Port* pstructCpy_port)
{
	tenumFncErrorState enumLocal_errState = LSTY_EXECUTED_SUCCESSFULLY;
	
	if(pstructCpy_port == NULL)
	{
		enumLocal_errState = LSTY_NULL_POINTER;
	}
	else if((pstructCpy_port->enumPort >= MDIO_PORTA) && (pstructCpy_port->enumPort <= MDIO_PORTD))
	{
		switch(pstructCpy_port->enumPort)
		{
			case MDIO_PORTA:
				MDIOA->DDR_R = pstructCpy_port->enumMode;
				break;
			
			case MDIO_PORTB:
				MDIOB->DDR_R = pstructCpy_port->enumMode;
				break;
			
			case MDIO_PORTC:
				MDIOC->DDR_R = pstructCpy_port->enumMode;
				break;
			
			case MDIO_PORTD:
				MDIOD->DDR_R = pstructCpy_port->enumMode;
				break;
			
			default:
				break;
			
		}	
	}
	else
	{
		enumLocal_errState = LSTY_OUT_OF_RANGE;
	}
	
	return enumLocal_errState;
}

tenumFncErrorState MDIO_enumPortValue(MDIO_Port* pstructCpy_port)
{
	tenumFncErrorState enumLocal_errState = LSTY_EXECUTED_SUCCESSFULLY;
	
	if((pstructCpy_port->enumPort >= MDIO_PORTA) && (pstructCpy_port->enumPort <= MDIO_PORTD))
	{
		switch(pstructCpy_port->enumPort)
		{
			case MDIO_PORTA:
				MDIOA->PORT_R = pstructCpy_port->enumOutputLevel;
				break;
			
			case MDIO_PORTB:
				MDIOB->PORT_R = pstructCpy_port->enumOutputLevel;
				break;
			
			case MDIO_PORTC:
				MDIOC->PORT_R = pstructCpy_port->enumOutputLevel;
				break;
			
			case MDIO_PORTD:
				MDIOD->PORT_R = pstructCpy_port->enumOutputLevel;
				break;
			
			default:
				break;
		}
	}
	else
	{
		enumLocal_errState = LSTY_OUT_OF_RANGE;
	}
	
	return enumLocal_errState;
}

tenumFncErrorState MDIO_enumGetPortValue(MDIO_Port* pstructCpy_port, pu8 pu8Cpy_portValue)
{
	tenumFncErrorState enumLocal_errState = LSTY_EXECUTED_SUCCESSFULLY;
	
	if((pstructCpy_port->enumPort >= MDIO_PORTA) && (pstructCpy_port->enumPort <= MDIO_PORTD))
	{
		switch(pstructCpy_port->enumPort)
		{
			case MDIO_PORTA:
				*pu8Cpy_portValue = MDIOA->PIN_R;
				break;
			
			case MDIO_PORTB:
				*pu8Cpy_portValue = MDIOB->PIN_R;
				break;
			
			case MDIO_PORTC:
				*pu8Cpy_portValue = MDIOC->PIN_R;
				break;
			
			case MDIO_PORTD:
				*pu8Cpy_portValue = MDIOD->PIN_R;
				break;
			
			default:
				break;
		}
	}
	else
	{
		enumLocal_errState = LSTY_OUT_OF_RANGE;
	}
	
	return enumLocal_errState;	
}

tenumFncErrorState MDIO_enumPinDirection(MDIO_Pin* pstructCpy_pin)
{
		tenumFncErrorState enumLocal_errState = LSTY_EXECUTED_SUCCESSFULLY;
		
		if(((pstructCpy_pin->enumPort >= MDIO_PORTA) && (pstructCpy_pin->enumPort <= MDIO_PORTD)) &&
		   ((pstructCpy_pin->enumPin >= MDIO_PIN0) && (pstructCpy_pin->enumPin <= MDIO_PIN7)) &&
		   ((pstructCpy_pin->enumMode <= MDIO_Output) && (pstructCpy_pin->enumMode >= MDIO_Input)))
		   {
				switch(pstructCpy_pin->enumPort)
				{
					case MDIO_PORTA:
						if(pstructCpy_pin->enumMode == MDIO_Output)
							SET_BIT(MDIOA->DDR_R, pstructCpy_pin->enumPin);
						else if(pstructCpy_pin->enumMode == MDIO_Input)
							CLR_BIT(MDIOA->DDR_R, pstructCpy_pin->enumPin);
						break;
				
					case MDIO_PORTB:
						if(pstructCpy_pin->enumMode == MDIO_Output)
							SET_BIT(MDIOB->DDR_R, pstructCpy_pin->enumPin);
						else if(pstructCpy_pin->enumMode == MDIO_Input)
							CLR_BIT(MDIOB->DDR_R, pstructCpy_pin->enumPin);
						break;
				
				case MDIO_PORTC:
						if(pstructCpy_pin->enumMode == MDIO_Output)
							SET_BIT(MDIOC->DDR_R, pstructCpy_pin->enumPin);
						else if(pstructCpy_pin->enumMode == MDIO_Input)
							CLR_BIT(MDIOC->DDR_R, pstructCpy_pin->enumPin);
						break;
				
				case MDIO_PORTD:
						if(pstructCpy_pin->enumMode == MDIO_Output)
							SET_BIT(MDIOD->DDR_R, pstructCpy_pin->enumPin);
						else if(pstructCpy_pin->enumMode == MDIO_Input)
							CLR_BIT(MDIOD->DDR_R, pstructCpy_pin->enumPin);
						break;
				
				default:
						break;
				}
		   }
		 else
		{
			enumLocal_errState = LSTY_OUT_OF_RANGE;
		}

		
		return enumLocal_errState;
}

tenumFncErrorState MDIO_enumPinValue(MDIO_Pin* pstructCpy_pin)
{
		tenumFncErrorState enumLocal_errState = LSTY_EXECUTED_SUCCESSFULLY;
		
		if(((pstructCpy_pin->enumPort >= MDIO_PORTA) && (pstructCpy_pin->enumPort <= MDIO_PORTD)) &&
		   ((pstructCpy_pin->enumPin >= MDIO_PIN0) && (pstructCpy_pin->enumPin <= MDIO_PIN7)) &&
		   ((pstructCpy_pin->enumOutputLevel <= MDIO_High) && (pstructCpy_pin->enumOutputLevel >= MDIO_Low)))
		   {
				switch(pstructCpy_pin->enumPort)
				{
					case MDIO_PORTA:
						if(pstructCpy_pin->enumOutputLevel == MDIO_Low)
							CLR_BIT(MDIOA->PORT_R, pstructCpy_pin->enumPin);
						else 
							SET_BIT(MDIOA->PORT_R, pstructCpy_pin->enumPin);
						break;
				
					case MDIO_PORTB:
						if(pstructCpy_pin->enumOutputLevel == MDIO_Low)
							CLR_BIT(MDIOB->PORT_R, pstructCpy_pin->enumPin);
						else 
							SET_BIT(MDIOB->PORT_R, pstructCpy_pin->enumPin);
						break;
				
				case MDIO_PORTC:
						if(pstructCpy_pin->enumOutputLevel == MDIO_Low)
							CLR_BIT(MDIOC->PORT_R, pstructCpy_pin->enumPin);
						else 
							SET_BIT(MDIOC->PORT_R, pstructCpy_pin->enumPin);
						break;
				
				case MDIO_PORTD:
						if(pstructCpy_pin->enumOutputLevel == MDIO_Low)
							CLR_BIT(MDIOD->PORT_R, pstructCpy_pin->enumPin);
						else 
							SET_BIT(MDIOD->PORT_R, pstructCpy_pin->enumPin);
						break;
				
				default:
						break;
				}
		   }
		 else
		{
			enumLocal_errState = LSTY_OUT_OF_RANGE;
		}
		
		return enumLocal_errState;
}

tenumFncErrorState MDIO_enumTogglePinValue(MDIO_Pin* pstructCpy_pin)
{
		tenumFncErrorState enumLocal_errState = LSTY_EXECUTED_SUCCESSFULLY;
		
		if(((pstructCpy_pin->enumPort >= MDIO_PORTA) && (pstructCpy_pin->enumPort <= MDIO_PORTD)) &&
		((pstructCpy_pin->enumPin >= MDIO_PIN0) && (pstructCpy_pin->enumPin <= MDIO_PIN7)))
		{
			switch(pstructCpy_pin->enumPort)
			{
				case MDIO_PORTA:
					Toggle_BIT(MDIOA->PORT_R, pstructCpy_pin->enumPin);
					break;
				
				case MDIO_PORTB:
					Toggle_BIT(MDIOB->PORT_R, pstructCpy_pin->enumPin);
					break;
				
				case MDIO_PORTC:
					Toggle_BIT(MDIOC->PORT_R, pstructCpy_pin->enumPin);
					break;
				
				case MDIO_PORTD:
					Toggle_BIT(MDIOD->PORT_R, pstructCpy_pin->enumPin);
					break;
				
				default:
					break;
			}
		}
		else
		{
			enumLocal_errState = LSTY_OUT_OF_RANGE;
		}
		
		return enumLocal_errState;	
}

tenumFncErrorState MDIO_enumGetPinValue(MDIO_Pin* pstructCpy_pin, pu8 pu8Cpy_pinValue)
{
	tenumFncErrorState enumLocal_errState = LSTY_EXECUTED_SUCCESSFULLY;
	
	if(pu8Cpy_pinValue == NULL)
	{
		enumLocal_errState = LSTY_NULL_POINTER;
		return enumLocal_errState;
	}		
	else if(((pstructCpy_pin->enumPort >= MDIO_PORTA) && (pstructCpy_pin->enumPort <= MDIO_PORTD)) &&
	((pstructCpy_pin->enumPin >= MDIO_PIN0) && (pstructCpy_pin->enumPin <= MDIO_PIN7)))
	{
		switch(pstructCpy_pin->enumPort)
		{
			case MDIO_PORTA:
				*pu8Cpy_pinValue = GET_BIT(MDIOA->PIN_R,pstructCpy_pin->enumPin);
				break;
			
			case MDIO_PORTB:
				*pu8Cpy_pinValue = GET_BIT(MDIOB->PIN_R,pstructCpy_pin->enumPin);
				break;
			
			case MDIO_PORTC:
				*pu8Cpy_pinValue = GET_BIT(MDIOC->PIN_R,pstructCpy_pin->enumPin);
				break;
			
			case MDIO_PORTD:
				*pu8Cpy_pinValue = GET_BIT(MDIOD->PIN_R,pstructCpy_pin->enumPin);
				break;
			
			default:
				break;
		}		
	}
	else
	{
		enumLocal_errState = LSTY_OUT_OF_RANGE;
	}

	return enumLocal_errState;
}

