#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "log.h"

// Define ANSI colors for the serial console
#define ANSI_COLOR_RED              "\x1b[31m"
#define ANSI_COLOR_GREEN            "\x1b[32m"
#define ANSI_COLOR_YELLOW           "\x1b[33m"
#define ANSI_COLOR_BLUE             "\x1b[34m"
#define ANSI_COLOR_MAGENTA          "\x1b[35m"
#define ANSI_COLOR_CYAN             "\x1b[36m"
#define ANSI_COLOR_WHITE            "\x1b[37m"

#define ANSI_COLOR_BRIGHT_RED       "\x1b[91m"
#define ANSI_COLOR_BRIGHT_GREEN     "\x1b[92m"
#define ANSI_COLOR_BRIGHT_YELLOW    "\x1b[93m"
#define ANSI_COLOR_BRIGHT_BLUE      "\x1b[94m"
#define ANSI_COLOR_BRIGHT_MAGENTA   "\x1b[95m"
#define ANSI_COLOR_BRIGHT_CYAN      "\x1b[96m"
#define ANSI_COLOR_BRIGHT_WHITE     "\x1b[97m"

#define ANSI_COLOR_RESET            "\x1b[0m"

// Define the abbreviation for the message category
#define CRIT_ABBREV     "[Crit]"
#define ERR_ABBREV      "[Err]"
#define WARN_ABBREV     "[Warn]"
#define INFO_ABBREV     "[Info]"
#define DBG_ABBREV      "[Debug]"

// Define log categories
typedef enum {
    LOG_MSG_NONE = 0,
    LOG_MSG_CRIT,
    LOG_MSG_ERR,
    LOG_MSG_WARN,
    LOG_MSG_INFO,
    LOG_MSG_DBG
} LOG_MSG_CATEGORY;

// Set log level for the entire program. TODO: set it via config file
const int LOG_LEVEL = LOG_MSG_DBG;


/**
 * @brief Get the Local Date and Time in a fixed string format "YYYY-MM-DD - hh:mm:ss"
 * 
 * @param time_string 
 * @return size_t 
 */
static size_t getLocalDateAndTime(char* time_string)
{
    size_t ret = -1;

    if (time_string) 
    {
        time_t     now;
        struct tm *tm;

        /* get local time */
        now = time(NULL);

        /* format local time */
        tm = localtime(&now);
        ret = sprintf(time_string,"%04d/%02d/%02d - %02d:%02d:%02d", tm->tm_year+1900, tm->tm_mon+1, 
                tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
    }

    return ret;
}


// Function definitions
void print_critical(const char* fmt, ...)
{
    if (fmt)
    {
        va_list args;
        va_start(args, fmt);
        char time[80];
        getLocalDateAndTime(time);

        printf("%s[%s] [%s:%d] ", ANSI_COLOR_RED, CRIT_ABBREV, __FILE__, __LINE__);
        printf("[%s] ", time);
        vprintf(fmt, args);
        va_end(args);
        printf("%s", ANSI_COLOR_RESET);
    }
}


void print_error(const char* fmt, ...)
{
    if (fmt)
    {
        va_list args;
        va_start(args, fmt);
        char time[80];
        getLocalDateAndTime(time);

        printf("%s[%s] [%s:%d] ", ANSI_COLOR_BRIGHT_RED, ERR_ABBREV, __FILE__, __LINE__);
        printf("[%s] ", time);
        vprintf(fmt, args);
        va_end(args);
        printf("%s", ANSI_COLOR_RESET);
    }
}


void print_warning(const char* fmt, ...)
{
    if (fmt)
    {
        va_list args;
        va_start(args, fmt);
        char time[80];
        getLocalDateAndTime(time);

        printf("%s[%s] ", ANSI_COLOR_BRIGHT_YELLOW, WARN_ABBREV);
        printf("[%s] ", time);
        vprintf(fmt, args);
        va_end(args);
        printf("%s", ANSI_COLOR_RESET);
    }
}


void print_info(const char* fmt, ...)
{
    if (fmt)
    {
        va_list args;
        va_start(args, fmt);
        char time[500];
        getLocalDateAndTime(time);

        printf("%s[%s] ", ANSI_COLOR_BRIGHT_GREEN, INFO_ABBREV);
        printf("[%s] ", time);
        vprintf(fmt, args);
        va_end(args);
        printf("%s", ANSI_COLOR_RESET);
    }
}


void print_debug(const char* fmt, ...)
{
    if (fmt)
    {
        va_list args;
        va_start(args, fmt);
        char time[80];
        getLocalDateAndTime(time);

        printf("%s[%s] [%s:%d] ", ANSI_COLOR_BRIGHT_WHITE, DBG_ABBREV, __FILE__, __LINE__);
        printf("[%s] ", time);
        vprintf(fmt, args);
        va_end(args);
        printf("%s", ANSI_COLOR_RESET);
    }
}