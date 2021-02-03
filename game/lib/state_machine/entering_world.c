#include <request.h>
#include <server_packet/d0.h>
#include <client_request/quest_list.h>
#include <client_request/enter_world.h>
#include <client_packet/type.h>
#include "in_world.h"
#include "entering_world.h"

static void d0(request_t *request)
{
        packet response[SERVER_PACKET_D0_FULL_SIZE] = {0};

        assert_valid_request(request);

        server_packet_d0(response);
        session_encrypt_packet(request->session, response, response, (size_t) packet_get_size(response));
        request->host->send_response(request->session->socket, response, (size_t) packet_get_size(response));
}

void state_machine_entering_world(request_t *request)
{
        assert_valid_request(request);

        packet_type type = 0;

        type = packet_get_type(request->packet);

        switch (type) {
        case CLIENT_PACKET_TYPE_REQUEST_AUTO_SS_BSPS:
                d0(request);
                break;
        case CLIENT_PACKET_TYPE_REQUEST_QUEST_LIST:
                client_request_quest_list(request->session->socket, request->session, request->host->send_response);
                session_update_state(request->session, ENTERING_WORLD);
                break;
        case CLIENT_PACKET_TYPE_ENTER_WORLD:
                client_request_enter_world(request->session->socket, request->session, &request->storage->character_storage, request->host->send_response);
                session_update_state(request->session, IN_WORLD);

                /*
                 * Not sure about this one, refactor?
                 *
                 * This is being executed so the first spawn
                 * state is being handled (it notifies other players
                 * of the presence of the character).
                 *
                 * After that, the caracter's state will be idle.
                 */
                state_machine_in_world(request);
                break;
        default:
                printf("Packet %02X can't be handled by state_machine_entering_world.\n", type);
                break;
        }
}
