#include "log.h"

static FILE* logfile = NULL;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static size_t char_size = sizeof(char);

void close_log(void)
{
    if (logfile)
    {
        lprintf("atexit handler called, closing log");
        fclose(logfile);
    }
}

void lprintf(const char* message, ...)
{
    // the timestamp will be printed into time_buffer
    time_t time_struct;
    time(&time_struct);
    struct tm* time_info = localtime(&time_struct);

    //free(time_info);

    // this probably needs to be locked while working with the file, to avoid problems
    pthread_mutex_lock(&mutex);

    if (logfile == NULL)
    {
        char* logfile_path = getenv(FARL_LOG_ENVVAR);
        logfile = fopen(logfile_path, "w");
        atexit(close_log);
        //free(logfile_path);
    }

    if (logfile)
    {
        // prepend "%s | " to the message format string for writing the timestamp in it,
        // and add the newline, for a total of 6 additional characters
        int log_format_length = FARL_LOG_TIMELEN + 3 + strlen(message) + 1;
        char* log_format = (char*)malloc(char_size * log_format_length);
        strftime(log_format, FARL_LOG_TIMELEN, FARL_LOG_TIMEFMT, time_info);
        strcat(log_format, " | ");
        strcat(log_format, message);
        strcat(log_format, "\n");

        va_list args; // used for passing through the variable number of args

        va_start(args, message);
        vfprintf(logfile, log_format, args);
        va_end(args);

        #ifdef FARL_LOG_STDOUT
        va_start(args, message);
        vprintf(log_format, args);
        va_end(args);
        #endif

        free(log_format);
    }

    pthread_mutex_unlock(&mutex);
}
