#Makefile for SWS ARMKern

CC=arm-linux-gnueabi-gcc
LD=arm-linux-gnueabi-ld
CFLAGS=-g -Wall -Wextra -std=gnu11 -ffreestanding -march=armv6 -msoft-float -fPIC -mapcs-frame
LDFLAGS=-N -Ttext=0x10000
HWDEF=versatilepb #The set of hardware quirks to use.

#Paths
VPATH=src/:obj/
CINC=-Isrc/include/

kernel.elf: bootstrap.o kernel.o serialio.o context_switch.o syscall.o tasks.o memmgt.o

.PHONY: clean test

clean:
	rm -f obj/*.o elf/*.elf

test:
	qemu-system-arm -M versatilepb -cpu arm1176 -nographic -kernel elf/kernel.elf

.SUFFIXES: .s .c .o .elf

.o.elf:
	cd obj/ && \
	$(LD) $(LDFLAGS) -o ../elf/$@ $^

.c.o:
	$(CC) $(CFLAGS) $(CINC) -DHWCLASS=$(HWDEF) -o obj/$@ -c $^

.s.o:
	$(CC) $(CFLAGS) $(CINC) -DHWCLASS=$(HWDEF) -o obj/$@ -c $^
