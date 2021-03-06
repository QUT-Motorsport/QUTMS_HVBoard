/**
 * @file adc.h
 * @author Zoe Goodward
 * @brief Analogue to digital conversion
 * */

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define ADC_PRESCALE_MASK		0b11111000

void adc_init();
uint16_t adc_read(uint8_t adc_channel);

#endif /* ADC_H_ */