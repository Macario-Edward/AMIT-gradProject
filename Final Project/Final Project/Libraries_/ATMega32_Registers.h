#ifndef ATMega32_Features_h
#define ATMega32_Features_h

/* I/O Registers */
#define   TWBR         (*((volatile u8*)0x20))
#define   TWSR         (*((volatile u8*)0x21))
#define   TWAR         (*((volatile u8*)0x22))
#define   TWDR         (*((volatile u8*)0x23))

/* Analog Comparator */
#define   ACSR         (*((volatile u8*)0x28))


/* EEPROM Control Register */
#define   EECR         (*((volatile u8*)0x3C))

/* EEPROM Data Register */
#define   EEDR         (*((volatile u8*)0x3D))

/* EEPROM Address Register */
#define   EEAR         (*((volatile u16*)0x3E))
#define   EEARL        (*((volatile u8*)0x3E))
#define   EEARH        (*((volatile u8*)0x3F))

#define   ASSR         (*((volatile u8*)0x42))


#define   TWCR         (*((volatile u8*)0x56))

#define   SPMCR        (*((volatile u8*)0x57))

#define   SPL          (*((volatile u8*)0x5D))
#define   SPH          (*((volatile u8*)0x5E))


/* Bit numbers */

/* SPMCR */
#define SPMIE   7
#define RWWSB   6
/* bit 5 reserved */
#define RWWSRE  4
#define BLBSET  3
#define PGWRT   2
#define PGERS   1
#define SPMEN   0

/* TWCR */
#define TWINT   7
#define TWEA    6
#define TWSTA   5
#define TWSTO   4
#define TWWC    3
#define TWEN    2
/* bit 1 reserved */
#define TWIE    0

/* TWAR */
#define TWA6    7
#define TWA5    6
#define TWA4    5
#define TWA3    4
#define TWA2    3
#define TWA1    2
#define TWA0    1
#define TWGCE   0

/* TWSR */
#define TWS7    7
#define TWS6    6
#define TWS5    5
#define TWS4    4
#define TWS3    3
/* bit 2 reserved */
#define TWPS1   1
#define TWPS0   0

/* MCUCR */
#define SE      7
#define SM2     6
#define SM1     5
#define SM0     4
#define ISC11   3
#define ISC10   2
#define ISC01   1
#define ISC00   0

/* MCUCSR */
#define JTD     7
#define ISC2    6
/* bit 5 reserved */
#define JTRF    4
#define WDRF    3
#define BORF    2
#define EXTRF   1
#define PORF    0

/* SFIOR */
#define ACME    3
#define PUD     2
#define PSR2    1
#define PSR10   0

/* ASSR */
/* bits 7-4 reserved */
#define AS2     3
#define TCN2UB  2
#define OCR2UB  1
#define TCR2UB  0




/* ACSR */
#define ACD     7
#define ACBG    6
#define ACO     5
#define ACI     4
#define ACIE    3
#define ACIC    2
#define ACIS1   1
#define ACIS0   0

/* EEPROM Control Register */
#define EERIE   3
#define EEMWE   2
#define EEWE    1
#define EERE    0

/* Constants */
#define SPM_PAGESIZE 128
#define RAMEND      0x85F
#define XRAMEND     RAMEND
#define E2END       0x3FF
#define E2PAGESIZE  4
#define FLASHEND    0x7FFF


#endif

