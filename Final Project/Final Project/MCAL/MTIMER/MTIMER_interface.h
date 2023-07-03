#ifndef MTIMER_INTERFACE_H_
#define MTIMER_INTERFACE_H_

typedef enum{
	MTIMER_Busy, MTIMER_Free
}MTIMER_State;

//Timers (0 , 1 , 2)
#define MTIMER0		0
#define MTIMER1		1
#define MTIMER2		2

//Timer0/2 modes
#define MTIMER_NORMAL             0
#define MTIMER_PHASE_CORRECT_PWM  1
#define MTIMER_CTC                2
#define MTIMER_FAST_PWM           3

//Timer1 modes
#define MTIMER1_NORMAL                   		0
#define MTIMER1_PHASE_CORRECT_PWM_8BIT   		1
#define MTIMER1_PHASE_CORRECT_PWM_9BIT   		2
#define MTIMER1_PHASE_CORRECT_PWM_10BIT 		3
#define MTIMER1_CTC            		    		4
#define MTIMER1_FAST_PWM_8BIT  		    		5
#define MTIMER1_FAST_PWM_9BIT            		6
#define MTIMER1_FAST_PWM_10BIT           		7
#define MTIMER1_PHASE_FREQ_CORRECT_PWM_ICR1     8  //Top @ ICR1
#define MTIMER1_PHASE_FREQ_CORRECT_PWM_OCR1A    9  //Top @ OCR1A
#define MTIMER1_PHASE_CORRECT_PWM_ICR1   		10 //Top @ ICR1
#define MTIMER1_PHASE_CORRECT_PWM_OCR1A  		11 //Top @ OCR1A
#define MTIMER1_CTC_ICR1             		 	12 //Top @ ICR1

#define MTIMER1_FAST_PWM_ICR1            		14 //Top @ ICR1
#define MTIMER1_FAST_PWM_OCR1A           		15 //Top @ OCR1A

//Compare Match Output modes (for all timers)
#define MTIMER_OC_DISCONNECTED    0  //Normal Mode Operation
#define MTIMER_TOGGLE_OC          1
#define MTIMER_CLEAR_OC           2
#define MTIMER_SET_OC             3

//Timer0 prescaler modes
#define MTIMER0_NO_CLK     0   //(Timer/Counter) stopped
#define MTIMER0_NO_PS      1
#define MTIMER0_PS_8       2
#define MTIMER0_PS_64      3
#define MTIMER0_PS_256     4
#define MTIMER0_PS_1024    5
#define MTIMER0_EXT_CLK_F  6   //Falling Edge
#define MTIMER0_EXT_CLK_R  7   //Rising  Edge

//Timer1 Prescaller modes
#define MTIMER1_NO_CLK     0   //(Timer/Counter) stopped
#define MTIMER1_NO_PS      1
#define MTIMER1_PS_8       2
#define MTIMER1_PS_64      3
#define MTIMER1_PS_256     4
#define MTIMER1_PS_1024    5
#define MTIMER1_EXT_CLK_F  6   //Falling Edge
#define MTIMER1_EXT_CLK_R  7   //Rising  Edge

//Timer2 Prescaller modes
#define MTIMER2_NO_CLK     0   //(Timer/Counter) stopped
#define MTIMER2_NO_PS      1
#define MTIMER2_PS_8       2
#define MTIMER2_PS_32      3
#define MTIMER2_PS_64      4
#define MTIMER2_PS_128     5
#define MTIMER2_PS_256     6
#define MTIMER2_PS_1024    7

//Force Output Compare (for all timers)
#define MTIMER_FOC_SET   		1
#define MTIMER_FOC_CLEAR 		0

// Timer Interrupt Enable (for all timers)
#define MTIMER_OCIE_ENABLE      1  // Timer/Counter0 Output Compare Match Interrupt Enable
#define MTIMER_OCIE_DISABLE     0  // Timer/Counter0 Output Compare Match Interrupt Disable

#define MTIMER_TOIE_ENABLE      1  // Timer/Counter0 Overflow Interrupt Enable
#define MTIMER_TOIE_DISABLE     0  // Timer/Counter0 Overflow Interrupt Disable

//Global interrupt
#define MTIMER_GINTERRUPT_E     1  // Global Interrupt Enable
#define MTIMER_GINTERRUPT_D     0  // Global Interrupt Disable

#define MTIMER_OCn_E			1  //Enable OCn
#define MTIMER_OCn_D			0  //Disable OCn

tenumFncErrorState MTimer0_enuInit(void);
tenumFncErrorState MTimer1_enuInit(void);
tenumFncErrorState MTimer2_enuInit(void);

void MTIMER_voidTIM0OVFSetCallBack(void(*function_ptr) (void));
void MTIMER_voidTIM0COMPSetCallBack(void(*function_ptr) (void));
void MTIMER_voidTIM1OVFSetCallBack(void(*function_ptr) (void));
void MTIMER_voidTIM1COMPASetCallBack(void(*function_ptr) (void));
void MTIMER_voidTIM1COMPBSetCallBack(void(*function_ptr) (void));
void MTIMER_voidTIM1CAPTSetCallBack(void(*function_ptr) (void));
void MTIMER_voidTIM2OVFSetCallBack(void(*function_ptr) (void));
void MTIMER_voidTIM2COMPSetCallBack(void(*function_ptr) (void));

#endif /* MTIMER_INTERFACE_H_ */
