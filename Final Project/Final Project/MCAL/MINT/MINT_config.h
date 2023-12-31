#ifndef _MINT_CONFIG_H_
#define _MINT_CONFIG_H_

#include "MINT_interface.h"

/* MINT_INT_ENABLE, MINT_INT_DISABLE*/
#define MINT_EXINT0_ENABLE  MINT_INT_ENABLE
#define MINT_EXINT1_ENABLE  MINT_INT_DISABLE
#define MINT_EXINT2_ENABLE  MINT_INT_DISABLE

/* MINT_ISC_RISING, MINT_ISC_FALLING, MINT_ISC_ANYLOGIC, MINT_ISC_ANYLEVEL*/
#define MINT_EXINT0_ISC  MINT_ISC_FALLING
#define MINT_EXINT1_ISC  MINT_ISC_FALLING

/* MINT_ISC_RISING, MINT_ISC_FALLING */
#define MINT_EXINT2_ISC  MINT_ISC_FALLING

#endif /* _MINT_CONFIG_H_ */
