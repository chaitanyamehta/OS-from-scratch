; This is the kernel's entry point. Interrupts are disabled
; at this point:
[BITS 32]
global start
start:
	mov esp, _sys_stack     ; This points the stack to our new stack area
	jmp stublet

extern main
stublet:
	call main
	jmp $

; Definition of our BSS section. Right now, we'll use
; it just to store the stack. The stack grows downwards,
; so we declare the size of the data before declaring
; the identifier '_sys_stack'
SECTION .bss
	resb 8192					; This reserves 8KBytes of memory here
_sys_stack:
