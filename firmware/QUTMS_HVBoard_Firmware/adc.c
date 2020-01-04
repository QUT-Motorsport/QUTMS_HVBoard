/**
 * @file adc.c
 * @author Zoe Goodward
 * @brief Analogue to digital conversion
 * */

#include "adc.h"
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

/**
 * Initializes the analogue to digital conversion by first selecting 
 * the voltage reference and then setting the ADC Enable bit, ADEN 
 * in ADCSRA.
 * @return void
 * */
void adc_init() {
    ADCSRA = 0; // Clear
    // Right adjust result
    ADMUX &= ~(1 << ADLAR); // Clear
    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

/**
 * Sets the prescalar.
 * @return void
 * */
void adc_set_prescalar(uint8_t prescalar) {
    //ADCSRA &= ADC_PRESCALAR_MASK;
    ADCSRA |= prescalar;
}

/**
 * Reads an analogue input voltage and converts it to a 10-bit digital
 * value through successive approximation.
 * @param adc_channel Selected analogue input channel
 * @return Pass the 10 bit ADC number to requesting function
 * */
uint16_t adc_read(uint8_t adc_channel) {
    uint16_t result = 0;
    adc_channel = (ADMUX & 0b11100000) | (adc_channel & 0b00011111);
    ADMUX = adc_channel;
    ADCSRA |= (1 << ADSC);
    while (!(ADCSRA & (1 << ADIF)))
        ;
    result = ADCL;
    result |= ((0b00000011 & ADCH) << 0b00001000);
    ADCSRA |= (1 << ADIF);
    return result;
}
