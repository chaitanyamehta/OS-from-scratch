; This is the kernel's entry point. Interrupts are disabled
; at this point:
[BITS 32]
global start
start:
	mov esp, _sys_stack     ; This points the stack to our new stack area
	jmp stublet

; This part MUST be 4byte aligned, so we solve that issue using 'ALIGN 4'
ALIGN 4
mboot:
	; Multiboot macros
	MBOOT_PAGE_ALIGN	equ 1<<0
	MBOOT_MEMORY_INFO	equ 1<<1
	MBOOT_AOUT_KLUDGE	equ 1<<16
	MBOOT_HEADER_MAGIC	equ 0x1BADB002
	MBOOT_HEADER_FLAGS	equ MBOOT_PAGE_ALIGN | MBOOT_MEMORY_INFO | MBOOT_AOUT_KLUDGE
    MBOOT_CHECKSUM	equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)
	EXTERN code, bss, end
	
	; This is the GRUB Multiboot header. A boot signature
	dd  MBOOT_HEADER_MAGIC		; GRUB will search for this value on each
								; 4-byte boundary in your kernel file
	dd  MBOOT_HEADER_FLAGS		; How GRUB should load your file / settings
	dd  MBOOT_CHECKSUM			; To ensure that the above values are correct
   
	dd  mboot					; Location of this descriptor
	dd  code					; Start of kernel '.text' (code) section.
	dd  bss						; End of kernel '.data' section.
	dd  end						; End of kernel.
	dd  start					; Kernel entry point (initial EIP).

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
