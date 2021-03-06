/*
 * UltraSonic.c
 *
 *  Created on: 4Apr.,2019
 *      Author: Hi
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#include"UltraSonic.h"
#include "lcd.h"
#include"buttons_leds.h"
int TimerOverflow = 0,distance;

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;	/* Increment Timer Overflow count */
}

void UltraSonic_init(void)
{
	DDRD |=(1<<PD7);
	PORTD |=(1<<6);
	sei();			/* Enable global interrupt */
	TIMSK = (1 << TOIE1);	/* Enable Timer1 overflow interrupts */
	TCCR1A = 0;		/* Set all bit to zero Normal operation */

}

int	getDistance(void)
{
	int distance=0,count=0;
	/**** GENERATE triger pulse 10 usec to trig pin ****/
	PORTD |= (1 << 7);
	_delay_us(10);
	PORTD &= (~(1 << 7));

	/***** detect the raising edge of the echo pulse
	 *  (indicate the start time of reflect wave)*/
	TCNT1 = 0;	 /* Clear Timer counter */
	TCCR1B =(1<<ICES1) | (1<<CS11)|(1<<CS10);	/* Capture on rising edge prescaler=64*/
	TIFR = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
	TIFR = 1<<TOV1;	/* Clear Timer Overflow flag */
	/*Calculate width of Echo by Input Capture (ICP) */

	while ((TIFR & (1 << ICF1)) == 0); /* Wait for rising edge */

	/***** detect the fallen edge of the echo pulse
	 *  (indicate the end time of reflect wave)*/
	TCNT1 = 0;	/* Clear Timer counter */
	TCCR1B =(1<<CS11)|(1<<CS10);	/* Capture on falling edge,prescaler=64 */
	//TCCR1B =(1<<CS12);	/* Capture on falling edge,prescaler=256 */
	//TCCR1B =(1<<CS11);	/* Capture on falling edge,prescaler=8*/

	TIFR = 1<<ICF1;	/* Clear ICP flag (Input Capture flag) */
	TIFR = 1<<TOV1;	/* Clear Timer Overflow flag */
	while ((TIFR & (1 << ICF1)) == 0);/* Wait for falling edge */
	count = ICR1;	/* Take count */
	/* 8MHz Timer freq, sound speed =343 m/s */
	/*
	 * dis = 0.5 * (no of counts *pres * 340 m/s) / (clk freq)
	 */
	//distance = count/735; //in meter count/735

	distance = count/7; //in cm
return distance;
}


void read_enterance_data(void){
	distance=getDistance();
}
void display_enterance_data(void){
	LCD_clearScreen();
	LCD_displayString( "Distance =  ");
	LCD_goToRowColumn(1,5);
	LCD_intgerToString(distance);
	LCD_displayString( " cm ");

}

void enterance_alarm(void){
	on_led(RED_LED);  //give alarm
	uart_send_byte('t');
	_delay_ms(2);
	uart_send_byte(100);  //'e'
}
