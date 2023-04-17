################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/custom_c/CRC_16.c \
../Core/Src/custom_c/Callback.c \
../Core/Src/custom_c/Driver_Init.c \
../Core/Src/custom_c/Encoder.c \
../Core/Src/custom_c/KEY.c \
../Core/Src/custom_c/Motor.c \
../Core/Src/custom_c/My_UART.c \
../Core/Src/custom_c/PID.c \
../Core/Src/custom_c/Rpi.c \
../Core/Src/custom_c/Run_Function.c \
../Core/Src/custom_c/Servo.c \
../Core/Src/custom_c/fifo_test.c 

OBJS += \
./Core/Src/custom_c/CRC_16.o \
./Core/Src/custom_c/Callback.o \
./Core/Src/custom_c/Driver_Init.o \
./Core/Src/custom_c/Encoder.o \
./Core/Src/custom_c/KEY.o \
./Core/Src/custom_c/Motor.o \
./Core/Src/custom_c/My_UART.o \
./Core/Src/custom_c/PID.o \
./Core/Src/custom_c/Rpi.o \
./Core/Src/custom_c/Run_Function.o \
./Core/Src/custom_c/Servo.o \
./Core/Src/custom_c/fifo_test.o 

C_DEPS += \
./Core/Src/custom_c/CRC_16.d \
./Core/Src/custom_c/Callback.d \
./Core/Src/custom_c/Driver_Init.d \
./Core/Src/custom_c/Encoder.d \
./Core/Src/custom_c/KEY.d \
./Core/Src/custom_c/Motor.d \
./Core/Src/custom_c/My_UART.d \
./Core/Src/custom_c/PID.d \
./Core/Src/custom_c/Rpi.d \
./Core/Src/custom_c/Run_Function.d \
./Core/Src/custom_c/Servo.d \
./Core/Src/custom_c/fifo_test.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/custom_c/%.o Core/Src/custom_c/%.su: ../Core/Src/custom_c/%.c Core/Src/custom_c/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-custom_c

clean-Core-2f-Src-2f-custom_c:
	-$(RM) ./Core/Src/custom_c/CRC_16.d ./Core/Src/custom_c/CRC_16.o ./Core/Src/custom_c/CRC_16.su ./Core/Src/custom_c/Callback.d ./Core/Src/custom_c/Callback.o ./Core/Src/custom_c/Callback.su ./Core/Src/custom_c/Driver_Init.d ./Core/Src/custom_c/Driver_Init.o ./Core/Src/custom_c/Driver_Init.su ./Core/Src/custom_c/Encoder.d ./Core/Src/custom_c/Encoder.o ./Core/Src/custom_c/Encoder.su ./Core/Src/custom_c/KEY.d ./Core/Src/custom_c/KEY.o ./Core/Src/custom_c/KEY.su ./Core/Src/custom_c/Motor.d ./Core/Src/custom_c/Motor.o ./Core/Src/custom_c/Motor.su ./Core/Src/custom_c/My_UART.d ./Core/Src/custom_c/My_UART.o ./Core/Src/custom_c/My_UART.su ./Core/Src/custom_c/PID.d ./Core/Src/custom_c/PID.o ./Core/Src/custom_c/PID.su ./Core/Src/custom_c/Rpi.d ./Core/Src/custom_c/Rpi.o ./Core/Src/custom_c/Rpi.su ./Core/Src/custom_c/Run_Function.d ./Core/Src/custom_c/Run_Function.o ./Core/Src/custom_c/Run_Function.su ./Core/Src/custom_c/Servo.d ./Core/Src/custom_c/Servo.o ./Core/Src/custom_c/Servo.su ./Core/Src/custom_c/fifo_test.d ./Core/Src/custom_c/fifo_test.o ./Core/Src/custom_c/fifo_test.su

.PHONY: clean-Core-2f-Src-2f-custom_c

