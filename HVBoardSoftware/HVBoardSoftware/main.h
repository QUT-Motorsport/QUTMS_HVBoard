/*
 * main.h
 *
 * Created: 7/09/2019 8:40:00 PM
 * Author : Jonn
 */ 

// Define LEDs
// LED A => PIN 15, PD6
// LED B => PIN 16, PD7
#define LED_A_ON		PORTD |= 0b01000000
#define LED_A_OFF		PORTD &= ~0b01000000
#define LED_A_TOGGLE	PORTD ^= ~0b01000000

#define LED_B_ON		PORTD |= 0b10000000
#define LED_B_OFF		PORTD &= ~0b10000000
#define LED_B_TOGGLE	PORTD ^= ~0b10000000

