################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/ch32v20x_it.c \
../User/ch32v20x_usbfs_device.c \
../User/main.c \
../User/system_ch32v20x.c \
../User/usb_desc.c 

OBJS += \
./User/ch32v20x_it.o \
./User/ch32v20x_usbfs_device.o \
./User/main.o \
./User/system_ch32v20x.o \
./User/usb_desc.o 

C_DEPS += \
./User/ch32v20x_it.d \
./User/ch32v20x_usbfs_device.d \
./User/main.d \
./User/system_ch32v20x.d \
./User/usb_desc.d 


# Each subdirectory must supply rules for building sources it contributes
User/%.o: ../User/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


