/**
 * @file    errorCodes.h
 * @author  Pablo Pradillos (ppradillos_dev@proton.me)
 * @brief   Project's own errno file 
 * @version 0.1
 * @date    2023-09-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

typedef enum {
    OK                      = 0,

    /* Sockets */
    ERROR_SOCKET_CREATE     = -1,
    ERROR_SOCKET_OPTS       = -2,
    ERROR_SOCKET_BIND       = -3,
    ERROR_SOCKET_LISTEN     = -4,
    ERROR_SOCKET_ACCEPT     = -5,
    ERROR_SOCKET_OTHER      = -6,

    /* Threads*/
    ERROR_THREAD_CREATE     = -7,
} ERROR_CODE;