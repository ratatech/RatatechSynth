################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/_write.c 

CC_SRCS += \
../src/ratatechSynth.cc 

OBJS += \
./src/_write.o \
./src/ratatechSynth.o 

C_DEPS += \
./src/_write.d 

CC_DEPS += \
./src/ratatechSynth.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_STDOUT -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -I"/home/rata/Projects/Eclipse Workspace/RatatechSynth/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"/home/rata/Projects/Eclipse Workspace/RatatechSynth/Drivers/CMSIS/Include" -I"/home/rata/Projects/Eclipse Workspace/RatatechSynth/Drivers/STM32F1xx_HAL_Driver/Inc" -I../include -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C++ Compiler'
	arm-none-eabi-g++ -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_STDOUT -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -I"/home/rata/Projects/Eclipse Workspace/RatatechSynth/Drivers/CMSIS/Device/ST/STM32F1xx/Include" -I"/home/rata/Projects/Eclipse Workspace/RatatechSynth/Drivers/CMSIS/Include" -I"/home/rata/Projects/Eclipse Workspace/RatatechSynth/Drivers/STM32F1xx_HAL_Driver/Inc" -std=gnu++11 -fabi-version=0 -fno-exceptions -fno-rtti -fno-use-cxa-atexit -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


