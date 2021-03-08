#ifndef PRINT_H
#define PRINT_H

#include "stdint.h"

#define VIDEO_MEMORY 0xB8000
#define MAX_ROWS 25
#define MAX_COLUMNS 80

#define WHITE_ON_BLACK 0x0F

#define VGA_CTRL_REG 0x3D4
#define VGA_DATA_REG 0x3D5

// Write a single character
void print_char(char ch);

// Output a null-terminated ASCII string
void print(char *str);

// Clear screen
void cls();

#endif

