################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../utilities/fsl_debug_console.c 

C_DEPS += \
./utilities/fsl_debug_console.d 

OBJS += \
./utilities/fsl_debug_console.o 


# Each subdirectory must supply rules for building sources it contributes
utilities/%.o: ../utilities/%.c utilities/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DCPU_MKL25Z128VLK4 -DCPU_MKL25Z128VLK4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=1 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DNDEBUG -D__REDLIB__ -D$(GEN_OPTS_FLAG) -I"C:\Users\Dell Latitude\Desktop\CUB\PES\1_assignment\6_Assignment\uart_queue\board" -I"C:\Users\Dell Latitude\Desktop\CUB\PES\1_assignment\6_Assignment\uart_queue\source" -I"C:\Users\Dell Latitude\Desktop\CUB\PES\1_assignment\6_Assignment\uart_queue" -I"C:\Users\Dell Latitude\Desktop\CUB\PES\1_assignment\6_Assignment\uart_queue\drivers" -I"C:\Users\Dell Latitude\Desktop\CUB\PES\1_assignment\6_Assignment\uart_queue\CMSIS" -I"C:\Users\Dell Latitude\Desktop\CUB\PES\1_assignment\6_Assignment\uart_queue\utilities" -I"C:\Users\Dell Latitude\Desktop\CUB\PES\1_assignment\6_Assignment\uart_queue\startup" -O0 -fno-common -g -Wall -Werror -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-utilities

clean-utilities:
	-$(RM) ./utilities/fsl_debug_console.d ./utilities/fsl_debug_console.o

.PHONY: clean-utilities

