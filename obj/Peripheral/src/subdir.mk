################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_adc.c \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_bkp.c \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_can.c \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_crc.c \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_dbgmcu.c \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_dma.c \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_exti.c \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_flash.c \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_gpio.c \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_i2c.c \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_iwdg.c \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_misc.c \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_opa.c \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_pwr.c \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_rcc.c \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_rtc.c \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_spi.c \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_tim.c \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_usart.c \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_wwdg.c 

OBJS += \
./Peripheral/src/ch32v20x_adc.o \
./Peripheral/src/ch32v20x_bkp.o \
./Peripheral/src/ch32v20x_can.o \
./Peripheral/src/ch32v20x_crc.o \
./Peripheral/src/ch32v20x_dbgmcu.o \
./Peripheral/src/ch32v20x_dma.o \
./Peripheral/src/ch32v20x_exti.o \
./Peripheral/src/ch32v20x_flash.o \
./Peripheral/src/ch32v20x_gpio.o \
./Peripheral/src/ch32v20x_i2c.o \
./Peripheral/src/ch32v20x_iwdg.o \
./Peripheral/src/ch32v20x_misc.o \
./Peripheral/src/ch32v20x_opa.o \
./Peripheral/src/ch32v20x_pwr.o \
./Peripheral/src/ch32v20x_rcc.o \
./Peripheral/src/ch32v20x_rtc.o \
./Peripheral/src/ch32v20x_spi.o \
./Peripheral/src/ch32v20x_tim.o \
./Peripheral/src/ch32v20x_usart.o \
./Peripheral/src/ch32v20x_wwdg.o 

C_DEPS += \
./Peripheral/src/ch32v20x_adc.d \
./Peripheral/src/ch32v20x_bkp.d \
./Peripheral/src/ch32v20x_can.d \
./Peripheral/src/ch32v20x_crc.d \
./Peripheral/src/ch32v20x_dbgmcu.d \
./Peripheral/src/ch32v20x_dma.d \
./Peripheral/src/ch32v20x_exti.d \
./Peripheral/src/ch32v20x_flash.d \
./Peripheral/src/ch32v20x_gpio.d \
./Peripheral/src/ch32v20x_i2c.d \
./Peripheral/src/ch32v20x_iwdg.d \
./Peripheral/src/ch32v20x_misc.d \
./Peripheral/src/ch32v20x_opa.d \
./Peripheral/src/ch32v20x_pwr.d \
./Peripheral/src/ch32v20x_rcc.d \
./Peripheral/src/ch32v20x_rtc.d \
./Peripheral/src/ch32v20x_spi.d \
./Peripheral/src/ch32v20x_tim.d \
./Peripheral/src/ch32v20x_usart.d \
./Peripheral/src/ch32v20x_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
Peripheral/src/ch32v20x_adc.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_adc.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Peripheral/src/ch32v20x_bkp.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_bkp.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Peripheral/src/ch32v20x_can.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_can.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Peripheral/src/ch32v20x_crc.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_crc.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Peripheral/src/ch32v20x_dbgmcu.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_dbgmcu.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Peripheral/src/ch32v20x_dma.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_dma.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Peripheral/src/ch32v20x_exti.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_exti.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Peripheral/src/ch32v20x_flash.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_flash.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Peripheral/src/ch32v20x_gpio.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_gpio.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Peripheral/src/ch32v20x_i2c.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_i2c.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Peripheral/src/ch32v20x_iwdg.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_iwdg.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Peripheral/src/ch32v20x_misc.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_misc.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Peripheral/src/ch32v20x_opa.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_opa.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Peripheral/src/ch32v20x_pwr.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_pwr.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Peripheral/src/ch32v20x_rcc.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_rcc.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Peripheral/src/ch32v20x_rtc.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_rtc.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Peripheral/src/ch32v20x_spi.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_spi.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Peripheral/src/ch32v20x_tim.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_tim.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Peripheral/src/ch32v20x_usart.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_usart.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

Peripheral/src/ch32v20x_wwdg.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/src/ch32v20x_wwdg.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


