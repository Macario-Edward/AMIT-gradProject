#ifndef MAIN_H_
#define MAIN_H_

				/*******************************************/
				/*				   AVR Libraries		   */
				/*******************************************/
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

				/*******************************************/
				/*				   Libraries			   */
				/*******************************************/
#include "Libraries_/LIB_STDTypes.h"
#include "Libraries_/LIB_BMNP.h"
#include "Libraries_/ATMega32_Registers.h"

				/*******************************************/
				/*					MCAL				   */
				/*******************************************/
//Digital Input Output
#include "MCAL/MDIO/MDIO_interface.h"
#include "MCAL/MDIO/MDIO_Registers.h"

//Interrupt
#include "MCAL/MINT/MINT_interface.h"

//Digital to Analog Converter
#include "MCAL/MADC/MADC_interface.h"

//Timer
#include "MCAL/MTIMER/MTIMER_interface.h"
#include "MCAL/MTIMER/MTimerCounter/MTimerCounter_interface.h"
#include "MCAL/MTIMER/MPWM/MPWM_interface.h"
#include "MCAL/MTIMER/MICU/MICU_interface.h"
#include "MCAL/MTIMER/MTIMER_registers.h"

				/*******************************************/
				/*					HAL				       */
				/*******************************************/
//Led
#include "E:\AMIT Graduation Project\Final Project\Final Project\HAL\HDCMotor\HLED\HLed_config.h"
#include "E:\AMIT Graduation Project\Final Project\Final Project\HAL\HDCMotor\HLED\HLed_interface.h"

//Liquid Crystal Display (LCD)
#include "HAL/HLCD/HLCD_config.h"
#include "HAL/HLCD/HLCD_interface.h"
#include "HAL/HLCD/HLCD_private.h"

//ServoMotor
#include "HAL/HServoMotor/HServoMotor_interface.h"

//DCMotor
#include "HAL/HDCMotor/HDCMotor_config.h"
#include "HAL/HDCMotor/HDCMotor_interface.h"

//Movement
void Forward();
void Stop();
void Scan();
void Steer();

#endif /* MAIN_H_ */