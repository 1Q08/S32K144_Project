################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/key.c \
../Sources/led.c \
../Sources/main.c \
../Sources/uart.c 

OBJS += \
./Sources/key.o \
./Sources/led.o \
./Sources/main.o \
./Sources/uart.o 

C_DEPS += \
./Sources/key.d \
./Sources/led.d \
./Sources/main.d \
./Sources/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/%.o: ../Sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/key.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


