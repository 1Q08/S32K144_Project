################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SDK/platform/pal/src/can/can_pal.c 

OBJS += \
./SDK/platform/pal/src/can/can_pal.o 

C_DEPS += \
./SDK/platform/pal/src/can/can_pal.d 


# Each subdirectory must supply rules for building sources it contributes
SDK/platform/pal/src/can/%.o: ../SDK/platform/pal/src/can/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@SDK/platform/pal/src/can/can_pal.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


