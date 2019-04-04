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
	steps_numberX = 0;		//
	flag_stepX = 0 ;
	step_thresholdX = 20 ;	//the best value 80

	steps_numberY = 0;		//
		flag_stepY = 0 ;
		step_thresholdY = 30 ;	//the best value 80

		steps_numberZ = 0;		//
			flag_stepZ = 0 ;
			step_thresholdZ = 30 ;	//the best value 80




	/************* initialize global variables for fallen detection **********/
	fallen_threshold = 100;	//best value 200
	flag_fallen = 0;
	/************* initialize global variables for motion states **********/
	motion_states = 0;		//0 = stop  1 = walk
	count = 4000,
			steps_number2 = 0,
			steps_number1 = 0,
			motion_states = 0;	//0 = stop ,1 = walk




	float Asvm  = 0       //A_sum_vector_magnitude
			,Adsvm = 0    //A_differential_sum_vector_magnitude
			,theta = 0   //angle
			,Agsvm  = 0    //gravity-weighted_sum_vector_magnitude
			,Agdsvm = 0 ; //gravity-weighted_differential_sum_vector_magnitude

			float pre_Xa =0                                             //save A(t) to A(t-1)
			,pre_Ya=0
			,pre_Za=0

			,diff_Xa = 0     //to find diffrential measusure (A(t-1)-A(t))
			,diff_Ya = 0
			,diff_Za = 0;
	int fallen_parameter=0;




	void fallen_detection(void)
	{
		/*
		float Asvm  = 0       //A_sum_vector_magnitude
				,Adsvm = 0    //A_differential_sum_vector_magnitude
				,theta = 0   //angle
				,Agsvm  = 0    //gravity-weighted_sum_vector_magnitude
				,Agdsvm = 0 ; //gravity-weighted_differential_sum_vector_magnitude

				float pre_Xa =0                                             //save A(t) to A(t-1)
				,pre_Ya=0
				,pre_Za=0

				,diff_Xa = 0     //to find diffrential measusure (A(t-1)-A(t))
				,diff_Ya = 0
				,diff_Za = 0;
		int fallen_parameter=0;

	*/
		diff_Xa = (pre_Xa - Xa)*(pre_Xa - Xa) ;     //to find diffrential measusure (A(t-1)-A(t))
		diff_Ya = (pre_Ya - Ya)*(pre_Ya - Ya) ;
		diff_Za = (pre_Za - Za)*(pre_Za - Za) ;

		Asvm = sqrt( Xa*Xa + Ya*Ya + Za*Za);      //A_sum_vector_magnitude
		theta = abs(atan((double)sqrt( Ya*Ya + Za*Za )/ Xa) *(180/3.14));    //angle
		Adsvm =sqrt (diff_Xa + diff_Ya + diff_Za);       //A_differential_sum_vector_magnitude
		Agsvm =  (theta / 90) * Asvm;   //gravity-weighted_sum_vector_magnitude
		Agdsvm =  (theta / 90) * Adsvm;  //gravity-weighted_differential_sum_vector_magnitude

		fallen_parameter = (int)Adsvm * 100;
		if ((fallen_parameter >= fallen_threshold) &&( flag_fallen == 0 )){

			/*****************************************************
			 *WRIE ACTION OR ALARM FOR FALLEN ALARM FOR FALLEN
			 ******************************************************/
			USART_SendString("*****");
			flag_fallen=1;
		}
		else if((fallen_parameter >= fallen_threshold) && (flag_fallen == 1)) {
		}

		else{
			flag_fallen =0;
		}
		pre_Xa = Xa ;                                             //save A(t) to A(t-1)
		pre_Ya = Ya ;
		pre_Za = Za ;
	}


	I2C_Init();		/* Initialize I2C */
	Gyro_Init();		/* Initialize Gyro */
	PORTA |=(1<<0);
	USART_Init(1200);	/* Initialize USART with 9600 baud rate */

	while(1)
	{
		/*
		 * disable any non needed function , data read or data process to save speed
		 */
		Read_RawValue();	//read gyro and acc and tem data at ones
		process_reading();	//scale registers measure
		print_reading();	//print data at serial monitor using uart if you need to see any data
		//filter_hanning_gyro_sum1();		//first stage filter for gero data sum **** use only one stage for speed
		//filter_hanning_gyro_sum2();		//second stage filter for gero data sum  **** use only one stage for accuracy but this will be slow
		//step_counterX();					//count the steps and store in global variables steps_number
		step_counterY();					//count the steps and store in global variables steps_number
		step_counterZ();					//count the steps and store in global variables steps_number
		step_counter();					//count the steps and store in global variables steps_number

		fallen_detection();			//check if fallen happen and take action (alarm)
		check_motion_states();			//check state walk or stop
	}
}
