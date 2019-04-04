/*
 * mpu5060.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Hi
 */

#ifndef MPU6050_H_
#define MPU6050_H_
#include <avr/io.h>		/* Include AVR std. library file */
#include <util/delay.h>		/* Include delay header file */
#include <inttypes.h>		/* Include integer type header file */
#include <stdlib.h>		/* Include standard library file */
#include <stdio.h>		/* Include standard I/O library file */
#include <math.h>
#include "MPU6050_res_define.h"	/* Include MPU6050 register define file */
#include "I2C_Master_H_file.h"	/* Include I2C Master header file */
#include "USART_RS232_H_file.h"	/* Include USART header file */


	/*************  global variables for reading data **********/
float Acc_x,Acc_y,Acc_z,Temperature,Gyro_x,Gyro_y,Gyro_z;
char buffer[20], float_[10];
float Xa , Ya , Za , t ;
float Xg,Yg,Zg ;

/*************  global variables for filters **********/
float  acc_sum , acc_sumF , acc_sumFF ;
float  gyro_sum , gyro_sumF , gyro_sumFF ;
int filter_size;
float buffer_gyro_sum [100], buffer_gyro_sumF [100];

/*************  global variables for step counter function **********/
float threshold,avgAcc;    //to compare value of acc with it;
int steps_number,flag , step_threshold ;


/*************  global variables for step counter function **********/
int fallen_threshold;

/***************loacl variable for motion states fun ***********/
 int count,steps_number2,steps_number1;
 char motion_states;	//0 = stop ,1 = walk


void Gyro_Init();		/* Gyro initialization function */

void MPU_Start_Loc();

void Read_RawValue();

void process_reading(void);

void print_reading(void);

void filter_hanning_gyro_sum1(void);

void filter_hanning_gyro_sum2(void);

void step_counter(void);

void fallen_detection(void);

void check_motion_states(void);

#endif /* MPU6050_H_ */
