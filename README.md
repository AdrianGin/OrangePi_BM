# OrangePi_BM
A simple LED Blinker for the Orange Pi Zero H2+/H3


Update:

Adding project files.
Made for the Orange Pi Zero, this flashes the Red and Green LEDs
Use Eclipse to build

Use the following to build otherwise:
arm-none-eabi-gcc -marm -Os -fPIC  -g -Wa,-adhlns="main.o.lst" -MMD -MP -MF"main.d" -MT"main.o" -c -o "main.o" "../main.c"


arm-none-eabi-g++ -marm -Os -fPIC  -g -T "linker.ld" -nostartfiles -nodefaultlibs -nostdlib -Xlinker --gc-sections -Wl,-Map,"OrangePi_BM.map" -o "OrangePi_BM.elf"  ./main.o

A tricky part was getting the PORT L pins to work as it's located on the R_PIO module. This R_PIO clock comes from an undocumented:

CPUS_CLK_BASE_ADDR (0x01f01400)

CPUS_APB0_GATE     *(volatile unsigned int*)(CPUS_CLK_BASE_ADDR + 0x28)

R_PIO Gate is bit0 which must be set before the R_PIO/PORTL registers can be touched.





