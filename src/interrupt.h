#ifndef INTERRUPT_H
#define INTERRUPT_H

#include "stdint.h"

// A struct describing iinterrupt gate.
struct idt_entry
{
	uint16_t base_l;	// Lower 16 bits of the base address
	uint16_t segsel;	// Kernel segment selector
	uint8_t zero;
	uint8_t flags;		// type:5, dpl:2, present:1
	uint16_t base_h;	// Upper 16 bits of the base address
	
} __attribute__((packed));

// A struct describing a pointer to an array of interrupt handlers.
struct idt_ptr
{
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));

#include "stdint.h"

// This defines what stack looks like while handling interrupt
struct registers
{
    uint32_t ds;                  // Data segment selector
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    uint32_t int_no, err_code;    // Interrupt number and error code (if applicable)
    uint32_t eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
};

void idt_set_gate(uint8_t num, uint32_t base, uint16_t segsel, uint8_t flags);
void idt_install();
void isr_install();
void irq_install();

/* This installs a custom IRQ handler for the given IRQ */
void irq_install_handler(int irq, void (*handler)(void));

/* This clears the handler for a given IRQ */
void irq_uninstall_handler(int irq);

#endif
