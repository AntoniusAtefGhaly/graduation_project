/*
 * heart_pulse.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Hi
 */

#include "heart_pulse.h"


ISR(TIMER0_OVF_vect)
{
	timer_overflow++;
}

void timer0_init_normal_mode(void)
{
	TCNT0 = 0; //timer initial value
	TIMSK |= (1<<TOIE0); //enable overflow interrupt
	/* Configure the timer control register
	 * 1. Non PWM mode FOC0=1
	 * 2. Normal Mode WGM01=0 & WGM00=0
	 * 3. Normal Mode COM00=0 & COM01=0
	 * 4. clock = F_CPU/1024 CS00=1 CS01=0 CS02=1
	 */
	TCCR0 = (1<<FOC0) | (1<<CS02) | (1<<CS00);
}

void calculate_BPM(void){
	adc_init(); 	//initialize ADC driver
	pulse_data= adc_read_channel(0); //read ch0 where the heart sensor is connect
	/********** cal bpm *********/
	if(pulse_data>upper_threshold)
	{
		if(beat_complete)
		{
			BPM = TCNT0 - last_time;

			BPM = (int)(60/((float)BPM/1000));
			BPM_timing=0;
			beat_complete=0;
		}

		if(BPM_timing==0)
		{
			last_time=TCNT0;
			BPM_timing=1;
		}
	}

	if((pulse_data<lower_threshold)&(BPM_timing))
		beat_complete=1;
}
