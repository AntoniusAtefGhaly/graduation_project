/*
 * smoke_sensor.c
 *
 *  Created on:21/03/2018  06:48 pm
 *      Author: Antonius Atef
 */

#include"smoke_sensor.h"
uint8 smoke=0,old_smoke=0;

/****fun to read smoke percent from sensor*******/
void read_smoke_data(void){
	old_smoke=smoke;
	uint32 smoke_sensor_read= adc_read_channel(0); 	// read channel 0 where the smoke sensor conect
	smoke_sensor_read= smoke_sensor_read*100/1023 ;  		// precentage of smoke on air
	smoke = (uint8)smoke_sensor_read;
}


void send_smoke_data(void){
	if(smoke != old_smoke){

		uart_send_byte('s');
		_delay_ms(2);
		uart_send_byte(smoke);
	}
}

void display_smoke_data(void){
	LCD_clearScreen();
	//if(smoke != old_smoke){
		LCD_displayStringRowColumn(0,0,"SMOKE = ");
		LCD_intgerToString(smoke); 		//display the read on LCD
		LCD_displayString("  % ");		//when reads move from 3 digit to 2 or to 1 digit this to clear the over digit 100 to 99 or 10 to 9
	//}
}
void fire_alarm(void){
	on_led(RED_LED);  //give alarm
	uart_send_byte('s');
	_delay_ms(2);
	uart_send_byte(101);  //'e'
}
