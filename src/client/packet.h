// network_protocol.h
#ifndef NETWORK_PROTOCOL_H
#define NETWORK_PROTOCOL_H

#include <stdlib.h> // size_t

#include "../game/core/types.h"


#define HEADER_SIZE             8
#define MAX_PAYLOAD_SIZE        1024
#define MAX_PACKET_SIZE         (HEADER_SIZE + MAX_PAYLOAD_SIZE)

enum MessageType {
    MSG_JOIN_REQUEST      = 1,
    MSG_JOIN_RESPONSE     = 2,
    MSG_PLAYER_INPUT      = 3,
    MSG_STATE_UPDATE      = 4,
    // Adicione mais aqui depois
};

typedef struct PacketHeader {
    u8      message_type;
    u8      player_id;
    u16     sequence_number;
    u16     payload_size;
    u16     checksum;
} PacketHeader;

// Funções helper (vamos implementar depois)
void    pack_header(u8* buffer, u8 type, u8 player_id, u16 seq, u16 payload_size);
bool    unpack_header(const u8* buffer, PacketHeader* out_header);
u16     calculate_checksum(const u8* data, size_t length);

#endif // NETWORK_PROTOCOL_H