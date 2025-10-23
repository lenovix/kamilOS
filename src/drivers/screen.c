#include <stdint.h>
#include "../include/screen.h"

#define VIDEO_ADDRESS 0xB8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0F

static unsigned short *video_memory = (unsigned short *)VIDEO_ADDRESS;
static int cursor_row = 0, cursor_col = 0;

static uint16_t *const VGA_BUFFER = (uint16_t *)VGA_MEMORY;
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

// Encode karakter + warna ke format VGA
static uint16_t vga_entry(char c, uint8_t color)
{
    return (uint16_t)c | ((uint16_t)color << 8);
}

void clear_screen()
{
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            VGA_BUFFER[y * VGA_WIDTH + x] = vga_entry(' ', COLOR_BLACK << 4 | COLOR_LIGHT_GREY);
        }
    }
    cursor_x = 0;
    cursor_y = 0;
}

void put_char(char c, uint8_t color)
{
    if (c == '\n')
    {
        cursor_x = 0;
        cursor_y++;
    }
    else
    {
        VGA_BUFFER[cursor_y * VGA_WIDTH + cursor_x] = vga_entry(c, color);
        cursor_x++;
    }

    if (cursor_x >= VGA_WIDTH)
    {
        cursor_x = 0;
        cursor_y++;
    }

    if (cursor_y >= VGA_HEIGHT)
    {
        scroll_screen();
    }
}

void print_string(const char *str, uint8_t color)
{
    for (size_t i = 0; str[i] != 0; i++)
    {
        put_char(str[i], color);
    }
}

void scroll_screen()
{
    // Geser semua baris ke atas
    for (size_t y = 1; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            VGA_BUFFER[(y - 1) * VGA_WIDTH + x] = VGA_BUFFER[y * VGA_WIDTH + x];
        }
    }

    // Kosongkan baris terakhir
    for (size_t x = 0; x < VGA_WIDTH; x++)
    {
        VGA_BUFFER[(VGA_HEIGHT - 1) * VGA_WIDTH + x] = vga_entry(' ', COLOR_BLACK << 4 | COLOR_LIGHT_GREY);
    }

    if (cursor_y > 0)
        cursor_y--;
}

void set_cursor(uint8_t x, uint8_t y)
{
    cursor_x = x;
    cursor_y = y;
}

void get_cursor(uint8_t *x, uint8_t *y)
{
    *x = cursor_x;
    *y = cursor_y;
}