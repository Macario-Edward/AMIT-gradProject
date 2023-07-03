#ifndef _MINT_REGISTERS_H_
#define _MINT_REGISTERS_H_

#define   SREG         (*((volatile u8*)0x5F))
#define   GICR         (*((volatile u8*)0x5B))
#define   GIFR         (*((volatile u8*)0x5A))
#define   MCUCR        (*((volatile u8*)0x55))
#define   MCUCSR       (*((volatile u8*)0x54))

/* GICR */
#define INT1    7
#define INT0    6
#define INT2    5
#define IVSEL   1
#define IVCE    0

/* GIFR */
#define INTF1   7
#define INTF0   6
#define INTF2   5

/* MCUCR */
#define ISC11   3
#define ISC10   2
#define ISC01   1
#define ISC00   0

/* MCUCSR */
#define ISC2    6

/* SREG */
#define I		7  //global interrupt enable

#endif /* _MINT_REGISTERS_H_ */
