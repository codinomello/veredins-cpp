#include <stdio.h>

#include "client.h"

#ifdef _WIN32
    // linkagem do winsock via CMake ou flag: -lws2_32
#endif

static bool set_non_blocking(i32 sock) {
#ifdef _WIN32
    u_long mode = 1;
    return ioctlsocket(sock, FIONBIO, &mode) == 0;
#else
    i32 flags = fcntl(sock, F_GETFL, 0);
    if (flags == -1) return false;
    return fcntl(sock, F_SETFL, flags | O_NONBLOCK) != -1;
#endif
}

bool client_init(Client* client, const char* server_ip, u16 port) {
    if (client == NULL) return false;

    client->socket = INVALID_SOCKET_VALUE;
    client->is_initialized = false;

#ifdef _WIN32
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
        printf("WSAStartup failed.\n");
        return false;
    }
#endif

    client->socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client->socket == INVALID_SOCKET_VALUE) {
        printf("error creating socket.\n");
#ifdef _WIN32
        WSACleanup();
#endif
        return false;
    }

    memset(&client->server_address, 0, sizeof(client->server_address));
    client->server_address.sin_family = AF_INET;
    client->server_address.sin_port = htons(port);

    if (inet_pton(AF_INET, server_ip, &client->server_address.sin_addr) <= 0) {
        printf("invalid IP: %s\n", server_ip);
        goto cleanup;
    }

    if (!set_non_blocking(client->socket)) {
        printf("failed to configure non-blocking\n");
        goto cleanup;
    }

    client->is_initialized = true;
    printf("UDP client initialized -> %s:%u\n", server_ip, port);
    return true;

cleanup:
#ifdef _WIN32
    closesocket(client->socket);
    WSACleanup();
#else
    close(client->socket);
#endif
    client->socket = INVALID_SOCKET_VALUE;
    return false;
}

void client_shutdown(Client* client) {
    if (client == NULL || client->socket == INVALID_SOCKET_VALUE) return;

#ifdef _WIN32
    closesocket(client->socket);
    WSACleanup();
#else
    close(client->socket);
#endif

    client->socket = INVALID_SOCKET_VALUE;
    client->is_initialized = false;
}

bool client_send(const Client* client, const u8* data, size_t length) {
    if (client == NULL || !client->is_initialized || data == NULL || length == 0) {
        return false;
    }

    i32 sent = sendto(client->socket,
                      (const char*)data,
                      (i32)length,
                      0,
                      (struct sockaddr*)&client->server_address,
                      sizeof(client->server_address));

    if (sent < 0) {                    // ← usando < 0 em vez de SOCKET_ERROR
#ifdef _WIN32
        i32 err = WSAGetLastError();
        if (err == WSAEWOULDBLOCK) return true;
#else
        if (errno == EAGAIN || errno == EWOULDBLOCK) return true;
#endif
        return false;
    }

    return (size_t)sent == length;
}

bool client_try_receive(const Client* client,
                                u8* out_buffer,
                                size_t buffer_capacity,
                                size_t* out_received_size) {
    if (client == NULL || !client->is_initialized || out_buffer == NULL || out_received_size == NULL) {
        return false;
    }

    struct sockaddr_in from_addr;
    socklen_t addr_len = sizeof(from_addr);

    i32 received = recvfrom(client->socket,
                            (char*)out_buffer,
                            (i32)buffer_capacity,
                            0,
                            (struct sockaddr*)&from_addr,
                            &addr_len);

    if (received > 0) {
        *out_received_size = (size_t)received;
        return true;
    }

    // nenhum dado disponível (normal em non-blocking)
#ifdef _WIN32
    if (WSAGetLastError() == WSAEWOULDBLOCK) {
        *out_received_size = 0;
        return false;
    }
#else
    if (errno == EAGAIN || errno == EWOULDBLOCK) {
        *out_received_size = 0;
        return false;
    }
#endif

    // erro real
    return false;
}

bool client_test(Client* client) {
    *client = (Client){0};

    printf("trying to connect in 127.0.0.1:12345 ...\n");

    if (client_init(client, "127.0.0.1", 12345)) {
        printf("connected with success!\n");

        u8 msg[] = "hello from veredins client!";
        if (client_send(client, msg, sizeof(msg) - 1)) {
            printf("message sent!\n");
        }

        // Tenta receber (pode rodar em loop se quiser)
        u8 buffer[NETWORK_BUFFER_SIZE];
        size_t received = 0;

        for (int i = 0; i < 10; i++) {
            if (client_try_receive(client, buffer, NETWORK_BUFFER_SIZE, &received)) {
                buffer[received] = '\0';
                printf("recieved echo: %s\n", (char*)buffer);
                break;
            }

            // Pequeno delay pra não floodar CPU
            for (volatile int j = 0; j < 1000000; j++);
        }

        // NÃO chame shutdown aqui! Só no final do jogo
        // client_shutdown(client);

        return true;
    } else {
        printf("fail to initialize client\n");
        return false;
    }
}