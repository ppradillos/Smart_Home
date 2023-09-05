#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

#include "smartHubService.h"
#include "log.h"

int main() {
    ERROR_CODE ret = OK;

    /* Set log level for this application */
    log_set_level(LOG_MSG_DBG);

    /* Start up threads and components*/

    /* Smart Hub Service */
    ret = startSmartHubService();
    if (OK != ret)
        goto startup_error;

    log_print_info("Smart Hub application booted up successfully\n");

    // Services are now up and running. Main thread exites.
    pthread_exit(NULL);

startup_error:
    log_print_error("An error occured when booting up the Smart Hub application.\n");
    log_print_error("Error Code: [%d]\n", ret);
    log_print_info("Exiting...\n");
    return EXIT_FAILURE;
}
