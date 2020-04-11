#ifndef L2AUTH_GAME_SERVER_C
#define L2AUTH_GAME_SERVER_C

#include <assert.h>
#include <stdlib.h>
#include <core/l2_socket.h>
#include <core/l2_client.h>
#include <socket_strategy/socket_strategy_linux.h>
#include <game/handler/client.h>
#include <game/server.h>

struct GameServer {
        struct L2Socket socket;
        struct L2SocketStrategy socket_strategy;
        size_t accepted_clients;

        /*
         * (franco.montenegro)
         * I'm sure there is a better way of pre-allocating
         * a bunch of structs with unkown type, but for the time
         * being, this will do
         */
        void* clients;
};

void game_server_free(struct GameServer* server)
{
        assert(server);
        if (server->clients) free(server->clients);
        free(server);
}

struct GameServer* game_server_create(size_t max_players)
{
        struct GameServer* server = calloc(1, sizeof(struct GameServer));

        if (server == NULL) {
                return NULL;
        }

        server->accepted_clients = 0;
        server->clients = calloc(max_players, l2_client_struct_size());

        if (server->clients == NULL) {
                game_server_free(server);
                return NULL;
        }

        return server;
}

void game_server_listen(struct GameServer* server, unsigned short port)
{
        assert(server);
        /*
         * (franco.montenegro)
         * I don't like how we are forcing sockets to be
         * linux, why does the server knows about this?
         */
        socket_strategy_linux(&server->socket_strategy);
        l2_socket_connect(&server->socket, &server->socket_strategy);
        l2_socket_bind(&server->socket, port);
        l2_socket_listen(&server->socket);
}

struct L2Client* game_server_get_client
(
        struct GameServer* server,
        size_t index
)
{
        assert(server);
        return server->clients + (index * l2_client_struct_size());
}

void game_server_accept_client(struct GameServer* server)
{
        assert(server);

        struct L2Client* client = game_server_get_client(
                server,
                server->accepted_clients
        );

        l2_client_init(client);
        l2_client_accept(client, &server->socket);

        server->accepted_clients += 1;
        game_handler_client(server, client);
        server->accepted_clients -= 1;
        l2_client_close(client);
}

void game_server_start(struct GameServer* server, unsigned short port)
{
        assert(server);
        game_server_listen(server, port);
        while(1) game_server_accept_client(server);
}

#endif
