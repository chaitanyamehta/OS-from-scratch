#include "interrupt.h"
#include "print.h"

int main(struct multiboot *mboot_ptr)
{
	idt_install();
	isr_install();
	irq_install();
	
	cls();
	print("Hello, world!\n");
	asm volatile ("int $0x3");
	
    return 0xDEADBEEF;
}
