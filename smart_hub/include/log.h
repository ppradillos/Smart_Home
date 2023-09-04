/**
 * @file    log.h
 * @author  Pablo Pradillos (ppradillos_dev@proton.me)
 * @brief   Lightweight library to manage log messages for any application. 
 *          
 *          It adds an extra layer on top of the standard library's printf, such as:
 *              - 6 possible log levels: from one totally restrictive (no log output) to a 
 *                  non-restrictive one (debug), where all print calls from this API
 *                  shall make it to the log output.
 *                  See LOG_MSG_CATEGORY enum.
 * 
 *              - 5 different print calls, based on how important is to log a specific event in the source code:
 *                  - print_critical
 *                  - print_error
 *                  - print_warning
 *                  - print_info
 *                  - print_debug
 * 
 *              - Log messages have their own format: [label][date] message with arguments, where:
 *                  - label: category of the log message, according to LOG_MSG_CATEGORY.
 *                  - date: when the log message was printed
 *                  - message with arguments: it follows original standard C printf format
 *                  - Each one of the five print categories (mentioned above) has its own color to make them more visual to the eye,
 *                    only if stdout is the used log output.
 * 
 *              - It's possible to select a text file where log messages shall be written. If nothing is stated, stdout
 *                is assumed as the log output.
 * 
 * @version 1.0
 * @date    2023-09-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/*  
    Enum LOG_MSG_CATEGORY: Define log categories from level 0 to level 6. 
    LOG_MSG_NONE (0) = most restrictive. No log message shall make it to the log output.
    LOG_MSG_DBG  (6) = every print call across the codebase shall make it to the log output, including those for debugging purposes.
*/
typedef enum {
    LOG_MSG_NONE = 0,   // no logs
    LOG_MSG_CRIT,       // log only critical messages/events
    LOG_MSG_ERR,        // log only critical and error messages/events
    LOG_MSG_WARN,       // log critical, error and warning messages/events
    LOG_MSG_INFO,       // log every print call made out of this API, but debug messages. This is the default value.
    LOG_MSG_DBG         // log every print call made out of this API.
} LOG_MSG_CATEGORY;


/**
 * @brief   Set the Log Level for the entire application, according
 *          to LOG_MSG_CATEGORY enum.
 * 
 *          In case this function is not called, LOG_MSG_INFO level shall be assumed.
 * 
 *          it's strongly recommended to call this function on start up (e.g.: in the main funtion)
 *          if a different log level must apply.
 * 
 * @param log_level 
 */
void setLogLevel(LOG_MSG_CATEGORY log_level);

/**
 * @brief   Get the current Log Level in use by the library
 * 
 * @return  LOG_MSG_CATEGORY 
 */
LOG_MSG_CATEGORY getLogLevel();

/**
 * @brief   Set the log file where logs shall be written. Filepath size must not exceed 256 bytes.
 * 
 *          In case no log file specified, stdout shall be assumed as log output.
 * 
 * @param filepath 
 */
void setLogFile(const char* filepath, size_t filepath_size);

/**
 * @brief   Print critical messages if selected log level allows it.
 * 
 * @param fmt 
 */
void print_critical(const char* fmt, ...);

/**
 * @brief   Print error messages if selected log level allows it.
 * 
 * @param fmt 
 */
void print_error(const char* fmt, ...);

/**
 * @brief   Print warning messages if selected log level allows it.
 * 
 * @param fmt 
 */
void print_warning(const char* fmt, ...);

/**
 * @brief   Print info messages if selected log level allows it.
 * 
 * @param fmt 
 */
void print_info(const char* fmt, ...);

/**
 * @brief   Print debug messages if selected log level allows it.
 * 
 * @param fmt 
 */
void print_debug(const char* fmt, ...);