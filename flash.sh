rm -rf yourfile.bin
wch-isp list
#wch-isp -d 51-38-7e-26-3b-38-0a-97 erase

riscv-none-embed-objcopy -O binary /home/flinux/Desktop/nanoCH32V203-master_cp/doc/EVT/EXAM/USB/USBFS/my_code_HOST_KM/obj/HOST_KM.elf yourfile.bin 

wch-isp -D -p flash yourfile.bin
wch-isp -D -p verify yourfile.bin
