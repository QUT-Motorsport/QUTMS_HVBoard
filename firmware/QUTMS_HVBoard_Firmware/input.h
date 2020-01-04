/**
 * @file input.h
 * @author Zoe Goodward
 * @brief This file defines the outputs and inputs of the pins of the MCU test 
 * */

#ifndef INPUT_H_
#define INPUT_H_

/*	Pinout

	RX			PD0
	TX			PD1
	
*/

/* CAN */
#define CAN_CS_PORT		PORTB
#define CAN_CS			PINB3
#define CAN_INT			PINB0

/* LEDS */
#define LED_A			PIND6
#define LED_B			PIND7

#define LED_A_ON		PORTD |= 0b01000000
#define LED_A_OFF		PORTD &= ~0b01000000
#define LED_B_ON		PORTD |= 0b10000000
#define LED_B_OFF		PORTD &= ~0b10000000
#define LED_A_TOGGLE	PORTD ^= 0b01000000

/* IMD */
#define IMD_REG			PINA
#define IMD_STATUS		PINA2

/* HV SENSE LINE */
#define HV_SENSE_REG	PINA
#define HV_SENSE_STATUS	PINA0

#endif /* INPUT_H_ */