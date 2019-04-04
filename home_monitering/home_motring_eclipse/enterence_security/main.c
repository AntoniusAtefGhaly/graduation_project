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
uint16 distance;

int main(void)
{
	LCD_init();
	UltraSonic_init();
	LCD_clearScreen();
	while(1){
		UltraSonic_display_distance();
		_delay_ms(2);
	}
}
