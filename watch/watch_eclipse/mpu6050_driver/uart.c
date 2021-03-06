/*
 * uart.c
 *
 *  Created on: 21/03/2018 10:12 am
 *      Author: Antonius Atef Ghaly
 */
#include "uart.h"

#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 8UL))) - 1)


/*****fun to initial uart**********/
void uart_init(){
	/************************ UCSRA register ***********************/
	/*bit 1 :  U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X);

	/************************** UCSRB Description *********************
	 * bit 7 : RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * bit 6 : TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * bit 5 :UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * bit 4 : RXEN  = 1 Receiver Enable
	 * bit 3 : RXEN  = 1 Transmitter Enable
	 * bit 2 : UCSZ2 = 0 For 8-bit data mode
	 * bit 1&0 : RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	UCSRB = (1<<RXEN) | (1<<TXEN); //enable RX and TX

	/************************** UCSRC register **************************
	 * bit 7 : URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * bit 6 : UMSEL   = 0 Asynchronous Operation
	 * bit 5-4 : UPM1:0  = 00 Disable parity bit
	 * bit 3 : USBS    = 0 One stop bit
	 * bit 2-1 : UCSZ1:0 = 11 For 8-bit data mode
	 * bit 0 : UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1); //sel 8 bit mode

	/************************** UBRRH &UBRRL  registers **************************/
	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
		UBRRH = BAUD_PRESCALE>>8;
		UBRRL = BAUD_PRESCALE;

}

/************fun to send byte *************/
void uart_send_byte(uint8 data){
	/// wait for flag UDRE is 1
	//if UDRE=1 the buffer is empty and ready to be written
	while( !(UCSRA|(1<<UDRE)) ){}
	// writre data to data reg
UDR=data;
}

/*****fun to recieve byte ***********/
uint8 uart_recirve_byte(){
	/// wait for flag RXC is 1
	//if RXC=1 the UART recieve complete

	while( !(UCSRA|(1<<RXC)) ){}
	return UDR ;
}

/******** fun to send string ************/
void uart_send_string(uint8* string){
	uint8 i=0;
	while (string[i] != '\0'){
		uart_send_byte(string[i]);
		i++;
	}
}


void uart_recievr_string(uint8* string){
	uint8 i=0;
	while (string[i] != '#'){
	string[i]=uart_recirve_byte();
			i++;
		}
	string[i]='\0';
}
