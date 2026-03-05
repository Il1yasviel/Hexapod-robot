################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DSP_LIB/Source/FastMathFunctions/arm_cos_f32.c \
../DSP_LIB/Source/FastMathFunctions/arm_cos_q15.c \
../DSP_LIB/Source/FastMathFunctions/arm_cos_q31.c \
../DSP_LIB/Source/FastMathFunctions/arm_sin_f32.c \
../DSP_LIB/Source/FastMathFunctions/arm_sin_q15.c \
../DSP_LIB/Source/FastMathFunctions/arm_sin_q31.c \
../DSP_LIB/Source/FastMathFunctions/arm_sqrt_q15.c \
../DSP_LIB/Source/FastMathFunctions/arm_sqrt_q31.c 

OBJS += \
./DSP_LIB/Source/FastMathFunctions/arm_cos_f32.o \
./DSP_LIB/Source/FastMathFunctions/arm_cos_q15.o \
./DSP_LIB/Source/FastMathFunctions/arm_cos_q31.o \
./DSP_LIB/Source/FastMathFunctions/arm_sin_f32.o \
./DSP_LIB/Source/FastMathFunctions/arm_sin_q15.o \
./DSP_LIB/Source/FastMathFunctions/arm_sin_q31.o \
./DSP_LIB/Source/FastMathFunctions/arm_sqrt_q15.o \
./DSP_LIB/Source/FastMathFunctions/arm_sqrt_q31.o 

C_DEPS += \
./DSP_LIB/Source/FastMathFunctions/arm_cos_f32.d \
./DSP_LIB/Source/FastMathFunctions/arm_cos_q15.d \
./DSP_LIB/Source/FastMathFunctions/arm_cos_q31.d \
./DSP_LIB/Source/FastMathFunctions/arm_sin_f32.d \
./DSP_LIB/Source/FastMathFunctions/arm_sin_q15.d \
./DSP_LIB/Source/FastMathFunctions/arm_sin_q31.d \
./DSP_LIB/Source/FastMathFunctions/arm_sqrt_q15.d \
./DSP_LIB/Source/FastMathFunctions/arm_sqrt_q31.d 


# Each subdirectory must supply rules for building sources it contributes
DSP_LIB/Source/FastMathFunctions/%.o DSP_LIB/Source/FastMathFunctions/%.su DSP_LIB/Source/FastMathFunctions/%.cyclo: ../DSP_LIB/Source/FastMathFunctions/%.c DSP_LIB/Source/FastMathFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM3 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"D:/STM32 MCU Projects/test/Hexapod robot/DSP_LIB/Include" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-DSP_LIB-2f-Source-2f-FastMathFunctions

clean-DSP_LIB-2f-Source-2f-FastMathFunctions:
	-$(RM) ./DSP_LIB/Source/FastMathFunctions/arm_cos_f32.cyclo ./DSP_LIB/Source/FastMathFunctions/arm_cos_f32.d ./DSP_LIB/Source/FastMathFunctions/arm_cos_f32.o ./DSP_LIB/Source/FastMathFunctions/arm_cos_f32.su ./DSP_LIB/Source/FastMathFunctions/arm_cos_q15.cyclo ./DSP_LIB/Source/FastMathFunctions/arm_cos_q15.d ./DSP_LIB/Source/FastMathFunctions/arm_cos_q15.o ./DSP_LIB/Source/FastMathFunctions/arm_cos_q15.su ./DSP_LIB/Source/FastMathFunctions/arm_cos_q31.cyclo ./DSP_LIB/Source/FastMathFunctions/arm_cos_q31.d ./DSP_LIB/Source/FastMathFunctions/arm_cos_q31.o ./DSP_LIB/Source/FastMathFunctions/arm_cos_q31.su ./DSP_LIB/Source/FastMathFunctions/arm_sin_f32.cyclo ./DSP_LIB/Source/FastMathFunctions/arm_sin_f32.d ./DSP_LIB/Source/FastMathFunctions/arm_sin_f32.o ./DSP_LIB/Source/FastMathFunctions/arm_sin_f32.su ./DSP_LIB/Source/FastMathFunctions/arm_sin_q15.cyclo ./DSP_LIB/Source/FastMathFunctions/arm_sin_q15.d ./DSP_LIB/Source/FastMathFunctions/arm_sin_q15.o ./DSP_LIB/Source/FastMathFunctions/arm_sin_q15.su ./DSP_LIB/Source/FastMathFunctions/arm_sin_q31.cyclo ./DSP_LIB/Source/FastMathFunctions/arm_sin_q31.d ./DSP_LIB/Source/FastMathFunctions/arm_sin_q31.o ./DSP_LIB/Source/FastMathFunctions/arm_sin_q31.su ./DSP_LIB/Source/FastMathFunctions/arm_sqrt_q15.cyclo ./DSP_LIB/Source/FastMathFunctions/arm_sqrt_q15.d ./DSP_LIB/Source/FastMathFunctions/arm_sqrt_q15.o ./DSP_LIB/Source/FastMathFunctions/arm_sqrt_q15.su ./DSP_LIB/Source/FastMathFunctions/arm_sqrt_q31.cyclo ./DSP_LIB/Source/FastMathFunctions/arm_sqrt_q31.d ./DSP_LIB/Source/FastMathFunctions/arm_sqrt_q31.o ./DSP_LIB/Source/FastMathFunctions/arm_sqrt_q31.su

.PHONY: clean-DSP_LIB-2f-Source-2f-FastMathFunctions

