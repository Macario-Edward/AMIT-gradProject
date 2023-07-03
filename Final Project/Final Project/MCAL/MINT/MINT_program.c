//main avr libraries
#include <avr/interrupt.h>

//used libraries
#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"

//MINT
#include "MINT_interface.h"
#include "MINT_config.h"
#include "MINT_Registers.h"

static void (* ExINT_CallBack[3]) (void) ;

tenumFncErrorState MINT_enuInit(MINT* pstructCpy_INTObj)
{
	tenumFncErrorState enuReturnFncState = LSTY_EXECUTED_SUCCESSFULLY;
	
	if(pstructCpy_INTObj != NULL)
	{
		if(pstructCpy_INTObj->enumObj_Mode == MINT_INT)
		{
			MINT_enuEnableINTHandler(pstructCpy_INTObj);
		}
		else if(pstructCpy_INTObj->enumObj_Mode == MINT_POLLING)
		{
			MINT_enuDisableINTHandler(pstructCpy_INTObj);
		}
		MINT_enuSetINTLevel(pstructCpy_INTObj);
		SET_BIT(SREG,I); // Global Interrupt Enable
	}
	else
	{
		enuReturnFncState = LSTY_NULL_POINTER;
	}
	
	return enuReturnFncState;
}

tenumFncErrorState MINT_enuSetINTLevel(MINT* pstructCpy_INTObj)
{
	tenumFncErrorState enuReturnFncState = LSTY_EXECUTED_SUCCESSFULLY;
	
	if(pstructCpy_INTObj != NULL)
	{
		if(pstructCpy_INTObj->enumObj_Num == MINT_EXINT0)
		{
			switch(pstructCpy_INTObj->enumObj_Level)
			{
				case MINT_ANYLEVEL:// Activate INT0 on Any Low Level Change
				CLR_BIT(MCUCR,ISC00);
				CLR_BIT(MCUCR,ISC01);
				break;
				
				case MINT_ANYLOGIC:// Activate INT0 on Any Logical Change
				SET_BIT(MCUCR,ISC00);
				CLR_BIT(MCUCR,ISC01);
				break;
				
				case MINT_FALLING:// Activate INT0 on Falling Edge
				CLR_BIT(MCUCR,ISC00);
				SET_BIT(MCUCR,ISC01);
				break;
				
				case MINT_RISING:// Activate INT0 on Rising Edge
				SET_BIT(MCUCR,ISC00);
				SET_BIT(MCUCR,ISC01);
				break;
				default:
				enuReturnFncState = LSTY_OUT_OF_RANGE;
			}
		}
		else if(pstructCpy_INTObj->enumObj_Num == MINT_EXINT1)
		{
			switch(pstructCpy_INTObj->enumObj_Level)
			{
				case MINT_ANYLEVEL:// Activate INT1 on Any Low Level Change
				CLR_BIT(MCUCR,ISC10);
				CLR_BIT(MCUCR,ISC11);
				break;
				
				case MINT_ANYLOGIC:// Activate INT1 on Any Logical Change
				SET_BIT(MCUCR,ISC10);
				CLR_BIT(MCUCR,ISC11);
				break;
				
				case MINT_FALLING:// Activate INT1 on Falling Edge
				CLR_BIT(MCUCR,ISC10);
				SET_BIT(MCUCR,ISC11);
				break;
				
				case MINT_RISING:// Activate INT1 on Rising Edge
				SET_BIT(MCUCR,ISC10);
				SET_BIT(MCUCR,ISC11);
				break;
				default:
				enuReturnFncState = LSTY_OUT_OF_RANGE;
			}
		}
		else if(pstructCpy_INTObj->enumObj_Num == MINT_EXINT2)
		{
			switch(pstructCpy_INTObj->enumObj_Level)
			{
				case MINT_FALLING:// Activate INT2 on Falling Edge
				CLR_BIT(MCUCSR,ISC2); //Activate INT2 on Falling Edge
				break;
				
				case MINT_RISING:// Activate INT2 on Rising Edge
				SET_BIT(MCUCSR,ISC2); // Activate INT2 on Rising Edge
				break;
				
				default:
				enuReturnFncState = LSTY_OUT_OF_RANGE;
			}
		}
		else
		{
			enuReturnFncState = LSTY_OUT_OF_RANGE;
		}
	}
	else
	{
		enuReturnFncState = LSTY_NULL_POINTER;
	}
	
	return enuReturnFncState;
}

void MINT_ExitCriticalSection(void)
{
	SET_BIT(SREG,7);
}

void MINT_EnterCriticalSection(void)
{
	CLR_BIT(SREG,7);
}

tenumFncErrorState MINT_enuGetINTFlag(MINT* pstructCpy_INTObj, pu8 pu8Cpy_INTFlag)
{
	tenumFncErrorState enuReturnFncState = LSTY_EXECUTED_SUCCESSFULLY;
	
	switch(pstructCpy_INTObj->enumObj_Num)
	{
		case MINT_EXINT0:
			*pu8Cpy_INTFlag = GET_BIT(GIFR,INTF0);
			break;
		
		case MINT_EXINT1:
			*pu8Cpy_INTFlag = GET_BIT(GIFR,INTF1);
			break;
			
		case MINT_EXINT2:
			*pu8Cpy_INTFlag = GET_BIT(GIFR,INTF2);
			break;
			
		default:
			enuReturnFncState = LSTY_OUT_OF_RANGE;
			break;
	}
	
	return enuReturnFncState;
}

tenumFncErrorState MINT_enumClearINTFlag(MINT* pstructCpy_INTObj)
{
	tenumFncErrorState enuReturnFncState = LSTY_EXECUTED_SUCCESSFULLY;
	
	switch(pstructCpy_INTObj->enumObj_Num)
	{
		case MINT_EXINT0:
			SET_BIT(GIFR,INTF0);//(datasheet)the flag can be cleared by writing a logical one to it
			break;
			
		case MINT_EXINT1:
			SET_BIT(GIFR,INTF1);//(datasheet)the flag can be cleared by writing a logical one to it
			break;
			
		case MINT_EXINT2:
			SET_BIT(GIFR,INTF2);//(datasheet)the flag can be cleared by writing a logical one to it
			break;
		
		default:
			enuReturnFncState = LSTY_OUT_OF_RANGE;
			break;
	}
	
	return enuReturnFncState;
}

tenumFncErrorState MINT_enuEnableINTHandler(MINT* pstructCpy_INTObj)
{
	tenumFncErrorState enuReturnFncState = LSTY_EXECUTED_SUCCESSFULLY;

	switch(pstructCpy_INTObj->enumObj_Num)
	{
		case MINT_EXINT0 : SET_BIT(GICR,INT0); break; // Enable External Interrupt 0
		case MINT_EXINT1 : SET_BIT(GICR,INT1); break; // Enable External Interrupt 1
		case MINT_EXINT2 : SET_BIT(GICR,INT2); break; // Enable External Interrupt 2
		default : enuReturnFncState = LSTY_OUT_OF_RANGE; break;
	}
	return enuReturnFncState;
}

tenumFncErrorState MINT_enuDisableINTHandler(MINT* pstructCpy_INTObj)
{
	tenumFncErrorState enuReturnFncState = LSTY_EXECUTED_SUCCESSFULLY;

	switch(pstructCpy_INTObj->enumObj_Num)
	{
		case MINT_EXINT0 : CLR_BIT(GICR,INT0); break; // Disable External Interrupt 0
		case MINT_EXINT1 : CLR_BIT(GICR,INT1); break; // Disable External Interrupt 1
		case MINT_EXINT2 : CLR_BIT(GICR,INT2); break; // Disable External Interrupt 2
		default : enuReturnFncState = LSTY_OUT_OF_RANGE; break;
	}
	return enuReturnFncState;
}

/* This function is being called in main.c to hold an address of another function that have the ISR written by user */
void MINT_voidSetCallBack(void (*ptrFuncCpy) (void), MINT* pstructCpy_INTObj)
{
    /* Since the function is being passed to CB function is local we use the global varible "pointer to function" 
        to assign to it the address of the ISR function passed to CallBack function */
    switch(pstructCpy_INTObj->enumObj_Num)
	{
		case MINT_EXINT0:
			ExINT_CallBack[0] = ptrFuncCpy;
			break;
			
		case MINT_EXINT1:
			ExINT_CallBack[1] = ptrFuncCpy;
			break;
			
		case MINT_EXINT2:
			ExINT_CallBack[2] = ptrFuncCpy;
			break;
			
		default:
			break;
	
	}
}


ISR(INT0_vect)
{
	ExINT_CallBack[0]();
}

ISR(INT1_vect)
{
	ExINT_CallBack[1]();
}

ISR(INT2_vect)
{
	ExINT_CallBack[2]();
}
