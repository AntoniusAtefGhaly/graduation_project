################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
enterence_security.lss \

FLASH_IMAGE += \
enterence_security.hex \

EEPROM_IMAGE += \
enterence_security.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: enterence_security.elf secondary-outputs

# Tool invocations
enterence_security.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,enterence_security.map -mmcu=atmega32 -o "enterence_security.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

enterence_security.lss: enterence_security.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S enterence_security.elf  >"enterence_security.lss"
	@echo 'Finished building: $@'
	@echo ' '

enterence_security.hex: enterence_security.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex enterence_security.elf  "enterence_security.hex"
	@echo 'Finished building: $@'
	@echo ' '

enterence_security.eep: enterence_security.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex enterence_security.elf  "enterence_security.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: enterence_security.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 enterence_security.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) enterence_security.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
