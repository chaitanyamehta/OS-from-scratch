#include "interrupt.h"
#include "stdint.h"
#include "string.h"

/* Declare an IDT of 256 entries.
   If any undefined IDT entry is hit, it normally
   will cause an "Unhandled Interrupt" exception. Any descriptor
   for which the 'presence' bit is cleared (0) will generate an
   "Unhandled Interrupt" exception */
struct idt_entry idt[256];
struct idt_ptr idtp;

/* This exists in 'start.s', and is used to load our IDT */
extern void idt_load();

// Set an entry in IDT
void idt_set_gate(uint8_t num, uint32_t base, uint16_t segsel, uint8_t flags)
{
    idt[num].base_l = base & 0x00FF;
    idt[num].base_h = (base >> 16) & 0x00FF;
    idt[num].segsel = segsel;
    idt[num].zero = 0;
    idt[num].flags = flags;
}

/* Installs the IDT */
void idt_install()
{
    /* Sets the special IDT pointer up */
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = (uint32_t)&idt;

    /* Clear out the entire IDT, initializing it to zeros */
    memset(&idt, 0, sizeof(struct idt_entry) * 256);
    
    /* Points the processor's internal register to the new IDT */
    idt_load();
}

