/*
 * main.c
 *
 *  Created on: 27/06/2018
 *      Author: Antonius Atef Ghaly
 */
#include "adc.h"
#include "uart.h"
#include <avr/interrupt.h>
#include"heart_pulse.h"

uint8  timer_overflow=0 ;
uint16 pulse_data=0;
uint16 upper_threshold=550;
uint16 lower_threshold=500;
uint8 beat_complete=0;
uint16 BPM_timing=0;
uint16 last_time=0;
uint8 BPM;

int main(){

	adc_init(); 	//initialize ADC driver
	uart_init();    //initialize UART

	while(1)
	{
		calculate_BPM();
		uart_send_byte(BPM);
		_delay_ms(3000);
	}
	return 0;
}
