/*
 * UltraSonic.h
 *
 *  Created on: 4Apr.,2019
 *      Author: Hi
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

void UltraSonic_init(void);
int	getDistance(void);
void enterance_alarm(void);
void read_enterance_data(void);
void display_enterance_data(void);

#endif /* ULTRASONIC_H_ */
