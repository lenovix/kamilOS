#include "../include/timer.h"

static unsigned int ticks = 0;

void timer_init()
{
    ticks = 0;
}

unsigned int timer_get_ticks()
{
    // simulasi kenaikan waktu (nanti bisa diganti ke PIT nyata)
    ticks += 123; // 123 ms tiap kali dipanggil (dummy)
    return ticks;
}
