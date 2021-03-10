
; Loads the GDT defined in 'gdtp' into the processor.
; This is declared in C as 'extern void gdt_load();'
global gdt_load
extern gdtp
gdt_load:
	lgdt [gdtp]
	mov ax, 0x10			; 0x10 is the offset in the GDT to our data segment
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x08:.gdt_load_ret	; 0x08 is the offset to our code segment: Far jump!
.gdt_load_ret:
	ret						; Returns back to the C code!	
	
; Loads the IDT defined in 'idtp' into the processor.
; This is declared in C as 'extern void idt_load();'
global idt_load
extern idtp
idt_load:
	lidt [idtp]
	ret
