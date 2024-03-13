################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers_SMW/Src/GPIO.c \
../Drivers_SMW/Src/I2C.c \
../Drivers_SMW/Src/SPI.c 

OBJS += \
./Drivers_SMW/Src/GPIO.o \
./Drivers_SMW/Src/I2C.o \
./Drivers_SMW/Src/SPI.o 

C_DEPS += \
./Drivers_SMW/Src/GPIO.d \
./Drivers_SMW/Src/I2C.d \
./Drivers_SMW/Src/SPI.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers_SMW/Src/%.o Drivers_SMW/Src/%.su Drivers_SMW/Src/%.cyclo: ../Drivers_SMW/Src/%.c Drivers_SMW/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32G0 -DSTM32G0B1RETx -c -I../Inc -I"C:/Users/10820302/Desktop/Latest/Bit_Banging/Drivers_SMW/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers_SMW-2f-Src

clean-Drivers_SMW-2f-Src:
	-$(RM) ./Drivers_SMW/Src/GPIO.cyclo ./Drivers_SMW/Src/GPIO.d ./Drivers_SMW/Src/GPIO.o ./Drivers_SMW/Src/GPIO.su ./Drivers_SMW/Src/I2C.cyclo ./Drivers_SMW/Src/I2C.d ./Drivers_SMW/Src/I2C.o ./Drivers_SMW/Src/I2C.su ./Drivers_SMW/Src/SPI.cyclo ./Drivers_SMW/Src/SPI.d ./Drivers_SMW/Src/SPI.o ./Drivers_SMW/Src/SPI.su

.PHONY: clean-Drivers_SMW-2f-Src

