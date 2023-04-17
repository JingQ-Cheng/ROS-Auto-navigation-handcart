################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Inc/FFT/PID_stm32.s \
../Core/Inc/FFT/cr4_fft_1024_stm32.s \
../Core/Inc/FFT/cr4_fft_256_stm32.s \
../Core/Inc/FFT/cr4_fft_64_stm32.s \
../Core/Inc/FFT/fir_stm32.s \
../Core/Inc/FFT/iirarma_stm32.s 

OBJS += \
./Core/Inc/FFT/PID_stm32.o \
./Core/Inc/FFT/cr4_fft_1024_stm32.o \
./Core/Inc/FFT/cr4_fft_256_stm32.o \
./Core/Inc/FFT/cr4_fft_64_stm32.o \
./Core/Inc/FFT/fir_stm32.o \
./Core/Inc/FFT/iirarma_stm32.o 

S_DEPS += \
./Core/Inc/FFT/PID_stm32.d \
./Core/Inc/FFT/cr4_fft_1024_stm32.d \
./Core/Inc/FFT/cr4_fft_256_stm32.d \
./Core/Inc/FFT/cr4_fft_64_stm32.d \
./Core/Inc/FFT/fir_stm32.d \
./Core/Inc/FFT/iirarma_stm32.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/FFT/%.o: ../Core/Inc/FFT/%.s Core/Inc/FFT/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Inc-2f-FFT

clean-Core-2f-Inc-2f-FFT:
	-$(RM) ./Core/Inc/FFT/PID_stm32.d ./Core/Inc/FFT/PID_stm32.o ./Core/Inc/FFT/cr4_fft_1024_stm32.d ./Core/Inc/FFT/cr4_fft_1024_stm32.o ./Core/Inc/FFT/cr4_fft_256_stm32.d ./Core/Inc/FFT/cr4_fft_256_stm32.o ./Core/Inc/FFT/cr4_fft_64_stm32.d ./Core/Inc/FFT/cr4_fft_64_stm32.o ./Core/Inc/FFT/fir_stm32.d ./Core/Inc/FFT/fir_stm32.o ./Core/Inc/FFT/iirarma_stm32.d ./Core/Inc/FFT/iirarma_stm32.o

.PHONY: clean-Core-2f-Inc-2f-FFT

