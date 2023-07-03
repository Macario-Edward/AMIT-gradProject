#ifndef _MTIMER_CONFIG_H_
#define _MTIMER_CONFIG_H_

/**************************** Timer Selection *********************/
			/*0 -> MTIMER0 ... 1 -> MTIMER1 ... 2 -> MTIMER2*/

						#define MTIMER_SELECT	MTIMER1
/******************************************************************/
#if MTIMER_SELECT == MTIMER0
	//Timer0 mode
	#define MTIMER0_MODE            MTIMER_NORMAL

	//Timer0 Prescaller
	#define MTIMER0_PRESCALLER      MTIMER0_PS_1024

	#if MTIMER0_MODE == MTIMER_NORMAL
		//TCNT0 initialization (default is 0, maximum 255)
		#define MTIMER0_INIT_VALUE      0

		//Interrupt Enable (must, do not change)
		#define MTIMER0_TOIE0           MTIMER_TOIE_ENABLE

		//global interrupt E (must, do not change)
		#define MTimer_GINTERRUPT       MTIMER_GINTERRUPT_E

 	#elif MTIMER0_MODE == MTIMER_CTC

		// (OCR0) initialization range(0 - 255) [must be initialized]
		#define MTIMER0_OCR0			0

		//Interrupt Enable (if disabled, OC0 must be enabled )
		#define MTIMER0_OCIE0           MTIMER_OCIE_ENABLE
		#define MTIMER0_TOIE0           MTIMER_TOIE_ENABLE //(for pwm mode)

		//Enable/Disable OC0 pin
		#define MTIMER0_OC0_CFG			MTIMER_OCn_E

		//Force Output Compare (for CTC mode only)
		#define MTIMER0_FOC0            MTIMER_FOC_CLEAR

		#if MTIMER0_OCIE0 ==  MTIMER_OCIE_ENABLE
			//global interrupt E (must, do not change)
			#define MTimer_GINTERRUPT       MTIMER_GINTERRUPT_E
    	#elif MTIMER0_OCIE0 ==  MTIMER_OCIE_DISABLE
			//global interrupt D (must, do not change)
			#define MTimer_GINTERRUPT       MTIMER_GINTERRUPT_D
		#endif

		#if MTIMER0_OC0_CFG == MTIMER_OCn_E

			//Compare Match Output DISABLED (anything but, DISCONNECTED)
			#define MTIMER0_OC0_MODE        MTIMER_TOGGLE_OC

			//Enable OC0 pin (MUST, NEVER CHANGE)
			SET_BIT(DDRB_Register,3);

		#elif MTIMER0_OC0_CFG == MTIMER_OCn_D
				//Compare Match Output DISABLED (MUST, NEVER CHANGE)
				#define MTIMER0_OC0_MODE        MTIMER_OC_DISCONNECTED
		#endif

	#elif MTIMER0_MODE == MTIMER_FAST_PWM

			// (OCR0) initialization range(0 - 255) [must be initialized]
		#define MTIMER0_OCR0			0

			//Interrupt Enable (if disabled, OC0 must be enabled )
		#define MTIMER0_OCIE0           MTIMER_OCIE_ENABLE
		#define MTIMER0_TOIE0           MTIMER_TOIE_ENABLE //(for pwm mode)

			//Enable/Disable OC0 pin
		#define MTIMER0_OC0_CFG			MTIMER_OCn_E

			//Force Output Compare (for CTC mode only)
		#define MTIMER0_FOC0            MTIMER_FOC_CLEAR

		#if MTIMER0_OCIE0 ==  MTIMER_OCIE_ENABLE
			//global interrupt E (must, do not change)
			#define MTimer_GINTERRUPT       MTIMER_GINTERRUPT_E
		#elif MTIMER0_OCIE0 ==  MTIMER_OCIE_DISABLE
			//global interrupt D (must, do not change)
			#define MTimer_GINTERRUPT       MTIMER_GINTERRUPT_D
		#endif

		#if MTIMER0_OC0_CFG == MTIMER_OCn_E

			//Compare Match Output DISABLED (anything but, DISCONNECTED)
			#define MTIMER0_OC0_MODE        MTIMER_TOGGLE_OC

			//Enable OC0 pin (MUST, NEVER CHANGE)
			SET_BIT(DDRB_Register,3);

		#elif MTIMER0_OC0_CFG == MTIMER_OCn_D
			//Compare Match Output DISABLED (MUST, NEVER CHANGE)
			#define MTIMER0_OC0_MODE        MTIMER_OC_DISCONNECTED
		#endif

	#elif MTIMER0_MODE == MTIMER_PHASE_CORRECT_PWM

			// (OCR0) initialization range(0 - 255) [must be initialized]
		#define MTIMER0_OCR0			0

			//Interrupt Enable (if disabled, OC0 must be enabled )
		#define MTIMER0_OCIE0           MTIMER_OCIE_ENABLE
		#define MTIMER0_TOIE0           MTIMER_TOIE_ENABLE //(for pwm mode)

			//Enable/Disable OC0 pin
		#define MTIMER0_OC0_CFG			MTIMER_OCn_E

			//Force Output Compare (for CTC mode only)
		#define MTIMER0_FOC0            MTIMER_FOC_CLEAR

		#if MTIMER0_OCIE0 ==  MTIMER_OCIE_ENABLE
			//global interrupt E (must, do not change)
			#define MTimer_GINTERRUPT       MTIMER_GINTERRUPT_E
		#elif MTIMER0_OCIE0 ==  MTIMER_OCIE_DISABLE
			//global interrupt D (must, do not change)
			#define MTimer_GINTERRUPT       MTIMER_GINTERRUPT_D
		#endif

		#if MTIMER0_OC0_CFG == MTIMER_OCn_E

			//Compare Match Output DISABLED (anything but, DISCONNECTED)
			#define MTIMER0_OC0_MODE        MTIMER_TOGGLE_OC

		#elif MTIMER0_OC0_CFG == MTIMER_OCn_D
			//Compare Match Output DISABLED (MUST, NEVER CHANGE)
			#define MTIMER0_OC0_MODE        MTIMER_OC_DISCONNECTED
		#endif
#endif

/*****************************************************************************/
#elif MTIMER_SELECT == MTIMER1
	//Timer1 mode
	#define MTIMER1_MODE            MTIMER1_NORMAL

	//Timer1 Prescaller
	#define MTIMER1_PRESCALLER      MTIMER1_NO_PS

	#if MTIMER1_MODE == MTIMER1_NORMAL

		//TCNT1 initialization (default is 0, maximum 65536)
		#define MTIMER1_INIT_VALUE      0

		//Interrupt Enable (must, do not change)
		#define MTIMER1_TOIE1A          MTIMER_TOIE_DISABLE

		//global interrupt E (must, do not change)
		#define MTimer_GINTERRUPT       MTIMER_GINTERRUPT_E

	#elif MTIMER1_MODE != MTIMER1_NORMAL

		// OCR1A initialization , in range (0 - 65536)
		#define MTIMER1A_OCR1A              65536  //16 bits

		//Interrupt Enable (if disabled, OC1 must be enabled )
		#define MTIMER1_TOIE1A          MTIMER_TOIE_DISABLE
		#define MTIMER1_OCIE1A          MTIMER_OCIE_DISABLE

		//Enable/Disable OC1A pin
		#define MTIMER1_OC1A_CFG			MTIMER_OCn_D

		//global interrupt E (must, don't change)
		#define MTimer_GINTERRUPT       MTIMER_GINTERRUPT_E

		//Force Output Compare (for CTC mode only)
		#define MTIMER1_FOC1A            MTIMER_FOC_CLEAR
		#define MTIMER1B_FOC1B          MTIMER_FOC_CLEAR

		//Compare Match Output modes
		#define MTIMER1_OC1_MODE        MTIMER_CLEAR_OC



		#if MTIMER1_OCIE1A ==  MTIMER_OCIE_ENABLE

			//global interrupt E (must, do not change)
			#define MTimer_GINTERRUPT       MTIMER_GINTERRUPT_E
		#elif MTIMER1_OCIE1A ==  MTIMER_OCIE_DISABLE

			//global interrupt D (must, do not change)
			#define MTimer_GINTERRUPT       MTIMER_GINTERRUPT_D

		#endif

		#if MTIMER1_OC1A_CFG == MTIMER_OCn_E

			//Compare Match Output DISABLED (anything but, DISCONNECTED)
			#define MTIMER1_OC1A_MODE        MTIMER_TOGGLE_OC

		#elif MTIMER1_OC1A_CFG == MTIMER_OCn_D
			//Compare Match Output DISABLED (MUST, NEVER CHANGE)
			#define MTIMER1_OC1A_MODE        MTIMER_OC_DISCONNECTED
		#endif

	#endif
/*****************************************************************************/
#elif MTIMER_SELECT == MTIMER2
	//Timer2 mode
	#define MTIMER2_MODE            MTIMER_NORMAL

	//Timer2 Prescaller
	#define MTIMER2_PRESCALLER      MTIMER2_PS_1024

	#if MTIMER2_MODE == MTIMER_NORMAL
		//TCNT2 initialization (default is 0, maximum 255)
		#define MTIMER2_INIT_VALUE      0

		//Interrupt Enable (must, do not change)
		#define MTIMER2_TOIE2           MTIMER_TOIE_ENABLE

		//global interrupt E (must, do not change)
		#define MTimer_GINTERRUPT       MTIMER_GINTERRUPT_E

 	#elif MTIMER2_MODE != MTIMER_NORMAL

		// (OCR2) initialization range(0 - 255) [must be initialized]
		#define MTIMER2_OCR2			0

		//Interrupt Enable (if disabled, OC2 must be enabled )
		#define MTIMER2_OCIE2           MTIMER_OCIE_ENABLE
		#define MTIMER2_TOIE2           MTIMER_TOIE_ENABLE //(for pwm mode)

		//Enable/Disable OC2 pin
		#define MTIMER2_OC2_CFG			MTIMER_OCn_E

		//Force Output Compare (for CTC mode only)
		#define MTIMER2_FOC2            MTIMER_FOC_CLEAR

		#if MTIMER2_OCIE2 ==  MTIMER_OCn_E
			//global interrupt E (must, do not change)
			#define MTimer_GINTERRUPT       MTIMER_GINTERRUPT_E
    	#elif MTIMER2_OCIE2 ==  MTIMER_OCn_D
			//global interrupt D (must, do not change)
			#define MTimer_GINTERRUPT       MTIMER_GINTERRUPT_D
		#endif

		#if MTIMER2_OC2_CFG == MTIMER_OCn_E

			//Compare Match Output DISABLED (anything but, DISCONNECTED)
			#define MTIMER2_OC2_MODE        MTIMER_TOGGLE_OC

		#elif MTIMER2_OC2_CFG == MTIMER_OCn_D
				//Compare Match Output DISABLED (MUST, NEVER CHANGE)
				#define MTIMER2_OC2_MODE        MTIMER_OC_DISCONNECTED
		#endif

	#endif
#endif

#endif /* _MTIMER_CONFIG_H_ */
