#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define FARL_LOG_ENVVAR "FARL_LOG"
#define FARL_LOG_TIMEFMT "%Y-%m-%d %H:%M:%S"
#define FARL_LOG_TIMELEN 26  // "YYYY-mm-dd HH:MM:SS"

void lprintf(const char* message, ...);
