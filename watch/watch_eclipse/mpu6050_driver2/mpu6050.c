/*
 * mpu6050.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Hi
 */
#include "mpu6050.h"

/*
 *
 */
void Gyro_Init()		/* Gyro initialization function */
{
	_delay_ms(150);		/* Power up time >100ms */
	I2C_Start_Wait(0xD0);	/* Start with device write address */


	I2C_Write(SMPLRT_DIV);	/* Write to sample rate register */
	I2C_Write(0x07);	/* 1KHz sample rate */
	I2C_Stop();

	PORTA |=(1<<0);
	I2C_Start_Wait(0xD0);
	I2C_Write(PWR_MGMT_1);	/* Write to power management register */
	I2C_Write(0x01);	/* X axis gyroscope reference frequency */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(CONFIG);	/* Write to Configuration register */
	I2C_Write(0x00);	/* Fs = 8KHz */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(GYRO_CONFIG);	/* Write to Gyro configuration register */
	I2C_Write(0x18);	/* Full scale range +/- 2000 degree/C */
	I2C_Stop();

	I2C_Start_Wait(0xD0);
	I2C_Write(INT_ENABLE);	/* Write to interrupt enable register */
	I2C_Write(0x01);
	I2C_Stop();
}


/*
 *
 */
void MPU_Start_Loc()
{
	I2C_Start_Wait(0xD0);	/* I2C start with device write address */
	I2C_Write(ACCEL_XOUT_H);/* Write start location address from where to read */
	I2C_Repeated_Start(0xD1);/* I2C start with device read address */
}
/*
 *
 */
void Read_RawValue()
{
	MPU_Start_Loc();									/* Read Gyro values */
	Acc_x = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Acc_y = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Acc_z = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Temperature = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Gyro_x = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Gyro_y = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Ack());
	Gyro_z = (((int)I2C_Read_Ack()<<8) | (int)I2C_Read_Nack());
	I2C_Stop();
}

/*
 *
 */
void process_reading(void){
	/* Divide raw value by sensitivity scale factor */
	Xa = Acc_x/16384.0;
	Ya = Acc_y/16384.0;
	Za = Acc_z/16384.0;
	acc_sum = Xa + Ya + Za;

	Xg = Gyro_x/16.4;
	Yg = Gyro_y/16.4;
	Zg = Gyro_z/16.4;
	gyro_sum = Xg + Yg + Zg;
	/* Convert temperature in /c using formula */
	t = (Temperature/340.00)+36.53;
}


/*
 *
 */
void print_reading(void){
	/* Take values in buffer to send all parameters over USART */
	dtostrf( Xa, 3, 2, float_ );
	sprintf(buffer," Ax = %s g\t",float_);
	USART_SendString(buffer);

	dtostrf( Ya, 3, 2, float_ );
	sprintf(buffer," Ay = %s g\t",float_);
	USART_SendString(buffer);

	dtostrf( Za, 3, 2, float_ );
	sprintf(buffer," Az = %s g\t",float_);
	USART_SendString(buffer);

	dtostrf( t, 3, 2, float_ );
	sprintf(buffer," T = %s%cC\t",float_,0xF8);
	USART_SendString(buffer);

	dtostrf( Xg, 3, 2, float_ );
	sprintf(buffer," Gx = %s%c/s\t",float_,0xF8);
	USART_SendString(buffer);

	dtostrf( Yg, 3, 2, float_ );
	sprintf(buffer," Gy = %s%c/s\t",float_,0xF8);
	USART_SendString(buffer);

	dtostrf( Zg, 3, 2, float_ );
	sprintf(buffer," Gz = %s%c/s\r\t",float_,0xF8);
	USART_SendString(buffer);

	dtostrf( steps_number, 3, 2, float_ );
	sprintf(buffer," steps = %s%c\r\t",float_,0xF8);
	USART_SendString(buffer);

	dtostrf( motion_states, 3, 2, float_ );
	sprintf(buffer," state = %s%c\r\n",float_,0xF8);
	USART_SendString(buffer);
}

/*
 *
 */
void filter_hanning_gyro_sum1(void){
	for(int i=filter_size-1;i>1;i--){
		buffer_gyro_sum[i] = buffer_gyro_sum[i-1];
	}
	buffer_gyro_sum[1]=gyro_sum;

	gyro_sumF = 0;
	for(int i=0;i<filter_size;i++){
		gyro_sumF = gyro_sumF + buffer_gyro_sum[i];
	}
	gyro_sumF =gyro_sumF/filter_size;
}

/*
 *
 */

void filter_hanning_gyro_sum2(void){
	for(int i=filter_size-1;i>1;i--){
		buffer_gyro_sumF[i] = buffer_gyro_sumF[i-1];
	}
	buffer_gyro_sumF[1]=gyro_sumF;

	gyro_sumFF = 0;
	for(int i=0;i<filter_size;i++){
		gyro_sumFF = gyro_sumFF + buffer_gyro_sumF[i];
	}
	gyro_sumF =gyro_sumFF/filter_size;
}

/*
 *
 */
void step_counterX() {
	avgAcc = Xg;		//1 stage filter
	//avgAcc = gyro_sumFF; 		//2 stage filter

	if (avgAcc >= step_thresholdX && flag_stepX == 0 ){
		steps_numberX = steps_numberX + 1;
		flag_stepX=1;
	}
	else if((avgAcc >=step_thresholdX) && (flag_stepX == 1)) {
	}
	else{
		flag_stepX =0;
	}
}





void step_counterY() {
	avgAcc = Yg;		//1 stage filter
	//avgAcc = gyro_sumFF; 		//2 stage filter

	if (avgAcc >= step_thresholdY && flag_stepY == 0 ){
		steps_numberY = steps_numberY + 1;
		flag_stepY=1;
	}
	else if((avgAcc >=step_thresholdY) && (flag_stepY == 1)) {
	}
	else{
		flag_stepY =0;
	}
}

void step_counterZ() {
	avgAcc = Zg;		//1 stage filter
	//avgAcc = gyro_sumFF; 		//2 stage filter

	if (avgAcc >= step_thresholdZ && flag_stepZ == 0 ){
		steps_numberZ = steps_numberZ + 1;
		flag_stepZ=1;
	}
	else if((avgAcc >=step_thresholdZ) && (flag_stepZ == 1)) {
	}
	else{
		flag_stepZ =0;
	}
}


void step_counter() {
	steps_number = ( steps_numberY + steps_numberZ)/2;
}

/*
 *
 */

/*
void fallen_detection(void)
{

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

*//*
	diff_Xa = (pre_Xa - Xa)*(pre_Xa - Xa) ;     //to find diffrential measusure (A(t-1)-A(t))
	diff_Ya = (pre_Ya - Ya)*(pre_Ya - Ya) ;
	diff_Za = (pre_Za - Za)*(pre_Za - Za) ;

	Asvm = sqrt( Xa*Xa + Ya*Ya + Za*Za);      //A_sum_vector_magnitude
	theta = abs(atan((double)sqrt( Ya*Ya + Za*Za )/ Xa) *(180/3.14));    //angle
	Adsvm =sqrt (diff_Xa + diff_Ya + diff_Za);       //A_differential_sum_vector_magnitude
	Agsvm =  (theta / 90) * Asvm;   //gravity-weighted_sum_vector_magnitude
	Agdsvm =  (theta
	/ 90) * Adsvm;  //gravity-weighted_differential_sum_vector_magnitude

	fallen_parameter = (int)Adsvm * 100;
	if ((fallen_parameter >= fallen_threshold) &&( flag_fallen == 0 )){

		/*****************************************************
		 WRIE ACTION OR ALARM FOR FALLEN ALARM FOR FALLEN
		 ******************************************************/
	/*	USART_SendString("**********************************************");
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
*/
/*
 *
 */
void check_motion_states(void){
	count++;
	if(count==4000){
		steps_number2=steps_number;
		if( ((steps_number2 - steps_number1) <= 3)){
			motion_states =0;			//0 = stop
		}
		if( ((steps_number2 - steps_number1) > 3) && (steps_number2 - steps_number1) < 5){
					motion_states =1;	//1 = walk
				}
		else
		{
			motion_states =2;         //2 = run
		}
		count = 0;
		steps_number1 = steps_number2;
	}
}
