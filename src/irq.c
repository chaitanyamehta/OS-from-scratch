#include "interrupt.h"
#include "io.h"
#include "stdint.h"
#include "stdbool.h"

// These extern directives let us access the addresses of our ASM irq handlers.
extern void irq0 ();
extern void irq1 ();
extern void irq2 ();
extern void irq3 ();
extern void irq4 ();
extern void irq5 ();
extern void irq6 ();
extern void irq7 ();
extern void irq8 ();
extern void irq9 ();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void *irq_routines[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

/* This installs a custom IRQ handler for the given IRQ */
void irq_install_handler(int irq, void (*handler)(void))
{
	irq_routines[irq] = handler;
}

/* This clears the handler for a given IRQ */
void irq_uninstall_handler(int irq)
{
	irq_routines[irq] = 0;
}

/* Normally, IRQs 0 to 7 are mapped to entries 8 to 15. This
*  is a problem in protected mode, because IDT entry 8 is a
*  Double Fault! Without remapping, every time IRQ0 fires,
*  you get a Double Fault Exception, which is NOT actually
*  what's happening. We send commands to the Programmable
*  Interrupt Controller (PICs - also called the 8259's) in
*  order to make IRQ0 to 15 be remapped to IDT entries 32 to
*  47 */
void irq_remap()
{
	outb(0x20, 0x11);
	outb(0xA0, 0x11);
	  
	outb(0x21, 0x20);
	outb(0xA1, 0x28);
	
	outb(0x21, 0x04);
	outb(0xA1, 0x02);
	
	outb(0x21, 0x01);
	outb(0xA1, 0x01);
	
	outb(0x21, 0x0);
	outb(0xA1, 0x0);
}

void init_irq()
{
	irq_remap();

	idt_set_gate(32, (uint32_t)irq0 , 0x08, 0x8E);
	idt_set_gate(33, (uint32_t)irq1 , 0x08, 0x8E);
	idt_set_gate(34, (uint32_t)irq2 , 0x08, 0x8E);
	idt_set_gate(35, (uint32_t)irq3 , 0x08, 0x8E);
	idt_set_gate(36, (uint32_t)irq4 , 0x08, 0x8E);
	idt_set_gate(37, (uint32_t)irq5 , 0x08, 0x8E);
	idt_set_gate(38, (uint32_t)irq6 , 0x08, 0x8E);
	idt_set_gate(39, (uint32_t)irq7 , 0x08, 0x8E);
	idt_set_gate(40, (uint32_t)irq8 , 0x08, 0x8E);
	idt_set_gate(41, (uint32_t)irq9 , 0x08, 0x8E);
	idt_set_gate(42, (uint32_t)irq10, 0x08, 0x8E);
	idt_set_gate(43, (uint32_t)irq11, 0x08, 0x8E);
	idt_set_gate(44, (uint32_t)irq12, 0x08, 0x8E);
	idt_set_gate(45, (uint32_t)irq13, 0x08, 0x8E);
	idt_set_gate(46, (uint32_t)irq14, 0x08, 0x8E);
	idt_set_gate(47, (uint32_t)irq15, 0x08, 0x8E);
}

// This gets called from our ASM interrupt handler stub.
void irq_handler(struct registers *regs)
{
	void (*handler)(void);
	handler = irq_routines[regs->int_no - 32]; 
	if(handler != 0)
	{
		handler();
	}
	
	if(regs->int_no >= 40)
	{
		// Send reset signal to secondary PIC
		outb(0xA0, 0x20);
	} 
	// Send reset signal to main PIC
	outb(0x20, 0x20);
}
