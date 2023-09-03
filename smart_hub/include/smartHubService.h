/**
 * @file    smartHubService.h
 * @author  Pablo Pradillos (ppradillos_dev@proton.me)
 * @brief   This thread module shall receive and process inputs from the smart devices connected 
 *          to the smart home network, such as light sensors, temperature sensors, cameras, etc.
 * 
 *          It sends an ACK back to confirm reception of inputs.
 * 
 * @version 0.1
 * @date    2023-09-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "errorCodes.h"


/**
 * @brief Starts up the smart hub service thread.
 * 
 * @return NETWORK_ERROR 
 */
ERROR_CODE startSmartHubService();