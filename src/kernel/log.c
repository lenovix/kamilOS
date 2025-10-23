#include "../include/screen.h"
#include "../include/log.h"
#include "../include/colors.h"

#define WHITE_ON_BLACK 0x07
#define YELLOW_ON_BLACK 0x0E
#define RED_ON_BLACK 0x04
#define CYAN_ON_BLACK 0x03

static unsigned short *video_memory = (unsigned short *)0xB8000;
static int cursor = 0;

static void print_line(const char *label, const char *msg, unsigned char color)
{
    const char *prefix = label;
    int i = 0;
    while (prefix[i])
        video_memory[cursor++] = (color << 8) | prefix[i++];
    video_memory[cursor++] = (WHITE_ON_BLACK << 8) | ':';
    video_memory[cursor++] = (WHITE_ON_BLACK << 8) | ' ';
    i = 0;
    while (msg[i])
        video_memory[cursor++] = (color << 8) | msg[i++];
    cursor += 80 - (cursor % 80); // move to next line
}

void log_info(const char *msg)
{
    print_string("[INFO]  ", COLOR_LIGHT_GREEN);
    print_string(msg, COLOR_WHITE);
    put_char('\n', COLOR_WHITE);
}

void log_warn(const char *msg)
{
    print_string("[WARNING]  ", COLOR_YELLOW);
    print_string(msg, COLOR_WHITE);
    put_char('\n', COLOR_WHITE);
}

void log_error(const char *msg)
{
    print_string("[ERROR] ", COLOR_LIGHT_RED);
    print_string(msg, COLOR_WHITE);
    put_char('\n', COLOR_WHITE);
}

void log_debug(const char *msg)
{
    print_string("[DEBUG] ", COLOR_CYAN);
    print_string(msg, COLOR_WHITE);
    put_char('\n', COLOR_WHITE);
}
