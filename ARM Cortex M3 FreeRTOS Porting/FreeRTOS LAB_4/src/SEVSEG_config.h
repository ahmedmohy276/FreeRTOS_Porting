/********************************************************************/
/* Author   : Ahmed Mohy						    				*/
/* Date	    : 25 DEC 2021											*/
/* Version  : V01													*/
/********************************************************************/



#ifndef SEVSEG_CONFIG_H
#define SEVSEG_CONFIG_H

/* Options :    COMMON_ANODE_SEVSEG
				COMMON_CATHODE_SEVSEG
				*/
#define		SEVSEG_TYPE		COMMON_CATHODE_SEVSEG



/* Put the value in pair port,pin */
#define 	SEVSEG1_PINA			PORTA,PIN1
#define 	SEVSEG1_PINB			PORTA,PIN2
#define 	SEVSEG1_PINC			PORTA,PIN3
#define 	SEVSEG1_PIND 			PORTA,PIN4
#define 	SEVSEG1_PINE			PORTA,PIN5
#define 	SEVSEG1_PINF			PORTA,PIN6
#define 	SEVSEG1_PING			PORTA,PIN7



#define 	SEVSEG2_PINA			PORTB,PIN0
#define 	SEVSEG2_PINB			PORTB,PIN1
#define 	SEVSEG2_PINC			PORTB,PIN5
#define 	SEVSEG2_PIND 			PORTB,PIN6
#define 	SEVSEG2_PINE			PORTB,PIN7
#define 	SEVSEG2_PINF			PORTB,PIN8
#define 	SEVSEG2_PING			PORTB,PIN9



#endif
