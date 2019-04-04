/*
 * mpu5060.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Hi
 */

#ifndef MPU6050_H_
#define MPU6050_H_

#include "i2c.h"
#include "uart.h"

/*
 * GLOBAL VARIABLES
 */
uint16 RaccelX, RaccelY, RaccelZ;      //direct READING OF acceleration registers
uint16 RgyroX, RgyroY, RgyroZ;		 //direct READING OF gyro registers

float accelX, accelY, accelZ;		// measures of acceleration after caliberation by divide on
float gyroX, gyroY, gyroZ;			// measures of gyro after caliberation by divide on value

/******* FUNCTION to write value u8data at register of mpu6050 at address u8addr *******/
uint8 MPU6050_WRITE_REG(uint8 u8addr,uint8 u8data);

/******* FUNCTION to read data u8data from register of mpu6050 at address u8addr *******/
uint8 MPU6050_Read_REG(uint8 u8addr, uint8 *u8data);

/******* FUNCTION to initialize mpu5060 major setup & configuration *******/
void MPU6050_Init(void);

/******* FUNCTION to get accel data from 3 axis accel 6 register and store in global variables*******/
void record_Accel_Registers(void);

////////******* FUNCTION to get accel data from 3 axis accel 6 register and store in global variables*******/
void record_Gyro_Registers(void);

/* to covert read of accel register into areal read prepartional with real unit */
void process_Accel_Data(void);


/* to covert read of gyro register into areal read prepartional with real unit */
void process_Gyro_Data(void);

/**** use to check state reg and if it sucess or fail after every process ********/
#define SUCCESS 1
#define ERROR 0

/****** registe macro of mpu6050 ******/
#define PWR_MGMT_1 0x6B 	//power management 1
#define CONFIG 0X1A 		// MPU6050 Configuration
#define GYRO_CONFIG 0X1B 	//Gyroscope Configuration
#define ACCEL_CONFIG 0X1C 	// Accelerometer Configuration
/*
 * Registers 59 to 64 – Accelerometer Measurements
 */

#define ACCEL_XOUT_H 0X3B
#define ACCEL_XOUT_L 0X3C
#define	ACCEL_YOUT_H 0X3D
#define ACCEL_YOUT_L 0X3E
#define ACCEL_ZOUT_H 0X3F
#define ACCEL_ZOUT_L 0X40
/*
 * Registers 67 to 72 – Gyroscope Measurements
 */
#define GYRO_XOUT_H 0X43
#define GYRO_XOUT_L 0X44
#define	GYRO_YOUT_H 0X45
#define GYRO_YOUT_L 0X46
#define GYRO_ZOUT_H 0X47
#define GYRO_ZOUT_L 0X48
/*
 * Registers 65 and 66 – Temperature Measurement
 */
#define TEMP_OUT_H 0X41
#define TEMP_OUT_L 0X42

#endif /* MPU6050_H_ */
