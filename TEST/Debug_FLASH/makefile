################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Sources/subdir.mk
-include SDK/rtos/osif/subdir.mk
-include SDK/platform/drivers/src/pins/subdir.mk
-include SDK/platform/drivers/src/lpuart/subdir.mk
-include SDK/platform/drivers/src/interrupt/subdir.mk
-include SDK/platform/drivers/src/ftm/subdir.mk
-include SDK/platform/drivers/src/edma/subdir.mk
-include SDK/platform/drivers/src/clock/S32K1xx/subdir.mk
-include SDK/platform/drivers/src/adc/subdir.mk
-include SDK/platform/devices/S32K144/startup/subdir.mk
-include SDK/platform/devices/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Generated_Code/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
TEST.srec \

SECONDARY_SIZE += \
TEST.siz \


# All Target
all: TEST.elf secondary-outputs

# Tool invocations
TEST.elf: $(OBJS) C:/Users/zy/Desktop/githubspace/S32K144_Project/TEST/Project_Settings/Linker_Files/S32K144_64_flash.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Standard S32DS C Linker'
	arm-none-eabi-gcc -o "TEST.elf" "@TEST.args"  $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

TEST.srec: TEST.elf
	@echo 'Invoking: Standard S32DS Create Flash Image'
	arm-none-eabi-objcopy -O srec TEST.elf  "TEST.srec"
	@echo 'Finished building: $@'
	@echo ' '

TEST.siz: TEST.elf
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=berkeley -x TEST.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
