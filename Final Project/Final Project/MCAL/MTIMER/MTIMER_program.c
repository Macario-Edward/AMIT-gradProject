
//main avr libraries
#include "util/delay.h"
#include "avr/interrupt.h"
//used libraries
#include "../../Libraries_/LIB_STDTypes.h"
#include "../../Libraries_/LIB_BMNP.h"

//MTIMERS
#include "MTIMER_interface.h"
#include "MTIMER_config.h"
#include "MTIMER_registers.h"

#include "../MINT/MINT_Registers.h"
#include "../MDIO/MDIO_interface.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static volatile void (*G_TIMER0_OVF)   (void)= NULL ;
static volatile void (*G_TIMER0_COMP)  (void)= NULL ;
static volatile void (*G_TIMER1_OVF)   (void)= NULL ;
static volatile void (*G_TIMER1_COMPA) (void)= NULL ;
static volatile void (*G_TIMER1_COMPB) (void)= NULL ;
static volatile void (*G_TIMER1_CAPT)  (void)= NULL ;
static volatile void (*G_TIMER2_OVF)   (void)= NULL ;
static volatile void (*G_TIMER2_COMP)  (void)= NULL ;

/*******************************************************************************
 *                                 ISR'S                                       *
 *******************************************************************************/

/**********************************TIMER0***************************************/
ISR(TIMER0_OVF_vect)
{
	if (G_TIMER0_OVF!= NULL)
	{
		(*G_TIMER0_OVF)();
	}
}
ISR(TIMER0_COMP_vect)
{
	if (G_TIMER0_COMP!= NULL)
	{
		(*G_TIMER0_COMP)();
	}
}

/**********************************TIMER1***************************************/

ISR(TIMER1_OVF_vect)
{
	if (G_TIMER1_OVF!= NULL)
	{
		(*G_TIMER1_OVF)();
	}
}

ISR(TIMER1_COMPA_vect)
{
	if (G_TIMER1_COMPA!= NULL)
	{
		(*G_TIMER1_COMPA)();
	}
}

ISR(TIMER1_COMPB_vect)
{
	if (G_TIMER1_COMPB!= NULL)
	{
		(*G_TIMER1_COMPB)();
	}
}
/*
ISR(TIMER1_CAPT_vect)
{
	if (G_TIMER1_CAPT != NULL)
	{
		(*G_TIMER1_COMPB)();
	}
}
*/
/**********************************TIMER2***************************************/

ISR(TIMER2_OVF_vect)
{
	if (G_TIMER2_OVF!= NULL)
	{
		(*G_TIMER2_OVF)();
	}
}

ISR(TIMER2_COMP_vect)
{
	if (G_TIMER2_COMP!= NULL)
	{
		(*G_TIMER2_COMP)();
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 ****************************************************** *************************/

tenumFncErrorState MTimer0_enuInit(void)
{
	tenumFncErrorState ReturnFncState = LSTY_EXECUTED_SUCCESSFULLY;

	      // Set Timer0 prescaller
		#if MTIMER0_PRESCALLER   ==  MTIMER0_NO_CLK // no clock
	  		  TCCR0 &=~(1<<CS02) & ~(1<<CS01) & ~(1<<CS00);
	  	#elif MTIMER0_PRESCALLER == MTIMER0_NO_PS // no prescaller
	  		  TCCR0 &=~(1<<CS02) & ~(1<<CS01);
	  	      TCCR0 |= (1 << CS00);
	  	#elif MTIMER0_PRESCALLER ==  MTIMER0_PS_8 // Prescaler 8
	  		  TCCR0 &=~(1<<CS02) & ~(1<<CS00);
	  	      TCCR0 |= (1 << CS01);
	  	#elif MTIMER0_PRESCALLER ==  MTIMER0_PS_64 // Prescaler 64
	  	      TCCR0 &=~(1<<CS02);
	  	      TCCR0 |= (1 << CS01) | (1 << CS00);
	  	#elif MTIMER0_PRESCALLER ==  MTIMER0_PS_256 // Prescaler 256
	  	      TCCR0 |= (1 << CS02);
	  		  TCCR0 &=~(1<<CS01) & ~(1<<CS00);
	  	#elif MTIMER0_PRESCALLER ==  MTIMER0_PS_1024 // Prescaler 1024
	  	      TCCR0 |= (1 << CS02) | (1 << CS00);
	  	      TCCR0 &=~(1<<CS01);
	  	#elif MTIMER0_PRESCALLER ==  MTIMER0_EXT_CLK_F // Ex. clock at falling edge
	  	      TCCR0 |= (1 << CS02) | (1 << CS01);
	  	      TCCR0 &=~(1<<CS00);
	      #elif MTIMER0_PRESCALLER ==  MTIMER0_EXT_CLK_R // Ex. clock at rising edge
	  	      TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);
	  	#endif

	  	//Timer0 modes
	  	#if MTIMER0_MODE == MTIMER_NORMAL
	  		TCCR0 &=~(1 << WGM01) & ~(1<<WGM00);
	  		//TCNT0 initialization
	  		//TCNT0 = MTIMER0_INIT_VALUE ; (UnComment it if chosen)

	  		//Interrupt Enable (must, do not change)
	  	    SET_BIT(TIMSK, TOIE0);
	  	    //global interrupt E (must, do not change)
	  	    SET_BIT(SREG, I);

	  	#elif MTIMER0_MODE == MTIMER_PHASE_CORRECT_PWM
	  	    TCCR0 |=(1 << WGM00);
	  		TCCR0 &=~(1<<WGM01);
	  	#elif MTIMER0_MODE == MTIMER_CTC
	  		TCCR0 &=~(1<<WGM00);
	  		TCCR0 |= (1 << WGM01);
	  	  #elif MTIMER0_MODE == MTIMER_FAST_PWM
	  		TCCR0 |= (1 << WGM01) | (1 << WGM00);

	      #endif

		#if MTIMER0_MODE != MTIMER_NORMAL

	  			// (OCR0) initialization range(0 - 255) [must be initialized]
	  			OCR0   = MTIMER0_OCR0;

	  		//Overflow Interrupt Enable/Disable
			#if MTIMER0_OCIE0 == MTIMER_OCIE_ENABLE
	  			SET_BIT(TIMSK, OCIE0);
	  			SET_BIT(SREG, I);
			#elif MTIMER0_OCIE0 == MTIMER_OCIE_DISABLE
	  			CLR_BIT(TIMSK, OCIE0);
			#endif

	  	  	//Output Compare Match Interrupt Enable/Disable
			#if MTIMER0_TOIE0 == MTIMER_TOIE_ENABLE
	  			SET_BIT(TIMSK, TOIE0);
	  			SET_BIT(SREG, I);
			#elif MTIMER0_TOIE0 == MTIMER_TOIE_DISABLE
	  			CLR_BIT(TIMSK, TOIE0);
			#endif

	  	  	//Force Output Compare
			#if MTIMER0_FOC0 == MTIMER_FOC_CLEAR
	  			CLR_BIT(TCCR0, FOC0);
			#elif MTIMER0_FOC0 == MTIMER_FOC_SET
	  			SET_BIT(TCCR0, FOC0);
			#endif

			#if MTIMER0_OC0_CFG == MTIMER_OCn_E
	  			//Compare Match Output DISABLED (anything but, DISCONNECTED)
				#if MTIMER0_OC0_MODE == MTIMER_OC_DISCONNECTED
	  				TCCR0 |= (0 << COM01) | (0 << COM00);
				#elif MTIMER0_OC0_MODE == MTIMER_TOGGLE_OC
	  				TCCR0 |= (0 << COM01) | (1 << COM00);
				#elif MTIMER0_OC0_MODE == MTIMER_CLEAR_OC
	  				TCCR0 |= (1 << COM01) | (0 << COM00);
				#elif MTIMER0_OC0_MODE == MTIMER_SET_OC
	  				TCCR0 |= (1 << COM01) | (1 << COM00);
				#endif
	  			//Enable OC0 pin (MUST, NEVER CHANGE)
				  DIO_Pin PD3;
				  PD3.enumPin = MDIO_PIN3;
				  PD3.enumPort = MDIO_PORTD;
				  MDIO_enumPinDirection(&PD3);
			#elif MTIMER0_OC0_CFG == MTIMER_OCn_D
	  			//Compare Match Output DISABLED (MUST, NEVER CHANGE)
	  			TCCR0 |= (0 << COM01) | (0 << COM00);
			#endif
		#endif

	return ReturnFncState;
}

tenumFncErrorState MTimer1_enuInit(void)
{
	tenumFncErrorState ReturnFncState = LSTY_EXECUTED_SUCCESSFULLY;

	// Set Timer1 prescaller
	#if MTIMER1_PRESCALLER   ==  MTIMER1_NO_CLK
	      TCCR1B &=~(1 << CS12) & ~(1 << CS11) & ~(1 << CS10); // no clock
	#elif MTIMER1_PRESCALLER == MTIMER1_NO_PS
	      TCCR1B |= (1 << CS10); // no prescaller
	      TCCR1B &=~(1 << CS12) & ~(1 << CS11);
	#elif MTIMER1_PRESCALLER ==  MTIMER1_PS_8
	      TCCR1B |=(1 << CS11); // Prescaler 8
	      TCCR1B &=~(1 << CS12) & ~(1 << CS10);
	#elif MTIMER1_PRESCALLER ==  MTIMER1_PS_64
	      TCCR1B |= (1 << CS11) | (1 << CS10); // Prescaler 64
	      TCCR1B &=~(1 << CS12);
	#elif MTIMER1_PRESCALLER ==  MTIMER1_PS_256
	      TCCR1B |= (1 << CS12); // Prescaler 256
	      TCCR1B &=~(1 << CS11) & ~(1 << CS10);
	#elif MTIMER1_PRESCALLER ==  MTIMER1_PS_1024
	      TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler 1024
	      TCCR1B &=~(1 << CS11);
	#elif MTIMER1_PRESCALLER ==  MTIMER1_EXT_CLK_F
	      TCCR1B |= (1 << CS12) | (1 << CS11); // falling edge
	      TCCR1B &=~(1 << CS10);
    #elif MTIMER1_PRESCALLER ==  MTIMER1_EXT_CLK_R
	      TCCR1B |= (1 << CS12) | (1 << CS11) | (1 << CS10); // rising edge
	#endif

	//Timer1 modes
	#if MTIMER1_MODE == MTIMER1_NORMAL //0
	    TCCR1A &= ~(0 << WGM11) & ~(0 << WGM10);
	    TCCR1B &= ~(0 << WGM13) & ~(0 << WGM12);
		//TCNT1 initialization
		//TCNT1H = MTIMER1_INIT_VALUE >> 8 ; //(UnComment it if chosen)
		//TCNT1L = MTIMER1_INIT_VALUE & 0x00ff ; //(UnComment it if chosen)

		//Interrupt Enable (must, do not change)
	    SET_BIT(TIMSK, OCIE1A);
	    //global interrupt E (must, do not change)
	    SET_BIT(SREG, I);

	#elif MTIMER1_MODE == MTIMER1_PHASE_CORRECT_PWM_8BIT //1
      TCCR1A |=  | (1 << WGM10);
      TCCR1B &= ~(1 << WGM13) & ~(1 << WGM12);
      TCCR1A &= ~(1 << WGM11);

	#elif MTIMER1_MODE == MTIMER1_PHASE_CORRECT_PWM_9BIT //2
      TCCR1A |= (1 << WGM11);
      TCCR1A &=~(1 << WGM10);
      TCCR1B &= ~(1 << WGM13) & ~(1 << WGM12);
	#elif MTIMER1_MODE == MTIMER1_PHASE_CORRECT_PWM_10BIT //3
      TCCR1A |= (1 << WGM11) | (1 << WGM10);
      TCCR1B &= ~(1 << WGM13) & ~(1 << WGM12);
	#elif MTIMER1_MODE == MTIMER1_CTC //4
      TCCR1A &= ~(1 << WGM11) & ~(1 << WGM10);
      TCCR1B &= ~(1 << WGM13);
      TCCR1B |= (1 << WGM12);
	#elif MTIMER1_MODE == MTIMER1_FAST_PWM_8BIT //5
      TCCR1A |=(1 << WGM10);
      TCCR1B &= ~(1 << WGM13);
      TCCR1B |= (1 << WGM12);
      TCCR1A &=~(1 << WGM11);
	#elif MTIMER1_MODE == MTIMER1_FAST_PWM_9BIT //6
      TCCR1A |= (1 << WGM11);
      TCCR1B |= (1 << WGM12);
      TCCR1A &=~(1 << WGM10);
      TCCR1B &=~(1 << WGM13);
	#elif MTIMER1_MODE == MTIMER1_FAST_PWM_10BIT //7
      TCCR1A |= (1 << WGM11) | (1 << WGM10);
      TCCR1B |= (1 << WGM12);
      TCCR1B &=~(1 << WGM13);
	#elif MTIMER1_MODE == MTIMER1_PHASE_FREQ_CORRECT_PWM_ICR1 //8
      TCCR1A &= ~(1 << WGM11) & ~(1 << WGM10);
      TCCR1B |= (1 << WGM13);
      TCCR1B &=~(1 << WGM12);
	#elif MTIMER1_MODE == MTIMER1_PHASE_FREQ_CORRECT_PWM_OCR1A //9
      TCCR1A |=(1 << WGM10);
      TCCR1B |= (1 << WGM13);
      TCCR1B &=~(1 << WGM12);
      TCCR1A &=~(1 << WGM11);
	#elif MTIMER1_MODE == MTIMER1_PHASE_CORRECT_PWM_ICR1 //10
      TCCR1A &=~(1 << WGM10);
      TCCR1A |= (1 << WGM11);
      TCCR1B &=~(1 << WGM12);
      TCCR1B |= (1 << WGM13);
	#elif MTIMER1_MODE == MTIMER1_PHASE_CORRECT_PWM_OCR1A //11
      TCCR1A |= (1 << WGM11) | (1 << WGM10);
      TCCR1B |= (1 << WGM13);
      TCCR1B &=~(1 << WGM12);
	#elif MTIMER1_MODE == MTIMER1_CTC_ICR1 //12
      TCCR1A &= ~(1 << WGM11) & ~(1 << WGM10);
      TCCR1B |= (1 << WGM13) | (1 << WGM12);
	#elif MTIMER1_MODE == MTIMER1_FAST_PWM_ICR1 //14
      TCCR1A |= (1 << WGM11);
      TCCR1B |= (1 << WGM13) | (1 << WGM12);
      TCCR1A &=~(1 << WGM10);
	#elif MTIMER1_MODE == MTIMER1_FAST_PWM_OCR1A
      TCCR1A |= (1 << WGM11) | (1 << WGM10); //15
      TCCR1B |= (1 << WGM13) | (1 << WGM12);
	#endif

	#if MTIMER1_MODE != MTIMER_NORMAL

		// (OCR1A) initialization range(0 - 255) [must be initialized]
		OCR1AH   = MTIMER1A_OCR1A >> 8;
		OCR1AH   = MTIMER1A_OCR1A & 0x00ff;

		//Overflow Interrupt Enable/Disable
		#if MTIMER1_OCIE1A == MTIMER_OCIE_ENABLE
			SET_BIT(TIMSK, OCIE1A);
			SET_BIT(SREG, I);
		#elif MTIMER1_OCIE1A == MTIMER_OCIE_DISABLE
			CLR_BIT(TIMSK, OCIE1A);
		#endif

	  	//Output Compare Match Interrupt Enable/Disable
		#if MTIMER1_TOIE1A == MTIMER_TOIE_ENABLE
			SET_BIT(TIMSK, TOIE1);
			SET_BIT(SREG, I);
		#elif MTIMER1_TOIE1A == MTIMER_TOIE_DISABLE
			CLR_BIT(TIMSK, TOIE1);
		#endif

	    //Force Output Compare
		#if ((MTIMER1A_FOC1A == MTIMER_FOC_CLEAR) && (MTIMER1B_FOC1B == MTIMER_FOC_CLEAR))
			CLR_BIT(TCCR1A, FOC1A);
			CLR_BIT(TCCR1A, FOC1B);
		#elif ((MTIMER1A_FOC1A == MTIMER_FOC_SET) && (MTIMER1B_FOC1B == MTIMER_FOC_SET))
			SET_BIT(TCCR1A, FOC1A);
			SET_BIT(TCCR1A, FOC1B);
		#elif MTIMER1A_FOC1A == MTIMER_FOC_SET
			SET_BIT(TCCR1A, FOC1A);
			CLR_BIT(TCCR1A, FOC1B);
		#elif MTIMER1B_FOC1B == MTIMER_FOC_SET
			CLR_BIT(TCCR1A, FOC1A);
			SET_BIT(TCCR1A, FOC1B);
		#endif

		#if MTIMER1_OC1A_CFG == MTIMER_OCn_E
			//Compare Match Output DISABLED (anything but, DISCONNECTED)
			#if MTIMER1_OC1_MODE == MTIMER_OC_DISCONNECTED
				TCCR1A &=~(1 << COM1A0) & ~(1 << COM1A1);
			#elif MTIMER0_OC0_MODE == MTIMER_TOGGLE_OC
				TCCR1A |=(1 << COM1A0);
				TCCR1A &=~(1 << COM1A1);
			#elif MTIMER0_OC0_MODE == MTIMER_CLEAR_OC
				TCCR1A |= (1 << COM1A1);
				TCCR1A &=~(1 << COM1A0);
			#elif MTIMER0_OC0_MODE == MTIMER_SET_OC
				TCCR1A |= (1 << COM1A1) | (1 << COM1A0);
			#endif
			//Enable OC1 pin (MUST, NEVER CHANGE)
			DIO_Pin PD5;
			PD3.enumPin = MDIO_PIN5;
			PD3.enumPort = MDIO_PORTD;
			MDIO_enumPinDirection(&PD5);//make the pin OC1A (PIND5) output
		#elif MTIMER1_OC1A_CFG == MTIMER_OCn_D
			//Compare Match Output DISABLED (MUST, NEVER CHANGE)
			TCCR1A &=~(1 << COM1A0) & ~(1 << COM1A1);
		#endif
	#endif

	return ReturnFncState;
}

tenumFncErrorState MTimer2_enuInit(void)
{
	tenumFncErrorState ReturnFncState = LSTY_EXECUTED_SUCCESSFULLY;

			// Set Timer2 prescaller

			#if MTIMER2_PRESCALLER   ==  MTIMER2_NO_CLK
	      	  	  TCCR2 &= ~(1 << CS22) & ~(1 << CS21) & ~(1 << CS20); // no clock
			#elif MTIMER2_PRESCALLER == MTIMER2_NO_PS
	      	  	  TCCR2 |= (1 << CS20); // no prescaller
	      	  	  TCCR2 &=~(1 << CS22);
	      	  	  TCCR2 &=~(1 << CS21);
			#elif MTIMER2_PRESCALLER ==  MTIMER2_PS_8
	      	  	  TCCR2 |= (1 << CS21); // Prescaler 8
	      	  	  TCCR2 &=~(1 << CS22);
	      	  	  TCCR2 &=~(1 << CS20);
			#elif MTIMER2_PRESCALLER ==  MTIMER2_PS_32
	      	  	  TCCR2 |=(1 << CS21) | (1 << CS20); // Prescaler 32
	      	  	  TCCR2 &=~(1 << CS22);
			#elif MTIMER2_PRESCALLER ==  MTIMER2_PS_64
	      	  	  TCCR2 |= (1 << CS22); // Prescaler 64
	      	  	  TCCR2 &=~(1 << CS20);
	      	      TCCR2 &=~(1 << CS21);
			#elif MTIMER2_PRESCALLER ==  MTIMER2_PS_128
	      	  	  TCCR2 |= (1 << CS22) |(1 << CS20); // Prescaler 128
	      	  	  TCCR2 &=~(1 << CS21);
			#elif MTIMER2_PRESCALLER ==  MTIMER2_PS_256
	      	  	  TCCR2 |= (1 << CS22) | (1 << CS21); // Prescaler 256
	      	  	  TCCR2 &=~(1 << CS20);
    		#elif MTIMER2_PRESCALLER ==  MTIMER2_PS_1024
	      	  	  TCCR2 |= (1 << CS22) | (1 << CS21) | (1 << CS20); // Prescaler 1024
			#endif


		#if MTIMER2_MODE == MTIMER_NORMAL
	  	    TCCR2 &= ~(1 << WGM21) & ~(1 << WGM20);
	  		//TCNT2 initialization
	  		//TCNT2 = MTIMER2_INIT_VALUE ; (UnComment it if chosen)
	  	    //Interrupt Enable (must, do not change)
	  	    SET_BIT(TIMSK, TOIE2);
	  	    //global interrupt E (must, do not change)
	  	    SET_BIT(SREG, I);
		#elif MTIMER2_MODE == MTIMER_PHASE_CORRECT_PWM
	  	    TCCR2 |=(1 << WGM20);
	  	    TCCR2 &= ~(1 << WGM21);
		#elif MTIMER2_MODE == MTIMER_CTC
	  	    TCCR2 |= (1 << WGM21);
	  	    TCCR2 &= ~(1 << WGM20)
		#elif MTIMER2_MODE == MTIMER_FAST_PWM
	  	    TCCR2 |= (1 << WGM21) | (1 << WGM20);
		#endif

		#if MTIMER0_MODE != MTIMER_NORMAL

	  		// (OCR2) initialization range(0 - 255) [must be initialized]
	  		OCR2   = MTIMER2_OCR2;

	  		//Overflow Interrupt Enable/Disable
			#if MTIMER2_OCIE2 == MTIMER_OCIE_ENABLE
	  			SET_BIT(TIMSK, OCIE2);
				SET_BIT(SREG, I);
			#elif MTIMER2_OCIE2 == MTIMER_OCIE_DISABLE
	  			CLR_BIT(TIMSK, OCIE2);
			#endif

	  	    //Output Compare Match Interrupt Enable/Disable
    		#if MTIMER2_TOIE2 == MTIMER_TOIE_ENABLE
	  			SET_BIT(TIMSK, TOIE2);
				SET_BIT(SREG, I);
			#elif MTIMER2_TOIE2 == MTIMER_TOIE_DISABLE
	  			CLR_BIT(TIMSK, TOIE2);
			#endif

	  		//Force Output Compare
	  		#if MTIMER2_FOC2 == MTIMER_FOC_CLEAR
	  		    CLR_BIT(TCCR2, FOC2);
	  		#elif MTIMER2_FOC2 == MTIMER_FOC_SET
	  		    SET_BIT(TCCR2, FOC2);
	  		#endif

			#if MTIMER2_OC2_CFG == MTIMER_OCn_E
	  			//Compare Match Output DISABLED (anything but, DISCONNECTED)
				#if MTIMER2_OC2_MODE == MTIMER_OC_DISCONNECTED
	  				TCCR2 &= ~(1 << COM21) & ~(1 << COM20);
				#elif MTIMER2_OC2_MODE == MTIMER_TOGGLE_OC
	  				TCCR2 |=(1 << COM20);
	  				TCCR2 &= ~(1 << COM21);
				#elif MTIMER2_OC2_MODE == MTIMER_CLEAR_OC
	  				TCCR2 |= (1 << COM21);
	  				TCCR2 &= ~(1 << COM20);
				#elif MTIMER2_OC2_MODE == MTIMER_SET_OC
	  				TCCR2 |= (1 << COM21) | (1 << COM20);
				#endif
	  			//Enable OC2 pin (MUST, NEVER CHANGE)
				 DIO_Pin PD7;
				 PD3.enumPin = MDIO_PIN7;
				 PD3.enumPort = MDIO_PORTD;
				 MDIO_enumPinDirection(&PD7);
			#elif MTIMER2_OC2_CFG == MTIMER_OCn_D
	  			//Compare Match Output DISABLED (MUST, NEVER CHANGE)
	  			TCCR2 &= ~(1 << COM21) & ~(1 << COM20);
			#endif
		#endif

	return ReturnFncState;
}

/*******************************CALL BACK**************************************

/**********************************TIMER0***************************************/
 void MTIMER_voidTIM0OVFSetCallBack(void(*function_ptr) (void))
{
	G_TIMER0_OVF = function_ptr ;
}

void MTIMER_voidTIM0COMPSetCallBack(void(*function_ptr) (void))
{
	G_TIMER0_COMP=function_ptr ;
}

/**********************************TIMER1***************************************/
void MTIMER_voidTIM1OVFSetCallBack(void(*function_ptr) (void))
{
	G_TIMER1_OVF=function_ptr ;
}

void MTIMER_voidTIM1COMPASetCallBack(void(*function_ptr) (void))
{
	G_TIMER1_COMPA=function_ptr ;
}

void MTIMER_voidTIM1COMPBSetCallBack(void(*function_ptr) (void))
{
	G_TIMER1_COMPB=function_ptr ;
}

void MTIMER_voidTIM1CAPTSetCallBack(void(*function_ptr) (void))
{
	G_TIMER1_CAPT=function_ptr ;
}

/**********************************TIMER2***************************************/
void MTIMER_voidTIM2OVFSetCallBack(void(*function_ptr) (void))
{
	G_TIMER2_OVF=function_ptr ;
}

void MTIMER_voidTIM2COMPSetCallBack(void(*function_ptr) (void))
{
	G_TIMER2_COMP=function_ptr ;
}

/********************************************************************************/