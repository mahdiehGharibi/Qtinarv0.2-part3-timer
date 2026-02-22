# Compiler and flags
CC = gcc
CFLAGS = -m32 -ffreestanding -fno-pie -fno-stack-protector -O0 -Wall -Wextra
ASFLAGS = -m32 -c
LD = ld
LDFLAGS = -m elf_i386 -T linker.ld

SRC = src
CPU = $(SRC)/cpu
DRIVERS = $(SRC)/drivers
KERNEL = $(SRC)/kernel

OBJS = \
    $(CPU)/idt.o \
    $(CPU)/isr.o \
    $(CPU)/irq.o \
    $(CPU)/pic.o \
    $(CPU)/ports.o \
    $(CPU)/interrupts.o \
    $(DRIVERS)/screen.o \
    $(DRIVERS)/keyboard.o \
    $(KERNEL)/kernel.o

all: kernel.bin os.iso

%.o: %.c
[TAB]$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
[TAB]$(CC) $(ASFLAGS) $< -o $@

kernel.bin: $(OBJS)
[TAB]$(LD) $(LDFLAGS) -o kernel.bin $(OBJS)

os.iso: kernel.bin
[TAB]mkdir -p iso/boot/grub
[TAB]cp kernel.bin iso/boot/kernel.bin
[TAB]echo 'set timeout=0' > iso/boot/grub/grub.cfg
[TAB]echo 'set default=0' >> iso/boot/grub/grub.cfg
[TAB]echo 'menuentry "QtinarOS" { multiboot /boot/kernel.bin }' >> iso/boot/grub/grub.cfg
[TAB]grub-mkrescue -o os.iso iso

clean:
[TAB]rm -f $(CPU)/*.o $(DRIVERS)/*.o $(KERNEL)/*.o kernel.bin os.iso
[TAB]rm -rf iso

run: os.iso
[TAB]qemu-system-i386 -cdrom os.iso
