#ifndef L2AUTH_GAME_SERVER_C
#define L2AUTH_GAME_SERVER_C

#include <log/log.h>
#include <core/l2_server.h>
#include <game/handler/client.h>
#include <game/server.h>

void game_server_start_or_die(unsigned short port, size_t max_players)
{
        struct L2Server* server = l2_server_create(max_players);

        log_info("Starting gameserver");

        if (server == NULL) {
                log_fatal("Not able to allocate memory for gameserver");
                exit(1);
        }

        l2_server_start(server, port, game_handler_client);
}

#endif
