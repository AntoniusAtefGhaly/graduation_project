/*
 * smoke_sensor.h
 *
 *  Created on:21/03/2018  06:48 pm
 *      Author: Antonius Atef
 */
#ifndef SMOKE_SENSOR_H_
#define SMOKE_SENSOR_H_
#include "lcd.h"
#include "adc.h"
#include "buttons_leds.h"
#include "uart.h"

void read_smoke_data(void);
void send_smoke_data(void);
void display_smoke_data(void);
void fire_alarm(void);

#endif /* SMOKE_SENSOR_H_ */
