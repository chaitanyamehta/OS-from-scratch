[bits 16]

disk_load:
	push dx
	mov ah, 0x2		; BIOS read section function
	mov al, dh		; Read dh sectors
	mov ch, 0x0		; select 0th cylinder
	mov dh, 0x0		; select head 0
	mov cl, 0x2		; select sector 2
	
	int 0x13
	jc disk_error
	
	pop dx
	cmp al, dh		; compare number of sectors read
	jne disk_error
	ret
	
disk_error:
	mov bx, DISK_ERROR_MSG
	call print
	jmp $
	
DISK_ERROR_MSG:
	db "Disk read error! ", 0

