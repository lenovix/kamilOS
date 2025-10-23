#ifndef LOG_H
#define LOG_H

#include "screen.h"
void log_internal(const char *level, const char *msg, int color, const char *file, int line);
void log_info(const char *msg);
void log_warn(const char *msg);
void log_error(const char *msg);
void log_debug(const char *msg);
void clear_screen();

#endif
