################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../app/Src/mpu6050.c 

OBJS += \
./app/Src/mpu6050.o 

C_DEPS += \
./app/Src/mpu6050.d 


# Each subdirectory must supply rules for building sources it contributes
app/Src/%.o app/Src/%.su app/Src/%.cyclo: ../app/Src/%.c app/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -I"/home/justjhst/바탕화면/self-balancing-robot/Buzz_Rover/bsp" -I"/home/justjhst/바탕화면/self-balancing-robot/Buzz_Rover/drivers/Inc" -I"/home/justjhst/바탕화면/self-balancing-robot/Buzz_Rover/app/Inc" -I"/home/justjhst/바탕화면/self-balancing-robot/Buzz_Rover/debug_app/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-app-2f-Src

clean-app-2f-Src:
	-$(RM) ./app/Src/mpu6050.cyclo ./app/Src/mpu6050.d ./app/Src/mpu6050.o ./app/Src/mpu6050.su

.PHONY: clean-app-2f-Src

