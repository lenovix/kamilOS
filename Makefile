# ========== CONFIG ==========
CC = i686-linux-gnu-gcc
LD = i686-linux-gnu-ld
OBJCOPY = i686-linux-gnu-objcopy
AS = nasm
CFLAGS = -ffreestanding -m32 -nostdlib -fno-pie -fno-pic -O0
LDFLAGS = -m elf_i386
BUILD_DIR = build
SRC = kernel.c src/kernel/log.c src/drivers/screen.c


# ========== TARGETS ==========
all: $(BUILD_DIR)/os-image.bin

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile boot.asm → boot.bin
$(BUILD_DIR)/boot.bin: boot.asm | $(BUILD_DIR)
	$(AS) -f bin $< -o $@

# Compile .c files → .o
$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link kernel → ELF
$(BUILD_DIR)/kernel.elf: kernel.c src/kernel/log.c src/drivers/screen.c
	$(CC) $(CFLAGS) -T linker.ld -o $@ $^

# Convert ELF → binary
$(BUILD_DIR)/kernel.bin: $(BUILD_DIR)/kernel.elf
	$(OBJCOPY) -O binary $< $@

# Gabungkan boot dan kernel
$(BUILD_DIR)/os-image.bin: $(BUILD_DIR)/boot.bin $(BUILD_DIR)/kernel.bin
	dd if=$(BUILD_DIR)/boot.bin of=$@ bs=512 count=1 conv=notrunc
	dd if=$(BUILD_DIR)/kernel.bin of=$@ bs=512 seek=1 conv=notrunc

# Jalankan di QEMU
run: $(BUILD_DIR)/os-image.bin
	qemu-system-i386 -fda $(BUILD_DIR)/os-image.bin -boot a -net none

clean:
	rm -rf $(BUILD_DIR)