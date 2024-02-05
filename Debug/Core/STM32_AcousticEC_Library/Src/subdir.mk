################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/STM32_AcousticEC_Library/Src/Echo_library.c \
../Core/STM32_AcousticEC_Library/Src/acousticEC.c \
../Core/STM32_AcousticEC_Library/Src/echo.c \
../Core/STM32_AcousticEC_Library/Src/filterbank.c \
../Core/STM32_AcousticEC_Library/Src/preprocess.c \
../Core/STM32_AcousticEC_Library/Src/smallft.c 

OBJS += \
./Core/STM32_AcousticEC_Library/Src/Echo_library.o \
./Core/STM32_AcousticEC_Library/Src/acousticEC.o \
./Core/STM32_AcousticEC_Library/Src/echo.o \
./Core/STM32_AcousticEC_Library/Src/filterbank.o \
./Core/STM32_AcousticEC_Library/Src/preprocess.o \
./Core/STM32_AcousticEC_Library/Src/smallft.o 

C_DEPS += \
./Core/STM32_AcousticEC_Library/Src/Echo_library.d \
./Core/STM32_AcousticEC_Library/Src/acousticEC.d \
./Core/STM32_AcousticEC_Library/Src/echo.d \
./Core/STM32_AcousticEC_Library/Src/filterbank.d \
./Core/STM32_AcousticEC_Library/Src/preprocess.d \
./Core/STM32_AcousticEC_Library/Src/smallft.d 


# Each subdirectory must supply rules for building sources it contributes
Core/STM32_AcousticEC_Library/Src/%.o Core/STM32_AcousticEC_Library/Src/%.su Core/STM32_AcousticEC_Library/Src/%.cyclo: ../Core/STM32_AcousticEC_Library/Src/%.c Core/STM32_AcousticEC_Library/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -D__FPU_PRESENT=1U -DARM_MATH_CM4 -DUSE_HAL_DRIVER -DSTM32F446xx -c -I"C:/Users/nemet/STM32CubeIDE/workspace_1.10.1/Echo_destroyer_richter/Core/STM32_AcousticEC_Library/Inc" -I"C:/Users/nemet/STM32CubeIDE/workspace_1.10.1/Echo_destroyer_richter/Core/digitpoti" -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/ST/ARM/DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-STM32_AcousticEC_Library-2f-Src

clean-Core-2f-STM32_AcousticEC_Library-2f-Src:
	-$(RM) ./Core/STM32_AcousticEC_Library/Src/Echo_library.cyclo ./Core/STM32_AcousticEC_Library/Src/Echo_library.d ./Core/STM32_AcousticEC_Library/Src/Echo_library.o ./Core/STM32_AcousticEC_Library/Src/Echo_library.su ./Core/STM32_AcousticEC_Library/Src/acousticEC.cyclo ./Core/STM32_AcousticEC_Library/Src/acousticEC.d ./Core/STM32_AcousticEC_Library/Src/acousticEC.o ./Core/STM32_AcousticEC_Library/Src/acousticEC.su ./Core/STM32_AcousticEC_Library/Src/echo.cyclo ./Core/STM32_AcousticEC_Library/Src/echo.d ./Core/STM32_AcousticEC_Library/Src/echo.o ./Core/STM32_AcousticEC_Library/Src/echo.su ./Core/STM32_AcousticEC_Library/Src/filterbank.cyclo ./Core/STM32_AcousticEC_Library/Src/filterbank.d ./Core/STM32_AcousticEC_Library/Src/filterbank.o ./Core/STM32_AcousticEC_Library/Src/filterbank.su ./Core/STM32_AcousticEC_Library/Src/preprocess.cyclo ./Core/STM32_AcousticEC_Library/Src/preprocess.d ./Core/STM32_AcousticEC_Library/Src/preprocess.o ./Core/STM32_AcousticEC_Library/Src/preprocess.su ./Core/STM32_AcousticEC_Library/Src/smallft.cyclo ./Core/STM32_AcousticEC_Library/Src/smallft.d ./Core/STM32_AcousticEC_Library/Src/smallft.o ./Core/STM32_AcousticEC_Library/Src/smallft.su

.PHONY: clean-Core-2f-STM32_AcousticEC_Library-2f-Src

