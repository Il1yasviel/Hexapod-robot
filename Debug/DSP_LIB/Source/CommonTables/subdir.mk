################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DSP_LIB/Source/CommonTables/arm_common_tables.c \
../DSP_LIB/Source/CommonTables/arm_const_structs.c 

OBJS += \
./DSP_LIB/Source/CommonTables/arm_common_tables.o \
./DSP_LIB/Source/CommonTables/arm_const_structs.o 

C_DEPS += \
./DSP_LIB/Source/CommonTables/arm_common_tables.d \
./DSP_LIB/Source/CommonTables/arm_const_structs.d 


# Each subdirectory must supply rules for building sources it contributes
DSP_LIB/Source/CommonTables/%.o DSP_LIB/Source/CommonTables/%.su DSP_LIB/Source/CommonTables/%.cyclo: ../DSP_LIB/Source/CommonTables/%.c DSP_LIB/Source/CommonTables/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM3 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"D:/STM32 MCU Projects/test/Hexapod robot/DSP_LIB/Include" -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-DSP_LIB-2f-Source-2f-CommonTables

clean-DSP_LIB-2f-Source-2f-CommonTables:
	-$(RM) ./DSP_LIB/Source/CommonTables/arm_common_tables.cyclo ./DSP_LIB/Source/CommonTables/arm_common_tables.d ./DSP_LIB/Source/CommonTables/arm_common_tables.o ./DSP_LIB/Source/CommonTables/arm_common_tables.su ./DSP_LIB/Source/CommonTables/arm_const_structs.cyclo ./DSP_LIB/Source/CommonTables/arm_const_structs.d ./DSP_LIB/Source/CommonTables/arm_const_structs.o ./DSP_LIB/Source/CommonTables/arm_const_structs.su

.PHONY: clean-DSP_LIB-2f-Source-2f-CommonTables

