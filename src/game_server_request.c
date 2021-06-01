#include "include/util.h"
#include "include/socket.h"
#include "include/conn.h"
#include "include/log.h"
#include "include/gs_session.h"
#include "include/packet_protocol_version.h"
#include "include/packet_auth_login.h"
#include "include/game_server_request.h"

static void handle_protocol_version(gs_session_t *session)
{
        packet_t response[16] = { 0 };

        packet_protocol_version_t protocol_version = { 0 };

        packet_protocol_version(&protocol_version);
        packet_protocol_version_pack(response, &protocol_version);

        conn_send_packet(session->socket, response);
}

static void handle_auth_login(gs_session_t *session)
{
        static packet_t response[4096] = { 0 };

        static packet_auth_login_t auth_login = { 0 };

        bytes_zero(response, sizeof(response));
        bytes_zero((byte_t *) &auth_login, sizeof(auth_login));

        // packet_auth_login_add_character(&auth_login, character);
        packet_auth_login_pack(response, &auth_login);
        gs_session_encrypt(session, response, response);
        conn_send_packet(session->socket, response);
}

void game_server_request_new_conn(socket_t *socket)
{
        gs_session_new(socket);
}

void game_server_request(socket_t *socket, byte_t *buf, size_t n)
{
        // 65536 being the limit for a single packet.
        static packet_t packet[65536] = { 0 };

        gs_session_t *session = 0;

        u16_t size = 0;

        session = gs_session_find(socket);

        if (!session) {
                log("Game server, no session found for request. Ignoring.");
                return;
        }

        bytes_zero(packet, sizeof(packet));

        gs_session_decrypt(session, packet, buf);
        gs_session_encrypt_conn(session);

        switch (packet_type(packet)) {
        case 0x00: // Protocol version
                handle_protocol_version(session);
                break;
        case 0x08: // Auth request
                handle_auth_login(session);
                break;
        default:
                break;
        }

        size = packet_size(buf);

        // There can be multiple packets inside of buf.
        if (size < n) {
                game_server_request(socket, buf + size, n - size);
        }
}

void game_server_request_disconnect(socket_t *socket)
{
        PREVENT_UNUSED_WARNING(socket);
}