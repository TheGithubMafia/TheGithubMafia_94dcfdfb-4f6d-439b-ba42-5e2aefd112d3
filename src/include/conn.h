#ifndef INCLUDE_CONN_H
#define INCLUDE_CONN_H

#include <stdio.h>
#include "util.h"
#include "packet.h"

#define conn_send_packet(socket, packet) \
        conn_send_response(socket, packet, (size_t) packet_size(packet))

typedef void (*conn_send_response_cb)(void *s, byte_t *buf, size_t n);

void conn_set_cb(conn_send_response_cb cb);

void conn_send_response(void *socket, byte_t *buf, size_t n);

#endif
