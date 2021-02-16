#ifndef LIB_SERVER_PACKET_SAY_H
#define LIB_SERVER_PACKET_SAY_H

#include <headers.h>
#include <character.h>

struct ServerPacketSay {
        int sender_obj_id;
        l2_string_type_t msg_type;
        l2_string_t sender_name[28];
        l2_string_t msg[256];
};

typedef struct ServerPacketSay server_packet_say_t;

void server_packet_say(packet *dest, character_t *character, l2_string_type_t msg_type, char *msg, size_t msg_size);

#endif
