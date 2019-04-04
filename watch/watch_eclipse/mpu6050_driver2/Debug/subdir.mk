################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../I2C_Master_C_file.c \
../USART_RS232_C_file.c \
../main.c \
../mpu6050.c 

OBJS += \
./I2C_Master_C_file.o \
./USART_RS232_C_file.o \
./main.o \
./mpu6050.o 

C_DEPS += \
./I2C_Master_C_file.d \
./USART_RS232_C_file.d \
./main.d \
./mpu6050.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


