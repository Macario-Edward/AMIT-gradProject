/*
 * MDIO_config.h
 *
 * Created: 2/4/2023 9:44:29 PM
 *  Author: DELL 5480
 */ 


#ifndef MDIO_CONFIG_H_
#define MDIO_CONFIG_H_

#define PORTA_INIT_DIR			0xfe
#define PORTA_INIT_VALUE		0xfe

#define PORTB_INIT_DIR			MDIO_Ouput
#define PORTB_INIT_VALUE		0x01

#define PORTC_INIT_DIR			0x07
#define PORTC_INIT_VALUE		MDIO_Low

#define PORTD_INIT_DIR			0x10
#define PORTD_INIT_VALUE		0x10

#endif /* MDIO_CONFIG_H_ */