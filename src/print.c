#include "stdint.h"
#include "io.h"
#include "print.h"

uint16_t * const video_memory = (uint16_t *)VIDEO_MEMORY;

int cursor_x = 0;
int cursor_y = 0;

static void move_cursor();
static void scroll();

// Write a single character
void print_char(char ch)
{
	uint16_t *location;
	
	// Handle backspace by moving cursor backwards
	if(ch == 0x08 && cursor_x) 
	{
		--cursor_x;
	}
	
	// Handle a tab by increasing the cursor's X, but only to a point
	// where it is divisible by 8.
	else if (ch == 0x09)
	{
		cursor_x = (cursor_x + 8) & ~(8 - 1);
	}
	
	// Handle carriage return
	else if (ch == '\r')
	{
		cursor_x = 0;
	}

	// Handle newline by moving cursor back to left and increasing the row
	else if (ch == '\n')
	{
		cursor_x = 0;
 		++cursor_y;
	}
	
	// Handle any other printable character.
	else if(ch >= ' ')
	{
		location = video_memory + (cursor_y * MAX_COLUMNS + cursor_x);
		*location = WHITE_ON_BLACK << 8 | ch;
		++cursor_x;
   }

	// Check if we need to insert a new line because we have reached the end
	// of the screen.
	if (cursor_x >= MAX_COLUMNS)
	{
		cursor_x = 0;
		++cursor_y;
	}

	// Scroll the screen if needed.
	scroll();
	// Move the hardware cursor.
	move_cursor();
}

// Output a null-terminated ASCII string
void print(const char *str)
{
	int i = 0;
	while(str[i])
	{
		print_char(str[i++]);
	}
}

// Clear screen
void cls()
{
	uint16_t blank = (WHITE_ON_BLACK << 8) | 0x20; /* space */
	int i;
	
	for(i = 0; i < MAX_ROWS * MAX_COLUMNS; ++i)
	{
		video_memory[i] = blank;
	} 
	
	cursor_x = 0;
	cursor_y = 0;
	move_cursor();
}

static void move_cursor()
{
	uint16_t cursor_location = cursor_y * MAX_COLUMNS + cursor_x;
	outb(VGA_CTRL_REG, 14);						// Setting high cursor byte
	outb(VGA_DATA_REG, cursor_location >> 8);	// Send high cursor byte
	outb(VGA_CTRL_REG, 15);						// Setting low cursor byte
	outb(VGA_DATA_REG, cursor_location);		// Send low cursor byte
}

static void scroll()
{

	uint16_t blank = (WHITE_ON_BLACK << 8) | 0x20; /* space */
	
	// Row 25 is the end, this means we need to scroll up
	if(cursor_y >= MAX_ROWS)
	{
		int i;
		// Move the current text chunk that makes up screen back in the buffer by a line
		for(i = 0; i < (MAX_ROWS - 1) * MAX_COLUMNS; ++i)
		{
			video_memory[i] = video_memory[i + MAX_COLUMNS];
		}
		
		// The last line should now be blank
		for(; i < MAX_ROWS * MAX_COLUMNS; ++i)
		{
			video_memory[i] = blank;
		} 
		// The cursor should should now be on the last line
		cursor_y = MAX_ROWS - 1;
	}	 
}
