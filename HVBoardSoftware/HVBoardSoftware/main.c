/*
 * HVBoardSoftware.c
 *
 * Created: 3/08/2019 11:53:54 AM
 * Author : Jonn
 */ 

#define F_CPU 16000000

#include <avr/io.h>
#include <util/delay.h>
#include "main.h"

int init(void) {
	// Set Up Ports
	//		 LED B			  LED A
	PORTD = (1 << PORTD7) || (1 << PORTD6);
	return 0;
}

int main(void)
{
    while (1) 
    {
		LED_A_ON;
		LED_B_OFF;
		_delay_ms(500);
		LED_A_OFF;
		LED_B_ON;
		_delay_ms(500);
    }
}

