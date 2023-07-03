#ifndef _MINT_INTERFACE_H_
#define _MINT_INTERFACE_H_

#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"

typedef enum{
	MINT_ANYLEVEL, MINT_ANYLOGIC, MINT_FALLING, MINT_RISING 
}MINT_ExIntLevel;

typedef enum{
	MINT_EXINT0, MINT_EXINT1, MINT_EXINT2
}MINT_ExInts;

typedef enum{
	MINT_INTF_CLEAR, MINT_INTF_SET
}MINT_INTFlagValue;

typedef enum{
	MINT_INT, MINT_POLLING
}MINT_INTMode;

typedef struct{
	MINT_ExInts			enumObj_Num;
	MINT_ExIntLevel		enumObj_Level;
	MINT_INTMode		enumObj_Mode;
}MINT;

tenumFncErrorState MINT_enuInit(MINT* pstructCpy_INTObj);
tenumFncErrorState MINT_enuEnableINTHandler(MINT* pstructCpy_INTObj);
tenumFncErrorState MINT_enuDisableINTHandler(MINT* pstructCpy_INTObj);
tenumFncErrorState MINT_enuSetINTLevel(MINT* pstructCpy_INTObj);
void MINT_ExitCriticalSection(void);
void MINT_EnterCriticalSection(void);
tenumFncErrorState MINT_enuGetINTFlag(MINT* pstructCpy_INTObj, pu8 pu8Cpy_INTFlag);
tenumFncErrorState MINT_enumClearINTFlag(MINT* pstructCpy_INTObj);
void MINT_voidSetCallBack(void (*ptr) (void), MINT* pstructCpy_INTObj);

/* Simple Application in main:
_______________________________

void func(u8 ADC_value)
{
	Hled_voidToggleLed(&HLED_ArrayOfLeds[HLED_NUM0]);;
}

int main(void)
{
	Hled_voidInitArr();
	HSwitch_voidInit();
	MINT_enuInit();
	MINT_voidSetCallBack(func, MINT_EXINT0);
	
	while(1)
	{
	}
}
*/

#endif /* _MINT_INTERFACE_H_ */
