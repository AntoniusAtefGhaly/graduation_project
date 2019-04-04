/*
 * uart.h
*
*  Created on: 21/03/2018 10:12 am
*      Author: Antonius Atef Ghaly
*/

#ifndef UART_H_
#define UART_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

#define USART_BAUDRATE 9600

void uart_init(void);

void uart_send_byte(uint8 data);

uint8 uart_recirve_byte(void);

void uart_send_string(uint8* str);

void uart_recievr_string(uint8* str);

#endif /* UART_H_ */
