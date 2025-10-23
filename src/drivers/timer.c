#include "../include/timer.h"

static volatile uint32_t timer_ticks = 0;

void timer_callback()
{
    timer_ticks++;
}

void timer_init()
{
    timer_ticks = 0; // Dummy init
}

uint32_t timer_get_ticks()
{
    return timer_ticks;
}
