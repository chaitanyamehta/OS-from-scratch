#ifndef IDT_H
#define IDT_H

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

void idt_set_gate(uint8_t num, uint32_t base, uint16_t segsel, uint8_t flags);
void idt_install();

#endif
