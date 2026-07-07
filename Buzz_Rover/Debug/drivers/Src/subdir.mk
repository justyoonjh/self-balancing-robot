################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/Src/buzz_gpio.c \
../drivers/Src/buzz_i2c.c \
../drivers/Src/buzz_rcc.c \
../drivers/Src/buzz_systick.c \
../drivers/Src/buzz_tim.c \
../drivers/Src/buzz_usart.c 

OBJS += \
./drivers/Src/buzz_gpio.o \
./drivers/Src/buzz_i2c.o \
./drivers/Src/buzz_rcc.o \
./drivers/Src/buzz_systick.o \
./drivers/Src/buzz_tim.o \
./drivers/Src/buzz_usart.o 

C_DEPS += \
./drivers/Src/buzz_gpio.d \
./drivers/Src/buzz_i2c.d \
./drivers/Src/buzz_rcc.d \
./drivers/Src/buzz_systick.d \
./drivers/Src/buzz_tim.d \
./drivers/Src/buzz_usart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/Src/%.o drivers/Src/%.su drivers/Src/%.cyclo: ../drivers/Src/%.c drivers/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -DNUCLEO_F446RE -c -I../Inc -I"/home/justjhst/바탕화면/self-balancing-robot/Buzz_Rover/bsp" -I"/home/justjhst/바탕화면/self-balancing-robot/Buzz_Rover/drivers/Inc" -I"/home/justjhst/바탕화면/self-balancing-robot/Buzz_Rover/app/Inc" -I"/home/justjhst/바탕화면/self-balancing-robot/Buzz_Rover/debug_app/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-drivers-2f-Src

clean-drivers-2f-Src:
	-$(RM) ./drivers/Src/buzz_gpio.cyclo ./drivers/Src/buzz_gpio.d ./drivers/Src/buzz_gpio.o ./drivers/Src/buzz_gpio.su ./drivers/Src/buzz_i2c.cyclo ./drivers/Src/buzz_i2c.d ./drivers/Src/buzz_i2c.o ./drivers/Src/buzz_i2c.su ./drivers/Src/buzz_rcc.cyclo ./drivers/Src/buzz_rcc.d ./drivers/Src/buzz_rcc.o ./drivers/Src/buzz_rcc.su ./drivers/Src/buzz_systick.cyclo ./drivers/Src/buzz_systick.d ./drivers/Src/buzz_systick.o ./drivers/Src/buzz_systick.su ./drivers/Src/buzz_tim.cyclo ./drivers/Src/buzz_tim.d ./drivers/Src/buzz_tim.o ./drivers/Src/buzz_tim.su ./drivers/Src/buzz_usart.cyclo ./drivers/Src/buzz_usart.d ./drivers/Src/buzz_usart.o ./drivers/Src/buzz_usart.su

.PHONY: clean-drivers-2f-Src

