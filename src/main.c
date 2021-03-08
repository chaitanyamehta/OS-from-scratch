#include "print.h"

int main(struct multiboot *mboot_ptr)
{
	cls();
	print("Hello, world!");
    return 0xDEADBEEF;
}
