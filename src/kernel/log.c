#include "../include/log.h"

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

void log_info(const char *msg) { print_line("[INFO]", msg, WHITE_ON_BLACK); }
void log_warn(const char *msg) { print_line("[WARN]", msg, YELLOW_ON_BLACK); }
void log_error(const char *msg) { print_line("[ERROR]", msg, RED_ON_BLACK); }
void log_debug(const char *msg) { print_line("[DEBUG]", msg, CYAN_ON_BLACK); }
