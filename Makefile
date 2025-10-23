# ========== CONFIG ==========
CC = i686-linux-gnu-gcc
LD = i686-linux-gnu-ld
OBJCOPY = i686-linux-gnu-objcopy
AS = nasm
CFLAGS = -ffreestanding -m32 -nostdlib -fno-pie -fno-pic -O0
LDFLAGS = -m elf_i386
BUILD_DIR = build

# ========== TARGETS ==========
all: $(BUILD_DIR)/os-image.bin

# Pastikan folder build ada
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile boot.asm → boot.o
$(BUILD_DIR)/boot.o: boot.asm | $(BUILD_DIR)
	$(AS) -f bin $< -o $@

# Compile kernel.c → kernel.o
$(BUILD_DIR)/kernel.o: kernel.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link kernel.o → kernel.elf
$(BUILD_DIR)/kernel.elf: $(BUILD_DIR)/kernel.o linker.ld
	$(LD) $(LDFLAGS) -T linker.ld -o $@ $(BUILD_DIR)/kernel.o

# Convert ELF → binary
$(BUILD_DIR)/kernel.bin: $(BUILD_DIR)/kernel.elf
	$(OBJCOPY) -O binary $< $@

# Gabungkan boot dan kernel menjadi os-image.bin
$(BUILD_DIR)/os-image.bin: $(BUILD_DIR)/boot.o $(BUILD_DIR)/kernel.bin
	dd if=$(BUILD_DIR)/boot.o of=$@ bs=512 count=1 conv=notrunc
	dd if=$(BUILD_DIR)/kernel.bin of=$@ bs=512 seek=1 conv=notrunc

# Jalankan dengan QEMU
run: $(BUILD_DIR)/os-image.bin
	qemu-system-i386 -fda $(BUILD_DIR)/os-image.bin -boot a -net none

# Bersihkan semua hasil build
clean:
	rm -rf $(BUILD_DIR)
