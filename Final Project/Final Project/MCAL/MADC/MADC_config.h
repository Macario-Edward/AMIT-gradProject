#ifndef MADC_CONFIG_H_
#define MADC_CONFIG_H_

#include "MADC_interface.h"

//set ADC channel
#define MADC_CHANNEL MADC_Channel_1

//adc reference voltage (MADC_AREF : AREF, Internal Vref turned off ,
//						 MADC_AVCC : AVCC with external capacitor at AREF pin,
//						 MADC_IREF : Internal 2.56V Voltage Reference with external cap at AREF)
#define MADC_REF MADC_AVCC

//adc prescaler (MADC_PS_2,MADC_PS_4, MADC_PS_8, MADC_PS_16, MADC_PS_32, MADC_PS_64, MADC_PS_128)
#define MADC_PRESCALER MADC_PS_64

//adc justify (MADC_8BIT for 8-bit read  or MADC_10BIT for 10-bit read)
#define MADC_JUSTIFY MADC_10BIT

//adc mode (MADC_SINGLE_CONV, MADC_AUTO_TRIG_CONV)
#define MADC_CONV_MODE	MADC_SINGLE_CONV

//adc type(MADC_INT, MADC_POLLING)
#define MADC_TYPE		MADC_POLLING

#endif /* MADC_CONFIG_H_ */
