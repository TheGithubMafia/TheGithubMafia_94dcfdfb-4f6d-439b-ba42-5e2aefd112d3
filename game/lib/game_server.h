#ifndef LIB_GAME_SERVER_H
#define LIB_GAME_SERVER_H

#include <stddef.h>
#include <sys/types.h>
#include <host.h>
#include <storage/server.h>

/**
 * Handle game server initialization.
 * Return data that will be attached
 * and sent in new connections, requests
 * and disconnect.
 */
void *game_server_init(host_alloc alloc_memory, host_dealloc dealloc_memory);

/**
 * Handle a new connection.
 */
void game_server_new_connection(int client, storage_server_t *server_storage);

/**
 * Handle new request from client.
 */
void game_server_new_request(int client, unsigned char *request, ssize_t request_size, storage_server_t *server_storage, host_alloc alloc_memory, host_dealloc dealloc_memory, host_send_response_cb send_response, host_disconnect_cb disconnect_connection);

/**
 * Client was disconnected from the server.
 */
void game_server_client_disconnected(int client, storage_server_t *server_storage);

/**
 * Timer tick.
 */
void game_server_timer_tick(double delta, storage_server_t *server_storage);

#endif
