#include "src/include/log.h"

void main()
{
    clear_screen();
    log_info("Welcome Ichsanul Kamil Sudarmi to kamilOS!");
    log_debug("Initializing kernel subsystems...");
    log_warn("No filesystem found, continuing in minimal mode...");
    log_error("Unable to find init process.");

    while (1)
        ;
}