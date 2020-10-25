#include <assert.h>
#include <core/l2_raw_packet.h>
#include "../../client.h"
#include "response.h"
#include "next_handler.h"
#include "handler.h"

void show_map_handler(struct Client *client, l2_raw_packet *packet)
{
        assert(client);
        assert(packet);

        l2_packet *response = NULL;

        response = show_map_response(client, 1665);

        client_encrypt_packet(client, response);
        client_queue_response(client, response);

        client_update_request_handler(client, &show_map_next_handler);

        client_free_mem(client, response);
}
