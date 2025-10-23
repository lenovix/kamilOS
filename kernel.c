#include "src/include/log.h"
#include "src/include/screen.h"

void main()
{
    clear_screen();

    print_string("Welcome to kamilOS!\n", COLOR_LIGHT_CYAN);
    print_string("Testing screen driver...\n\n", COLOR_LIGHT_GREY);

    log_info("System initialized successfully.");
    log_warn("Low memory warning.");
    log_error("Kernel panic detected!");
    log_debug("Debugger attached.");

    for (int i = 1; i <= 30; i++)
    {
        print_string("Line ", COLOR_LIGHT_GREEN);
        put_char('0' + (i / 10), COLOR_LIGHT_GREEN);
        put_char('0' + (i % 10), COLOR_LIGHT_GREEN);
        print_string(": Scrolling test\n", COLOR_WHITE);
    }

    while (1)
        ;
}

// void main()
// {
//     clear_screen();
//     log_info("Welcome Ichsanul Kamil Sudarmi to kamilOS!");
//     log_debug("Initializing kernel subsystems...");
//     log_warn("No filesystem found, continuing in minimal mode...");
//     log_error("Unable to find init process.");

//     while (1)
//         ;
// }