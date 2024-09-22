################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../User/USB_Host/app_km.c \
../User/USB_Host/ch32v20x_usbfs_host.c \
../User/USB_Host/usb_host_hid.c \
../User/USB_Host/usb_host_hub.c 

OBJS += \
./User/USB_Host/app_km.o \
./User/USB_Host/ch32v20x_usbfs_host.o \
./User/USB_Host/usb_host_hid.o \
./User/USB_Host/usb_host_hub.o 

C_DEPS += \
./User/USB_Host/app_km.d \
./User/USB_Host/ch32v20x_usbfs_host.d \
./User/USB_Host/usb_host_hid.d \
./User/USB_Host/usb_host_hub.d 


# Each subdirectory must supply rules for building sources it contributes
User/USB_Host/%.o: ../User/USB_Host/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


