################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/debug_led/debug_led.c 

OBJS += \
./Core/debug_led/debug_led.o 

C_DEPS += \
./Core/debug_led/debug_led.d 


# Each subdirectory must supply rules for building sources it contributes
Core/debug_led/%.o Core/debug_led/%.su Core/debug_led/%.cyclo: ../Core/debug_led/%.c Core/debug_led/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -D__FPU_PRESENT=1U -DARM_MATH_CM4 -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"C:/Users/nemet/STM32CubeIDE/workspace_1.10.1/Echo_destroyer_richter/Core/STM32_AcousticEC_Library/Inc" -I"C:/Users/nemet/STM32CubeIDE/workspace_1.10.1/Echo_destroyer_richter/Core/debug_led" -I"C:/Users/nemet/STM32CubeIDE/workspace_1.10.1/Echo_destroyer_richter/Core/NVS" -I"C:/Users/nemet/STM32CubeIDE/workspace_1.10.1/Echo_destroyer_richter/Core/digitpoti" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/ARM/DSP/Inc -Og -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-debug_led

clean-Core-2f-debug_led:
	-$(RM) ./Core/debug_led/debug_led.cyclo ./Core/debug_led/debug_led.d ./Core/debug_led/debug_led.o ./Core/debug_led/debug_led.su

.PHONY: clean-Core-2f-debug_led

