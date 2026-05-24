################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32f401ceux.s 

OBJS += \
./Core/Startup/startup_stm32f401ceux.o 

S_DEPS += \
./Core/Startup/startup_stm32f401ceux.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I../Core/Inc -I/home/potato/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Inc -I/home/potato/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I/home/potato/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Middlewares/Third_Party/FreeRTOS/Source/include -I/home/potato/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I/home/potato/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I/home/potato/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/CMSIS/Device/ST/STM32F4xx/Include -I/home/potato/STM32Cube/Repository/STM32Cube_FW_F4_V1.28.3/Drivers/CMSIS/Include -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32f401ceux.d ./Core/Startup/startup_stm32f401ceux.o

.PHONY: clean-Core-2f-Startup

