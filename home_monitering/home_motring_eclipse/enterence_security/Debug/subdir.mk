################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../UltraSonic.c \
../adc.c \
../buttons_leds.c \
../lcd.c \
../main.c \
../smoke_sensor.c \
../uart.c 

OBJS += \
./UltraSonic.o \
./adc.o \
./buttons_leds.o \
./lcd.o \
./main.o \
./smoke_sensor.o \
./uart.o 

C_DEPS += \
./UltraSonic.d \
./adc.d \
./buttons_leds.d \
./lcd.d \
./main.d \
./smoke_sensor.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


