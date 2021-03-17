[bits 16]

print:
	pusha
	mov ah, 0x0e
	print_loop:
		mov al, [bx]
		cmp al, 0x0
		je print_done
		int 0x10
		add bx, 0x1
		jmp print_loop
	print_done:
	popa
	ret
