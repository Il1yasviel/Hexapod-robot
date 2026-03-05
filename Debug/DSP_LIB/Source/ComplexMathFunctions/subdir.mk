################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_f32.c \
../DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_q15.c \
../DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_q31.c \
../DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_f32.c \
../DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q15.c \
../DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q31.c \
../DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_f32.c \
../DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_q15.c \
../DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_q31.c \
../DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_f32.c \
../DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q15.c \
../DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q31.c \
../DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_f32.c \
../DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q15.c \
../DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q31.c \
../DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_f32.c \
../DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_q15.c \
../DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_q31.c 

OBJS += \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_f32.o \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_q15.o \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_q31.o \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_f32.o \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q15.o \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q31.o \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_f32.o \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_q15.o \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_q31.o \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_f32.o \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q15.o \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q31.o \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_f32.o \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q15.o \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q31.o \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_f32.o \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_q15.o \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_q31.o 

C_DEPS += \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_f32.d \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_q15.d \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_q31.d \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_f32.d \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q15.d \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q31.d \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_f32.d \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_q15.d \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_q31.d \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_f32.d \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q15.d \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q31.d \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_f32.d \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q15.d \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q31.d \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_f32.d \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_q15.d \
./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_q31.d 


# Each subdirectory must supply rules for building sources it contributes
DSP_LIB/Source/ComplexMathFunctions/%.o DSP_LIB/Source/ComplexMathFunctions/%.su DSP_LIB/Source/ComplexMathFunctions/%.cyclo: ../DSP_LIB/Source/ComplexMathFunctions/%.c DSP_LIB/Source/ComplexMathFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM3 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"D:/STM32 MCU Projects/test/Hexapod robot/DSP_LIB/Include" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-DSP_LIB-2f-Source-2f-ComplexMathFunctions

clean-DSP_LIB-2f-Source-2f-ComplexMathFunctions:
	-$(RM) ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_f32.cyclo ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_f32.d ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_f32.o ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_f32.su ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_q15.cyclo ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_q15.d ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_q15.o ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_q15.su ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_q31.cyclo ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_q31.d ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_q31.o ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_conj_q31.su ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_f32.cyclo ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_f32.d ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_f32.o ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_f32.su ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q15.cyclo ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q15.d ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q15.o ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q15.su ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q31.cyclo ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q31.d ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q31.o ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_dot_prod_q31.su ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_f32.cyclo ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_f32.d ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_f32.o ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_f32.su ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_q15.cyclo ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_q15.d ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_q15.o ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_q15.su ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_q31.cyclo ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_q31.d ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_q31.o ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_q31.su ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_f32.cyclo ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_f32.d ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_f32.o ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_f32.su ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q15.cyclo ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q15.d ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q15.o ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q15.su ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q31.cyclo ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q31.d ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q31.o ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mag_squared_q31.su ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_f32.cyclo ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_f32.d ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_f32.o ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_f32.su ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q15.cyclo ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q15.d ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q15.o ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q15.su ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q31.cyclo ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q31.d ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q31.o ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_cmplx_q31.su ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_f32.cyclo ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_f32.d ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_f32.o ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_f32.su ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_q15.cyclo ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_q15.d ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_q15.o ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_q15.su ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_q31.cyclo ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_q31.d ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_q31.o ./DSP_LIB/Source/ComplexMathFunctions/arm_cmplx_mult_real_q31.su

.PHONY: clean-DSP_LIB-2f-Source-2f-ComplexMathFunctions

