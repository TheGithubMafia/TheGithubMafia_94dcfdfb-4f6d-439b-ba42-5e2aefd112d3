#ifndef ENTER_WORLD_HANDLER_H
#define ENTER_WORLD_HANDLER_H

#include <core/l2_raw_packet.h>
#include "../../client.h"

void enter_world_handler
(struct Client *client, l2_raw_packet *packet);

#endif
