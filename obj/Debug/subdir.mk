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
	riscv-none-embed-gcc -march=rv32imac -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Debug" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User/USB_Host" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Core" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/User" -I"/home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/SRC/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


