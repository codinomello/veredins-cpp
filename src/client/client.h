// network_client.h
#ifndef CLIENT_CLIENT_H
#define CLIENT_CLIENT_H

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#endif

#include <string.h> // memset
#include <stdlib.h> // size_t

#include "common/types.h"

#define INVALID_SOCKET_VALUE    -1
#define NETWORK_BUFFER_SIZE     2048

typedef struct Client {
    i32         socket;
    struct sockaddr_in  server_address;
    bool        is_initialized;
} Client;


bool client_init(Client* client, const char* server_ip, u16 port);
void client_shutdown(Client* client);
bool client_send(const Client* client, const u8* data, size_t length);
bool client_try_receive(const Client* client,
                           u8* out_buffer,
                           size_t buffer_capacity,
                           size_t* out_received_size);
bool client_test(Client* client);

#endif // CLIENT_CLIENT_H