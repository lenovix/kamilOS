# kamilOS v0.0.1

**kamilOS** adalah sistem operasi minimal buatan sendiri sebagai latihan eksplorasi sistem operasi dari nol menggunakan bahasa Assembly dan C, serta compiler cross-platform `i386-elf-gcc`.

Versi 0.0.1 adalah rilis awal yang berfokus pada:
- Bootloader buatan sendiri (512-byte MBR)
- Kernel 32-bit sederhana yang ditulis dalam C
- Dapat dijalankan di emulator QEMU
- Struktur awal file dan toolchain


## 📁 Struktur Proyek
```
kamilOS/
├── boot.asm # Bootloader 16-bit (MBR)
├── kernel.c # Kernel C sederhana
├── kernel.ld # Linker script untuk ELF ke binary
├── Makefile # Otomatisasi build
├── os-image.bin # Image akhir yang siap dijalankan QEMU
├── README.md # Dokumentasi ini
```
---

## 🛠 Persyaratan

Sebelum mem-build, pastikan kamu sudah install:

- `i386-elf-gcc` & `i386-elf-ld` (cross compiler)
- `nasm`
- `qemu`
- `make`

### Install Cross Compiler (contoh ringkas)
```bash
export PREFIX="$HOME/cross"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"
```
Kamu bisa ikuti panduan osdev.org - GCC Cross Compiler untuk setup lengkapnya.

---
## ⚙️ Build
Jalankan perintah berikut untuk membangun image OS:

```bash
make
```
Jika berhasil, kamu akan mendapatkan file os-image.bin.

---
## 🚀 Menjalankan kamilOS
Gunakan QEMU untuk menguji OS ini:

```bash
qemu-system-i386 -fda os-image.bin -boot a
```
Kamu seharusnya melihat hasil dari kernel atau debug awal dari bootloader.

## 🧪 Status Fitur v0.0.1

| Fitur |  Status  |
|:-----|:--------:|
| Bootloader 16-bit   | **✅ Selesai** |
| Switch ke 32-bit protected mode   | **✅ Selesai** |
| Kernel Hello World   | **✅ Selesai** |
| Output teks ke layar   | **⚠️ Minimal** |
| File system / input keyboard   | **❌ Belum** |
| Memory management   | **❌ Belum** |


## 🧭 Tujuan Selanjutnya
- Menambahkan dukungan keyboard input
- Sistem output teks yang lebih baik (print string, newline, dll)
- Setup stack dan interrupt descriptor table (IDT)
- Paging dan manajemen memori dasar