#include <log/log.h>
#include <core/l2_raw_packet.h>
#include <core/l2_packet.h>
#include "../../client.h"
#include "../../entity/pc.h"
#include "../../entity/vec3.h"
#include "response.h"
#include "handler.h"

void move_handler(struct Client *client, l2_raw_packet *packet)
{
        unsigned char* content = l2_packet_content(packet);

        struct Vec3 prev_location;
        struct Vec3 new_location;

        l2_packet* response;

        struct Pc *player = client_character(client);

        prev_location.x = player->character.x;
        prev_location.y = player->character.y;
        prev_location.z = player->character.z;

        content = byte_reader_cpy_int_n_mv(content, &new_location.x);
        content = byte_reader_cpy_int_n_mv(content, &new_location.y);
        content = byte_reader_cpy_int_n_mv(content, &new_location.z);

        log_info(
                "Trying to move character from x: %d, y: %d, z: %d to x: %d, y: %d, z: %d",
                prev_location.x,
                prev_location.y,
                prev_location.z,
                new_location.x,
                new_location.y,
                new_location.z
        );

        response = move_response(client);

        client_encrypt_packet(client, response);
        client_queue_response(client, response);

        client_free_mem(client, player);
        client_free_mem(client, response);
}
