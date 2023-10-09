################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ECUAL/SERVO/SERVO.c \
../ECUAL/SERVO/SERVO_cfg.c 

OBJS += \
./ECUAL/SERVO/SERVO.o \
./ECUAL/SERVO/SERVO_cfg.o 

C_DEPS += \
./ECUAL/SERVO/SERVO.d \
./ECUAL/SERVO/SERVO_cfg.d 


# Each subdirectory must supply rules for building sources it contributes
ECUAL/SERVO/SERVO.o: ../ECUAL/SERVO/SERVO.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ECUAL/SERVO/SERVO.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
ECUAL/SERVO/SERVO_cfg.o: ../ECUAL/SERVO/SERVO_cfg.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F103xB -DDEBUG -c -I../Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"ECUAL/SERVO/SERVO_cfg.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

