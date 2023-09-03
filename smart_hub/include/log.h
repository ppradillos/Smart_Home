/**
 * @file    log.h
 * @author  Pablo Pradillos (ppradillos_dev@proton.me)
 * @brief   Module to manage log messages, adding value with a layer of
 *          user-friendly messages, visuals and configurations
 * 
 * @version 0.1
 * @date    2023-09-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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