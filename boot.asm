[org 0x7C00]
[bits 16]

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    ; enable A20
    call enable_a20

    ; Load kernel (sector 2++) - MASIH DI 16-BIT!
    mov bx, 0x1000          ; segment 0x1000 → 0x10000 (load here)
    mov es, bx
    xor bx, bx              ; offset 0x0000

    mov ah, 0x02            ; function: read sectors
    mov al, 4               ; number of sectors (ganti sesuai ukuran kernel)
    mov ch, 0               ; cylinder
    mov cl, 2               ; sector (start from 2)
    mov dh, 0               ; head
    mov dl, 0               ; drive (floppy/HD)
    int 0x13
    jc disk_error           ; jika gagal

    ; setup GDT dan masuk protected mode
    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    ; Far jump ke mode 32-bit
    jmp CODE_SEG:init_pm

; ===================== GDT =========================
gdt_start:
gdt_null:
    dd 0x0
    dd 0x0

gdt_code:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10011010b
    db 11001111b
    db 0x00

gdt_data:
    dw 0xFFFF
    dw 0x0000
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10

; ==================== Mode 32-bit ====================
[bits 32]
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; lompat ke kernel di 0x10000
    jmp 0x10000

; ==================== Error & Utils ====================
disk_error:
    mov si, error_msg
    call print
hang:
    jmp hang

print:
    mov ah, 0x0E
.loop:
    lodsb
    or al, al
    jz .done
    int 0x10
    jmp .loop
.done:
    ret

enable_a20:
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

error_msg db "Disk read error!", 0

times 510 - ($ - $$) db 0
dw 0xAA55
