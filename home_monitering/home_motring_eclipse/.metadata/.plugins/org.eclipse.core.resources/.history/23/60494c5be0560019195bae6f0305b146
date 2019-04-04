/*
 * adc.c
 *
 *  Created on:07/03/2018  09:02 pm
 *      Author: Antonius Atef
 */
#include "adc.h"

/**** initialize adc *****/
void adc_init(){

	/*
	 * ADMUX REGESTER
	 * bit 7:6  REFS1:REFS0  = 00 TO CHOISE AREF as input volt reference
	 * bit 5  ADLAR  = 0 TO RIGHT ADJUST OF the 2 reg high & low of ADC
	 * bit 4:0  MUX4 : MUX0 =  0000 to choise channel 0 at PORTA 0
	 */

	ADMUX =0;

	/*
	 * ADCSRA REGESTER
	 * bit7 - ADEN  = 1 to enable ADC
	 * bit -  ADIN =0 disable interupt
	 * bit 2:0 ADPS2:ADPS0 = 011 USE prescaller =8 1MHZ/8 = 125 KHZ
	 */

	ADCSRA |= (1<<ADEN) | (1<<ADPS0)| (1<<ADPS1);


}

uint16  adc_read_channel(uint8 channel_num){
	ADMUX |= channel_num;   //selecting channel which use
	channel_num &=0X07;     //BE SURE CHANNEL_num < 7;
	ADMUX |= channel_num;	//SELECT THE CHANNEL NUM
	ADCSRA |= (1<<ADSC); 	//ADC start conversion
	while(!(ADCSRA&(1<<ADIF))); //wait untle coversion occure and the interupt flage return 1
	ADCSRA &= ~(1<<ADIF);  		//clear the interupt flag to be set in next conversion
return ADC;
}
