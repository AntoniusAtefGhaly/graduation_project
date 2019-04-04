/*
 * main.c
 *
 *  Created on: 28/02/2018
 *      Author: Antonius Atef Ghaly
 */

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include "lcd.h"
#include"UltraSonic.h"
#include "adc.h"
#include "buttons_leds.h"
#include "uart.h"
#include"smoke_sensor.h"
#define normal_smoke 20
#define normal_distance 130

#define FIRE 50
#define FIRE_SAFE 60
#define FIRE_DANGER 70
#define ENTRANCE 80
#define ENTRANCE_SAFE 90
#define ENTRANCE_SAFE 100

extern uint8 smoke;
extern uint16 distance;


void enterance_state(void);
void fire_state(void);
/*****ISR of INT 0 (button 0) ******/
ISR(INT0_vect){
	LCD_clearScreen();  //clear LCD
}
/*****ISR of INT 1 (button 1) ******/
ISR(INT1_vect){
	/**** do an action we chose eg :it can check the conductivity ****/
	LCD_clearScreen();  //
	send_smoke_data();
}


int main(void)
{
	INT0_Init();	//initialize and enable Interrupt 0
	INT1_Init();	//initialize and enable Interrupt 1
	leds_init(); 	//initialize led port
	LCD_init(); 	// initialize LCD driver
	adc_init(); 	//initialize ADC driver
	uart_init();    //initialize UART
	UltraSonic_init();
	LCD_clearScreen();
	LED_start_flash();
	while(1){
		 read_enterance_data();
//		 display_enterance_data();

		read_smoke_data();	//read data and store in global variable smoke
//		send_smoke_data();	//send data which read (send value of smoke )
		//display_smoke_data();	//display the value of last read
		fire_state();
		enterance_state();

	}
}


void	enterance_state(){
	/******** give fire alarm if the smoke above normal *********/
	if(distance<normal_distance){
		_delay_ms(1);
		if(distance<normal_distance){
			LCD_clearScreen();
			LCD_displayString("danger on door!!!");
			enterance_alarm();
		}
	}

	else{
		uart_send_byte(ENTRANCE);
		uart_send_byte(ENTRANCE_SAFE);
		LCD_clearScreen();
		LCD_displayString("doors:safe");
	}

}
void fire_state(void)
{
	/******** give fire alarm if the smoke above normal *********/
	if(smoke>normal_smoke){
		_delay_ms(1);
		if(smoke>normal_smoke){
			LCD_clearScreen();
			LCD_displayString("fire !!!!");
			fire_alarm();
		}
	}

	else{
		uart_send_byte(FIRE);
		uart_send_byte(FIRE_SAFE);
		LCD_clearScreen();
		LCD_displayString("fire state :safe");
	}
}
