/*
 * main.c
 *
 *  Created on: 09/02/2018  10:32 pm
 *      Author: antonius atef ghaly
 */
#include "mpu6050.h"
#include "i2c.h"
#include "uart.h"
#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"

int main(void){

	//DDRA |= (1<<0);
	//PORTA &=~(1<<0);
	//PORTA |=(1<<0);
	/* initialize mpu6050 main register such as
	 * Power Management-Gyroscope Configuration - Gyroscope Configuration
	 */
	MPU6050_Init();
	//9DDRD  = 0xFF;  //adjust data direction port D to use it to test the reading of mpu6050
	//PORTD = 0x00;  //itial output 0

	while(1){

		for(int i=1;i<2000;i++){
			uart_send_byte('s');
			_delay_ms(200);
		}

		record_Accel_Registers();  //reading the accel registers and prepare reading to be areal measure
		record_Gyro_Registers();  //reading the gyro  registers and prepare reading to be areal measure

		uart_send_byte((uint8)gyroX);
		uart_send_byte(12);
		uart_send_byte((uint8)gyroY);
		uart_send_byte(12);
		uart_send_byte((uint8)gyroZ);
		uart_send_byte(10);
		//PORTD = RaccelX;           //output the reading on port D
		_delay_ms(10);            //DELAY between reading to can be record the measures
	}
	return 0;
}
