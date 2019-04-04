/*
 * buttons_leds.c
 *
 *  Created on:07/03/2018  10:54 pm
 *      Author: Antonius Atef
 */

#include "buttons_leds.h"
void leds_init(){
	LEDS_DDR |=(1<<RED_LED)|(1<<YEL_LED)|(1<<GRN_LED);
	LEDS_PORT &=~((1<<RED_LED)|(1<<YEL_LED)|(1<<GRN_LED)) ;
}

void on_led (uint8 led_colour){
	LEDS_PORT |=(1<<led_colour);
}

void off_led (uint8 led_colour){
	LEDS_PORT &=~(1<<led_colour);
}



/***** FUNCTION FOR ENABLE INT0 (button 0)*****/
void INT0_Init(void){
	SREG &= (~(1<<7));      //disable INT general flag
	DDRD &= (~(1<<2));		//CONFIG PD2 AS INPUT PIN
	GICR |= (1<<INT0);         //enable external INT0 pin
	MCUCR |= (1<<1) |(1<<0); //SET int1 as raising edge interrupt
	SREG|=(1<<7);					//enable INT general flag
}

/***** FUNCTION FOR ENABLE INT1 (button 1)*****/
void INT1_Init(void){
	SREG &= (~(1<<7));      //disable INT general flag
	DDRD &= (~(1<<3));		//CONFIG PD2 AS INPUT PIN
	GICR |= (1<<INT1);         //enable external INT1 pin
	MCUCR |= (1<<1) |(1<<0); //SET int1 as raising edge interrupt
	SREG|=(1<<7);					//enable INT general flag
}


void LED_start_flash(void){
	for(uint8 i =0;i<10;i++){
		off_led(GRN_LED);
		_delay_ms(1);
		on_led(GRN_LED);
		_delay_ms(1);
	}
}
