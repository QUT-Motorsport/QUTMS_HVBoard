/*
 * QUTMS_HVBoard_Firmware.c
 *
 * Created: 18/09/2019 12:51:26 PM
 * Author : Zoe Goodward
 */

#define F_CPU 16000000UL /* CPU clock in Hertz */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#include "input.h"
#include "UART.h"
#include "spi.h"
#include "adc.h"
#include "MCP2517.h"
#include "MCP2517_reg.h"

#define BIT_VALUE(reg, pin) ((reg>>pin) & 1)

uint8_t HV_BOARD_DATA[3] = {0};

/*============================================================================
Function:   HV_board_init()
------------------------------------------------------------------------------
Purpose :   consolidates all the functions required for the initialisation of
			the HV board
Input   :   none
Returns :   void
Notes   :
============================================================================*/
void HV_board_init() 
{
	DDRD = 0b11000010; // LEDs as outputs
	DDRB = 0b10111000; // MOSI and SCK and CAN_CS as output, SS output
	// Set IMD Status pin as input - High = no fault, Low = failure
	DDRA = 0b00000000;
	
	CAN_CS_PORT |= (1 << CAN_CS); // CS high to turn off
	
	adc_init();
	uart0_init(9600);
	spi_init(0,0); // 1,0
	MCP2517_init();
	sei(); // Enable interrupts
}

int main(void)
{
    HV_board_init();
	
	uint8_t data[8] = {0};
	CAN_RECEIVE_ADDRESS receiveID;
	uint8_t numDataBytes;

	/**
	* @brief transmit message packet
	* CAN Packet 1
	* Byte 0									| Byte 1						| Byte 2						|
	* 0b  	  0,     	 0, 0, 0, 0,       000	| 0b00000000					| 0b00000000					|
	* HV Sense, IMD Alarm, -, -, -, IMD State	| LEM Measurement (bits 15-8)	| LEM Measurement (bits 7-0) 	|
	**/
	
    while(1) 
    {
		MCP2517_recieveMessage(&receiveID, &numDataBytes, data);
		if(receiveID == CAN_RECEIVE_ID_HV >> 18) {
			//LED_A_ON;		
			MCP2517_transmitMessage(CAN_SEND_ID_HV, 5, HV_BOARD_DATA);
			_delay_ms(100);
			//LED_A_OFF;
		}
		receiveID = 0;
		numDataBytes = 0;
		
		// Check whether the IMD Status pin is high or low (only after it's been plugged in/ running for min of 2s)
		if(BIT_VALUE(IMD_REG, IMD_STATUS) != 0) {
			data[0] |= 0b01000000;
			LED_B_ON;
		} else {
			data[0] &=~ 0b01000000;
			LED_B_OFF;
		}
		
		// Check the HV_SENSE_ON pin, High - TSAL is off, Low - TSAL is on
		if(BIT_VALUE(HV_SENSE_REG, HV_SENSE_STATUS) == 0) {
			data[0] |= 0b10000000; // Send 1 when TSAL on
			LED_A_ON;
		} else {
			data[0] &=~ 0b10000000;
			LED_A_OFF;
		}
		
		// Get the current LEM measurement
		uint16_t lemMeasurement = adc_read(0x01);
		HV_BOARD_DATA[1] = lemMeasurement >> 8;
		HV_BOARD_DATA[2] = lemMeasurement;
		//LED_A_TOGGLE;
		_delay_ms(200);
    }
}