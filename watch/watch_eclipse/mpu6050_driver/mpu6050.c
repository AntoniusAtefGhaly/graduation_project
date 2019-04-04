/*
 * mpu6050.c
 *  Created on: 09/02/2018  10:36 pm
 *      Author: antonius atef ghaly
 */
#include "mpu6050.h"

/******* FUNCTION to write value u8data at register of mpu6050 at address u8addr *******/
uint8 MPU6050_WRITE_REG(uint8 u8addr,uint8 u8data){
	TWI_Start();
    if (TWI_Get_Status() != TW_START)
        return ERROR;

    //write the device address  R/W=0 (write)
    TWI_Write(0b11010000);
    if (TWI_Get_Status() != TW_MT_SLA_W_ACK)
        return ERROR;

    //send the required location address
    TWI_Write((uint8)(u8addr));
    if (TWI_Get_Status() != TW_MT_DATA_ACK)
        return ERROR;

    //write byte to mpu6050
    TWI_Write(u8data);
    if (TWI_Get_Status() != TW_MT_DATA_ACK)
        return ERROR;

    TWI_Stop();

    return SUCCESS;
}




/******* FUNCTION to read data u8data from register of mpu6050 at address u8addr *******/
uint8 MPU6050_Read_REG(uint8 u8addr, uint8 *u8data){

    TWI_Start();
    if (TWI_Get_Status() != TW_START)
        return ERROR;

    //write the device address and so we need to get A8 A9 A10 address bits and R/W=0 (write)
    TWI_Write(0b11010000);
    if (TWI_Get_Status() != TW_MT_SLA_W_ACK)
        return ERROR;

    //send the required location address
    TWI_Write((uint8)(u8addr));
    if (TWI_Get_Status() != TW_MT_DATA_ACK)
        return ERROR;

    //send a repeated start
    TWI_Start();
    if (TWI_Get_Status() != TW_REP_START)
        return ERROR;

    //write the device address and so we need to get A8 A9 A10 address bits and R/W=1 (Read)
    TWI_Write(0b11010001);
    if (TWI_Get_Status() != TW_MT_SLA_R_ACK)
        return ERROR;

    *u8data = TWI_Read_With_NACK();
    if (TWI_Get_Status() != TW_MR_DATA_NACK)
        return ERROR;

    TWI_Stop();
    return SUCCESS;
}
/******* FUNCTION to initialize mpu5060 major setup & configuration *******/
void MPU6050_Init(void){

	/******* PWR_MGMT_1 ******
	 *  MPU-6000/MPU-6050 Register Map and Descriptions (page 40)
	 * - bit 7 ( DEVICE_RESET) : When set to 1, this bit resets all internal registers to their default values.
		The bit automatically clears to 0 once the reset is done.
		The default values for each register can be found in Section 3.

		- bit 6 (SLEEP) : When set to 1, this bit puts the MPU-60X0 into sleep mode.

		- bit 5 (CYCLE) :  When this bit is set to 1 and SLEEP is disabled, the MPU-60X0 will cycle
		between sleep mode and waking up to take a single sample of data from active sensors at
 	 	 a rate determined by LP_WAKE_CTRL (register 108).

		- bit 4 : reserved

		- bit 3 (TEMP_DIS) :  When set to 1, this bit disables the temperature sensor.

		- bit 2-0 (CLKSEL) :  3-bit unsigned value. Specifies the clock source of the device.
	 */
	MPU6050_WRITE_REG(PWR_MGMT_1,0X00);

	/******* GYRO_CONFIG ********
	 *   MPU-6000/MPU-6050 Register Map and Descriptions (page 15)
	 * - bit 7 (XG_ST) :  When set to 1, the X- Axis gyroscope performs self test.
		-BIT 6 (YG_ST) :  Setting this bit causes the Y axis gyroscope to perform self test.
		-BIT 5 (ZG_ST) : Setting this bit causes the Z axis gyroscope to perform self test.
		-bit 4-3(FS_SEL): 2-bit unsigned value. Selects the full scale range of gyroscopes.
		- bit2-0 : reserved .
	 */
	MPU6050_WRITE_REG(GYRO_CONFIG,0X00);

	/******* ACCEL_CONFIG ********
		 *   MPU-6000/MPU-6050 Register Map and Descriptions (page 15)
		 * - bit 7 (XA_ST) :  When set to 1, the X- Axis accelerometer performs self test.
			-BIT 6 (YA_ST) :  Setting this bit causes the Y axis accelerometer to perform self test.
			-BIT 5 (ZA_ST) : Setting this bit causes the Z axis accelerometer to perform self test.
			-bit 4-3(AFS_SEL): 2-bit unsigned value. Selects the full scale range of accelerometer.
			- bit2-0 : reserved .
		 */
	MPU6050_WRITE_REG(ACCEL_CONFIG,0X00);
}


/******* FUNCTION to get accel data from 3 axis accel 6 register and store in global variables*******/
void record_Accel_Registers(void){
	uint8 reg_H=0,reg_L=0;
	MPU6050_Read_REG(ACCEL_XOUT_H,&reg_H);
	MPU6050_Read_REG(ACCEL_XOUT_L,&reg_L);
	RaccelX =  (reg_H<<8) | reg_L;

	MPU6050_Read_REG(ACCEL_YOUT_H,&reg_H);
	MPU6050_Read_REG(ACCEL_YOUT_L,&reg_L);
	RaccelY =  (reg_H<<8) | reg_L;

	MPU6050_Read_REG(ACCEL_ZOUT_H,&reg_H);
	MPU6050_Read_REG(ACCEL_ZOUT_L,&reg_L);
	RaccelZ =  (reg_H<<8) | reg_L;
}


////////******* FUNCTION to get accel data from 3 axis accel 6 register and store in global variables*******/
void record_Gyro_Registers(void){
	uint8 reg_H=0,reg_L=0;

	MPU6050_Read_REG(GYRO_XOUT_H,&reg_H);
	MPU6050_Read_REG(GYRO_XOUT_L,&reg_L);
	RaccelX =  (reg_H<<8) | reg_L;

	MPU6050_Read_REG(GYRO_YOUT_H,&reg_H);
	MPU6050_Read_REG(GYRO_YOUT_L,&reg_L);
	RaccelY =  (reg_H<<8) | reg_L;

	MPU6050_Read_REG(GYRO_ZOUT_H,&reg_H);
	MPU6050_Read_REG(GYRO_ZOUT_L,&reg_L);
	RaccelZ =  (reg_H<<8) | reg_L;
}


/* to covert read of accel register into areal read prepartional with real unit */
void process_Accel_Data(void){

	accelX = RaccelX / 16384.0;
	accelY = RaccelY / 16384.0;
	accelZ = RaccelZ / 16384.0;
}

/* to covert read of gyro register into areal read prepartional with real unit */
void process_Gyro_Data(void){
	gyroX = RgyroX / 131.0;
	gyroY = RgyroX / 131.0;
	gyroZ = RgyroX / 131.0;
}
