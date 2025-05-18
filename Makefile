all: os-image

boot.o: boot.asm
	nasm -f bin boot.asm -o boot.o

kernel.o: kernel.c
	i386-elf-gcc -ffreestanding -m32 -nostdlib -fno-pie -fno-pic -O0 -c kernel.c -o kernel.o

kernel.elf: kernel.o linker.ld
	i386-elf-ld -m elf_i386 -T linker.ld -o kernel.elf kernel.o

kernel.bin: kernel.elf
	i386-elf-objcopy -O binary kernel.elf kernel.bin

os-image: boot.o kernel.bin
	dd if=boot.o of=os-image.bin bs=512 count=1 conv=notrunc
	dd if=kernel.bin of=os-image.bin bs=512 seek=1 conv=notrunc

run: os-image
	# qemu-system-i386 -drive format=raw,if=floppy,file=os-image.bin
	qemu-system-i386 -fda os-image.bin -boot a -net none

clean:
	rm -f *.o *.bin
