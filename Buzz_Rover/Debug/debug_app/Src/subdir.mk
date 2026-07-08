################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../debug_app/Src/i2c_scanner.c \
../debug_app/Src/tim_profiling.c 

OBJS += \
./debug_app/Src/i2c_scanner.o \
./debug_app/Src/tim_profiling.o 

C_DEPS += \
./debug_app/Src/i2c_scanner.d \
./debug_app/Src/tim_profiling.d 


# Each subdirectory must supply rules for building sources it contributes
debug_app/Src/%.o debug_app/Src/%.su debug_app/Src/%.cyclo: ../debug_app/Src/%.c debug_app/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -I"/home/justjhst/바탕화면/self-balancing-robot/Buzz_Rover/bsp" -I"/home/justjhst/바탕화면/self-balancing-robot/Buzz_Rover/drivers/Inc" -I"/home/justjhst/바탕화면/self-balancing-robot/Buzz_Rover/app/Inc" -I"/home/justjhst/바탕화면/self-balancing-robot/Buzz_Rover/debug_app/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-debug_app-2f-Src

clean-debug_app-2f-Src:
	-$(RM) ./debug_app/Src/i2c_scanner.cyclo ./debug_app/Src/i2c_scanner.d ./debug_app/Src/i2c_scanner.o ./debug_app/Src/i2c_scanner.su ./debug_app/Src/tim_profiling.cyclo ./debug_app/Src/tim_profiling.d ./debug_app/Src/tim_profiling.o ./debug_app/Src/tim_profiling.su

.PHONY: clean-debug_app-2f-Src

