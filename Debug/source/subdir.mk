################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/LEDs.c \
../source/PWM.c \
../source/UART.c \
../source/accelerometer.c \
../source/adc.c \
../source/command_processing.c \
../source/i2c.c \
../source/llfifo.c \
../source/main.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/sysclock.c \
../source/systick.c \
../source/test_funcs.c 

C_DEPS += \
./source/LEDs.d \
./source/PWM.d \
./source/UART.d \
./source/accelerometer.d \
./source/adc.d \
./source/command_processing.d \
./source/i2c.d \
./source/llfifo.d \
./source/main.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/sysclock.d \
./source/systick.d \
./source/test_funcs.d 

OBJS += \
./source/LEDs.o \
./source/PWM.o \
./source/UART.o \
./source/accelerometer.o \
./source/adc.o \
./source/command_processing.o \
./source/i2c.o \
./source/llfifo.o \
./source/main.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/sysclock.o \
./source/systick.o \
./source/test_funcs.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -D$(GEN_OPTS_FLAG) -I"C:\Users\Dell Latitude\Desktop\CUB\PES\1_assignment\6_Assignment\uart_queue\board" -I"C:\Users\Dell Latitude\Desktop\CUB\PES\1_assignment\6_Assignment\uart_queue\source" -I"C:\Users\Dell Latitude\Desktop\CUB\PES\1_assignment\6_Assignment\uart_queue" -I"C:\Users\Dell Latitude\Desktop\CUB\PES\1_assignment\6_Assignment\uart_queue\drivers" -I"C:\Users\Dell Latitude\Desktop\CUB\PES\1_assignment\6_Assignment\uart_queue\CMSIS" -I"C:\Users\Dell Latitude\Desktop\CUB\PES\1_assignment\6_Assignment\uart_queue\utilities" -I"C:\Users\Dell Latitude\Desktop\CUB\PES\1_assignment\6_Assignment\uart_queue\startup" -O0 -fno-common -g3 -Wall -Werror -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/LEDs.d ./source/LEDs.o ./source/PWM.d ./source/PWM.o ./source/UART.d ./source/UART.o ./source/accelerometer.d ./source/accelerometer.o ./source/adc.d ./source/adc.o ./source/command_processing.d ./source/command_processing.o ./source/i2c.d ./source/i2c.o ./source/llfifo.d ./source/llfifo.o ./source/main.d ./source/main.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/sysclock.d ./source/sysclock.o ./source/systick.d ./source/systick.o ./source/test_funcs.d ./source/test_funcs.o

.PHONY: clean-source

