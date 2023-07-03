#ifndef MADC_REGISTERS_H_
#define MADC_REGISTERS_H_

#define   SFIOR        (*((volatile u8*)0x50))
#define   ADCW         (*((volatile u16*)0x24))
#define   ADCL         (*((volatile u8*)0x24))
#define   ADCH         (*((volatile u8*)0x25))
#define   ADCSRA       (*((volatile u8*)0x26))
#define   ADMUX        (*((volatile u8*)0x27))

/* SFIOR */
#define ADTS2   7
#define ADTS1   6
#define ADTS0   5

/* ADCSRA */
#define ADEN    7
#define ADSC    6
#define ADATE   5
#define ADIF    4
#define ADIE    3
#define ADPS2   2
#define ADPS1   1
#define ADPS0   0

/* ADMUX */
#define REFS1   7
#define REFS0   6
#define ADLAR   5
#define MUX4    4
#define MUX3    3
#define MUX2    2
#define MUX1    1
#define MUX0    0

#endif /* MADC_REGISTERS_H_ */