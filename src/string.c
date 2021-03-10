#include "string.h"

void *memcpy(void *dest, const void *src, int count)
{
	/* Add code here to copy 'count' bytes of data from 'src' to
	*  'dest', finally return 'dest' */
	int i;
	char *dest_p = (char *)dest;
	const char *src_p = (const char *)src;
	for (i = 0; i < count; ++i)
	{
		dest_p[i] = src_p[i];
	}
	return dest;
}

void *memset(void *dest, char val, int count)
{
	/* Add code here to set 'count' bytes in 'dest' to 'val'.
	*  Again, return 'dest' */
	int i;
	char *dest_p = (char *)dest;
	for (i = 0; i < count; ++i)
	{
		dest_p[i] = val;
	}
	return dest;
}

void *memsetw(void *dest, unsigned short val, int count)
{
	/* Same as above, but this time, we're working with a 16-bit
	*  'val' and dest pointer. Your code can be an exact copy of
	*  the above, provided that your local variables if any, are
	*  unsigned short */
	int i;
	unsigned short *dest_p = (unsigned short *)dest;
	for (i = 0; i < count; ++i)
	{
		dest_p[i] = val;
	}
	return dest;
}
