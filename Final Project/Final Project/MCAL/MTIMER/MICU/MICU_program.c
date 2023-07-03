#include "../../../Libraries_/LIB_STDTypes.h"
#include "../../../Libraries_/LIB_BMNP.h"

#include "../MTimerCounter/MTimerCounter_interface.h"
#include "../../MINT/MINT_interface.h"

#include "MICU_interface.h"

volatile u8 x = 0;
volatile u16 temp = 0;
static MTimerCounter timer;
static MINT inter;
static MICU MICU_Obj;

static void func(void);

void MICU_voidInit(void)
{
	x     = 0;
	temp  = 0;
	
	timer.enumObj_Num   = MTimerCounter_Num0;
	timer.enumObj_State = MTIMER_Free;
	timer.enumObj_TimeFormat = MTimerCounter_Us;
	
	inter.enumObj_Num   = MINT_EXINT0;
	inter.enumObj_Level = MINT_RISING;
	inter.enumObj_Mode  = MINT_INT;	
	
	MINT_voidSetCallBack(func, &inter);
	MTimerCounter_voidStartTimer(&timer);
	MINT_enuInit(&inter);
}

void MICU_voidFetchData(MICU* pstructCpy_ICUObj)
{
	pstructCpy_ICUObj->u16Obj_Ton  = MICU_Obj.u16Obj_Ton;
	pstructCpy_ICUObj->u16Obj_Toff = MICU_Obj.u16Obj_Toff;
	pstructCpy_ICUObj->u8Obj_DutyCycle = ((MICU_Obj.u16Obj_Ton * 100)/(MICU_Obj.u16Obj_Ton + MICU_Obj.u16Obj_Toff));
}

static void func(void)
{
	temp = MTimerCounter_f32GetTimerValue(&timer);
	if(x == 0)
	{
		x++;
		inter.enumObj_Level = MINT_FALLING;
		MINT_enuSetINTLevel(&inter);
		MTimerCounter_voidStartTimer(&timer);
	}
	else if(x == 1)
	{
		x++;
		MICU_Obj.u16Obj_Ton = temp;
		inter.enumObj_Level = MINT_RISING;
		MINT_enuSetINTLevel(&inter);
		MTimerCounter_voidStartTimer(&timer);
	}
	else if(x == 2)
	{
		MICU_Obj.u16Obj_Toff = temp;
		MINT_enuDisableINTHandler(&inter);
	}
}
