#ifndef SCREEN_H
#define SCREEN_H

#include <stddef.h>
#include <stdint.h>

// VGA text mode constants
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

// Warna teks (foreground/background)
typedef enum
{
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GREY = 7,
    COLOR_DARK_GREY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_MAGENTA = 13,
    COLOR_LIGHT_BROWN = 14,
    COLOR_WHITE = 15,
} vga_color_t;

void clear_screen();
void put_char(char c, uint8_t color);
void print_string(const char* str, uint8_t color);
void set_cursor(uint8_t x, uint8_t y);
void get_cursor(uint8_t* x, uint8_t* y);
void scroll_screen();

#endif
