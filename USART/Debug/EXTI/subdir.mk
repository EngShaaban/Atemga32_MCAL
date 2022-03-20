################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../EXTI/EXTI_Cnfg.c \
../EXTI/EXTI_prog.c 

OBJS += \
./EXTI/EXTI_Cnfg.o \
./EXTI/EXTI_prog.o 

C_DEPS += \
./EXTI/EXTI_Cnfg.d \
./EXTI/EXTI_prog.d 


# Each subdirectory must supply rules for building sources it contributes
EXTI/%.o: ../EXTI/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


