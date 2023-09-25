#include <arpa/inet.h>
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "smartHubService.h"
#include "log4embedded.h"

#define PORT 3001
#define MAX_CLIENTS 5

// threads
static void *clientHandler(void *arg);
static void *smartHubThread(void *arg);


static void *clientHandler(void *arg) {
    int new_socket = *((int *)arg);
    char buffer[1024] = {0};

    // Handle data from the client
    while (1) {
        memset(buffer, 0, sizeof(buffer));
        ssize_t bytes_received = recv(new_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0) {
            log_print_debug("Connection closed by client.\n");
            break;
        }

        log_print_debug("Received data from client: %s", buffer);

        // Echo the received data back to the client
        send(new_socket, buffer, strlen(buffer), 0);
    }

    // Close the client socket
    close(new_socket);
    pthread_exit(NULL);
}


static void *smartHubThread(void *arg)
{
#if 0
    // TODO: monitor current threads running
    pthread_t client_threads[MAX_CLIENTS];
#endif
    intptr_t server_fd = (intptr_t) arg;
    log_print_info("Smart Hub Thread running\n");

    while (1) 
    {
        int new_socket;
        struct sockaddr_in client_addr;
        int client_addr_len = sizeof(client_addr);

        // Accept incoming connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_len)) < 0) {
            log_print_warning("Accept operation failed\n");
            continue;
        }

        log_print_debug("Connection established with client: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Create a new thread for the client
        pthread_t client_thread;
        if (pthread_create(&client_thread, NULL, clientHandler, (void *)&new_socket) != 0) {
            log_print_error("Thread creation failed");
            continue;
        }

        // Detach the thread to avoid resource leak
        pthread_detach(client_thread);
    }

    log_print_info("Smart Hub Thread Exiting...\n");
    return EXIT_SUCCESS;
}


ERROR_CODE startSmartHubService() 
{
    intptr_t server_fd;
    struct sockaddr_in server_addr;
    int addrlen = sizeof(server_addr);
    int opt = 1;

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        return ERROR_SOCKET_CREATE;

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        return ERROR_SOCKET_OPTS;

    // setup some parameters
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the specified address and port
    if (bind(server_fd, (struct sockaddr *)&server_addr, addrlen) < 0)
        return ERROR_SOCKET_BIND;

    // Start listening for incoming connections
    if (listen(server_fd, MAX_CLIENTS) < 0)
        return ERROR_SOCKET_LISTEN;

    log_print_info("Server listening on port %d...\n", PORT);

    // Create a dedicated thread for the service
    pthread_t smart_hub_thread;
    if (pthread_create(&smart_hub_thread, NULL, smartHubThread, (void*)server_fd) != 0)
        return ERROR_THREAD_CREATE;
    else
         // Detach the thread to avoid resource leak
        pthread_detach(smart_hub_thread);

    return OK;
}

