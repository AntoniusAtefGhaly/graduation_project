/*
 * main.c
 *
 *  Created on: 28/02/2018
 *      Author: Antonius Atef Ghaly
 */
#include "lcd.h"
#include "adc.h"
#include "buttons_leds.h"
#include "uart.h"
#include"smoke_sensor.h"
#include <avr/interrupt.h>
#define normal_smoke 20
extern uint8 smoke;

/*****ISR of INT 0 (button 0) ******/
ISR(INT0_vect){
	LCD_clearScreen();  //clear LCD
}
/*****ISR of INT 1 (button 1) ******/
ISR(INT1_vect){
	/**** do an action we chose eg :it can check the conductivity ****/
	LCD_clearScreen();  //
	_delay_ms(1);
	send_smoke_data();
	_delay_ms(1);
}

int main(){
	INT0_Init();	//initialize and enable Interrupt 0
	INT1_Init();	//initialize and enable Interrupt 1
	leds_init(); 	//initialize led port
	LCD_init(); 	// initialize LCD driver
	adc_init(); 	//initialize ADC driver
	uart_init();    //initialize UART

	/*******initialize system display flash led to idicate system work *******/
	for(uint8 i =0;i<10;i++){
		off_led(GRN_LED);
		_delay_ms(1);
		on_led(GRN_LED);
		_delay_ms(1);
	}

	while(1)
	{
		read_smoke_data();	//read data and store in global variable smoke
		send_smoke_data();	//send data which read (send value of smoke )
		display_smoke_data();	//display the value of last read
		/******** give fire alarm if the smoke above normal *********/
		if(smoke>normal_smoke){
			_delay_ms(1);
			if(smoke>normal_smoke){
				fire_alarm();
				_delay_ms(10);
				fire_alarm();
			}
		}
	}
	return 0;
}
