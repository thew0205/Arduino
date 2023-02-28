COMPILPER = avr-gcc
MACH = atmega328p
COMPILPEROPTION = -mmcu=$(MACH)    -Wl,-Map=main.map -std=c++17 -Os
UPLOADER= "C:\Program Files (x86)\Arduino\hardware\tools\avr\bin\avrdude"
CONFIG = "C:\Program Files (x86)\Arduino\hardware\tools\avr\etc\avrdude.conf"
PORT= COM8
BAUD = 19200


main.elf : main.c
	$(COMPILPER) $(COMPILPEROPTION) $^ -o $@  -T link.ld
	avr-objdump -h -S $@

read: read
	$(UPLOADER) -C $(CONFIG) -p$(MACH) -v -b$(BAUD) -P$(PORT) -cstk500v1 -Uflash:r:$@.bin

uploadbyte:
	$(UPLOADER) -C $(CONFIG) -p$(MACH) -v -b$(BAUD) -P$(PORT) -cstk500v1 -U hbyte:w:0xdf:m

erase: 
	$(UPLOADER) -C $(CONFIG) -p$(MACH) -v -b$(BAUD) -P$(PORT) -cstk500v1 -e

main.hex: main.o
	avr-objcopy -O ihex -j .data -j.text main.o main.hex

uploaddata:  
	$(UPLOADER) -C $(CONFIG) -p$(MACH) -v -b$(BAUD) -P$(PORT) -cstk500v1 -Uflash:w:read.bin
dump:
	avr-objdump  main.elf -h -S


clean:
	del *.o read