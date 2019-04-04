/*
 * heart_pulse.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Hi
 */

#ifndef HEART_PULSE_H_
#define HEART_PULSE_H_
#include "adc.h"
#include "uart.h"
#include <avr/interrupt.h>

void calculate_BPM(void);
extern uint8  timer_overflow ;
extern uint8 BPM;
extern uint16 pulse_data;
extern uint16 upper_threshold;
extern uint16 lower_threshold;
extern uint8 beat_complete;
extern uint16 BPM_timing;
extern uint16 last_time;
#endif /* HEART_PULSE_H_ */
