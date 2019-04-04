/*
 * buttons_leds.h
 *
 *  Created on:07/03/2018  10:54 pm
 *      Author: Antonius Atef Ghaly
 */

#ifndef BUTTONS_LEDS_H_
#define BUTTONS_LEDS_H_


#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"


#define LEDS_PORT PORTB
#define LEDS_DDR DDRB

#define RED_LED PB0
#define YEL_LED PB1
#define GRN_LED PB2

#define SW0 PD2
#define SW1 PD3
void leds_init();
void flash_led (uint8);
void on_led (uint8 led_colour);
void off_led (uint8 led_colour);
void INT0_Init(void);
void INT1_Init(void);
void press_sw(uint8);

#endif /* BUTTONS_LEDS_H_ */
