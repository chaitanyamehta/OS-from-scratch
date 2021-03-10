#include "gdt.h"
#include "interrupt.h"
#include "print.h"
#include "keyboard.h"
#include "timer.h"

int main()
{
	init_gdt();
	init_idt();
	
	cls();
	init_timer();
	init_keyboard();
	asm volatile ("sti");
	
	return 0xDEADBEEF;
}
