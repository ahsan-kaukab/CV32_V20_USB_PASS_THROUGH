################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug/debug.c 

OBJS += \
./Debug/debug.o 

C_DEPS += \
./Debug/debug.d 


# Each subdirectory must supply rules for building sources it contributes
Debug/debug.o: /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug/debug.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU RISC-V Cross C Compiler'
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Layouts" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Layouts/colemak" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Layouts/dvorak" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Layouts/fnrs" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Layouts/jasf" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Layouts/jnrf" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Layouts/jnsf" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Layouts/kvikk" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Layouts/none" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Layouts/skarp" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/CONFIG" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/inc" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/Device/USBLIB/USB-Driver/src" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


