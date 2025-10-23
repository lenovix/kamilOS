#include <stdint.h>
#include "../include/screen.h"

#define VIDEO_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0F

static unsigned short *video_memory = (unsigned short *)VIDEO_ADDRESS;
static int cursor_row = 0, cursor_col = 0;

void clear_screen()
{
    for (int i = 0; i < MAX_ROWS * MAX_COLS; i++)
    {
        video_memory[i] = (unsigned short)(' ' | (WHITE_ON_BLACK << 8));
    }
    cursor_row = 0;
    cursor_col = 0;
}

void print_char(char c, int color)
{
    if (c == '\n')
    {
        cursor_row++;
        cursor_col = 0;
    }
    else
    {
        int index = cursor_row * MAX_COLS + cursor_col;
        video_memory[index] = (unsigned short)(c | (color << 8));
        cursor_col++;
        if (cursor_col >= MAX_COLS)
        {
            cursor_col = 0;
            cursor_row++;
        }
    }
}

void print_string(const char *str, int color)
{
    while (*str)
    {
        print_char(*str++, color);
    }
}
