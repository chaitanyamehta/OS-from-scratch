#include "idt.h"
#include "print.h"

int main(struct multiboot *mboot_ptr)
{
	idt_install();
	
	cls();
	print("Hello, world!\n");
	asm volatile ("int $0x3");
    return 0xDEADBEEF;
}
