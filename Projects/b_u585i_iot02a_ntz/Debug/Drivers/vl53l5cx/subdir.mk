################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/vl53l5cx/vl53l5cx.c 

OBJS += \
./Drivers/vl53l5cx/vl53l5cx.o 

C_DEPS += \
./Drivers/vl53l5cx/vl53l5cx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/vl53l5cx/%.o Drivers/vl53l5cx/%.su Drivers/vl53l5cx/%.cyclo: ../Drivers/vl53l5cx/%.c Drivers/vl53l5cx/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 '-DLFS_CONFIG=fs/lfs_config.h' -DUSE_HAL_DRIVER -DDEBUG -DSTM32 -DB_U585I_IOT02A -DSTM32U585AIIxQ -DSTM32U5 -DSTM32U585xx '-DMBEDTLS_CONFIG_FILE="mbedtls_config_ntz.h"' -c -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/pkcs11" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Projects/b_u585i_iot02a_ntz/Inc" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Projects/b_u585i_iot02a_ntz/Src" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Projects/b_u585i_iot02a_ntz/Src/ota_pal" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/FreeRTOS/corePKCS11/source/dependency/3rdparty/mbedtls_utils" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/ARM/littlefs" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Drivers/BSP/B-U585I-IOT02A" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Drivers/CMSIS/DSP/Include" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/STM32_AI_Library/Inc" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/AWS/OTA/source/include" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/AWS/OTA/source/portable/os" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/tinycbor/src" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/ARM/mbedtls/library" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/ARM/mbedtls/include" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/AWS/IoTDeviceDefender/source/include" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/AWS/IoTDeviceShadow/source/include" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/STM32_AI_AudioPreprocessing_Library/Inc" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Projects/Common/app/mqtt" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/FreeRTOS/backoffAlgorithm/source/include" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/FreeRTOS/coreJSON/source/include" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/FreeRTOS/coreMQTT-Agent/source/include" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/FreeRTOS/coreMQTT/source/include" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/FreeRTOS/coreMQTT/source/interface" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Drivers/CommonIO/include" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Drivers/CommonIO/gpio" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Projects/Common/boards" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Projects/Common/net/lwip_port/include" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/lwip/src/include" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Drivers/CMSIS/Core/Include" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Projects/Common/cli" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Projects/Common/dpu" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Drivers/CMSIS/Device/ST/STM32U5xx/Include" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Drivers/STM32U5xx_HAL/Inc" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/FreeRTOS/kernel/portable/GCC/ARM_CM33_NTZ/non_secure" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/FreeRTOS/kernel/include" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Projects/Common/include" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Projects/Common/config" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Projects/Common" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Projects/Common/kvstore" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Middleware/FreeRTOS/corePKCS11/source/include" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Projects/Common/app" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Projects/Common/app/Target" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Projects/b_u585i_iot02a_ntz/Drivers/vl53l5cx" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Projects/b_u585i_iot02a_ntz/Drivers/vl53l5cx/modules" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Projects/b_u585i_iot02a_ntz/Drivers/vl53l5cx/porting" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Projects/b_u585i_iot02a_ntz/Middlewares/ST/STM32_AI_Runtime/Inc" -I"C:/Users/bachirin/Desktop/AWS_gs/aws_poc_aed/Projects/b_u585i_iot02a_ntz/Middlewares/ST/STM32_AI_Runtime" -Og -ffunction-sections -fdata-sections -Wall -Wextra -Wmissing-include-dirs -Wswitch-default -Wconversion -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-vl53l5cx

clean-Drivers-2f-vl53l5cx:
	-$(RM) ./Drivers/vl53l5cx/vl53l5cx.cyclo ./Drivers/vl53l5cx/vl53l5cx.d ./Drivers/vl53l5cx/vl53l5cx.o ./Drivers/vl53l5cx/vl53l5cx.su

.PHONY: clean-Drivers-2f-vl53l5cx

