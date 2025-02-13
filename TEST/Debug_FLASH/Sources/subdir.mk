################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/delay.c \
../Sources/key.c \
../Sources/led.c \
../Sources/main.c 

OBJS += \
./Sources/delay.o \
./Sources/key.o \
./Sources/led.o \
./Sources/main.o 

C_DEPS += \
./Sources/delay.d \
./Sources/key.d \
./Sources/led.d \
./Sources/main.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/delay.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


