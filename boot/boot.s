[org 0x7c00]

mov [BOOT_DRIVE], dl		; Bios stores boot drive in dl, remember it for future use

mov bp, STACK_16
mov sp, bp

mov bx, MSG_REAL_MODE
call print
call load_kernel
call switch_to_pm			; switch to protected mode

load_kernel:
	mov bx, MSG_LOAD_KERN
	call print
	
	mov bx, KERN_OFFSET
	mov dh, 30				; no of sectors to be read
	mov dl, [BOOT_DRIVE]	; restore dl
	call disk_load
	ret

[bits 32]
begin_pm:
	call KERN_OFFSET
	jmp $					; jump to current line indefinitely

%include "print.s"
%include "disk.s"
%include "gdt.s"

BOOT_DRIVE:
	db 0

MSG_REAL_MODE:
	db "16 bit real mode ", 0

MSG_LOAD_KERN:
	db "Loading Kernel ", 0

times 510-($-$$) db 0	; Fill remaining bytes with 0
dw	0xaa55				; Magic number, so bios knows this is a boot sector


STACK_16 equ 0x9000
KERN_OFFSET equ 0x1000
