#include "interrupt.h"
#include "stdint.h"
#include "io.h"
#include "print.h"
#include "timer.h"

int timer_ticks = 0;

/* Handles the timer interrupt */
void timer_handler()
{
	++timer_ticks;    
}	

void init_timer()
{
	uint32_t divisor = 1193180/100;
	// Send the command byte.
	outb(0x43, 0x36);
	// Send the frequency divisor.
	outb(0x40, divisor & 0xFF);
	outb(0x40, (divisor>>8) & 0xFF);
	
	irq_install_handler(0, timer_handler);	
}
