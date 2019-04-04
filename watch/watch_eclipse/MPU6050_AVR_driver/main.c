/*
 * ATmega16 Interface with MPU6050
 * http://www.electronicwings.com
 *
 */

//#define F_CPU 8000000UL		/* Define CPU clock Frequency 8MHz */
#include <avr/io.h>		/* Include AVR std. library file */
#include <util/delay.h>		/* Include delay header file */
#include <inttypes.h>		/* Include integer type header file */
#include <stdlib.h>		/* Include standard library file */
#include <stdio.h>		/* Include standard I/O library file */
#include <math.h>
#include "MPU6050_res_define.h"	/* Include MPU6050 register define file */
#include "I2C_Master_H_file.h"	/* Include I2C Master header file */
#include "USART_RS232_H_file.h"	/* Include USART header file */
#include "mpu6050.h"

int main()
{
	/************* initialize global variables for filters **********/
	filter_size = 40;		// average filter window

	/************* initialize global variables for step counter fun **********/
	steps_number = 0;		//
	flag = 0 ;
	step_threshold = 50 ;	//the best value 80

	/************* initialize global variables for fallen detection **********/
	fallen_threshold = 100;	//best value 200

	/************* initialize global variables for motion states **********/
	motion_states = 0;		//0 = stop  1 = walk
	count = 400,
			steps_number2 = 0,
			steps_number1 = 0,
			motion_states = 0;	//0 = stop ,1 = walk


	I2C_Init();		/* Initialize I2C */
	Gyro_Init();		/* Initialize Gyro */
	PORTA |=(1<<0);
	USART_Init(2400);	/* Initialize USART with 9600 baud rate */

	while(1)
	{
		/*
		 * disable any non needed function , data read or data process to save speed
		 */
		Read_RawValue();	//read gyro and acc and tem data at ones
		process_reading();	//scale registers measure
		print_reading();	//print data at serial monitor using uart if you need to see any data
		filter_hanning_gyro_sum1();		//first stage filter for gero data sum **** use only one stage for speed
		filter_hanning_gyro_sum2();		//second stage filter for gero data sum  **** use only one stage for accuracy but this will be slow
		step_counter();					//count the steps and store in global variables steps_number
		fallen_detection();			//check if fallen happen and take action (alarm)
		check_motion_states();			//check state walk or stop
	}
}
