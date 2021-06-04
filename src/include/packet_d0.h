#ifndef INCLUDE_PACKET_D0_H
#define INCLUDE_PACKET_D0_H

#include "packet.h"

typedef struct {
        short unknown;
        int manor_size;
} packet_d0_t;

void packet_d0_pack(packet_t *dest, packet_d0_t *src);

#endif
