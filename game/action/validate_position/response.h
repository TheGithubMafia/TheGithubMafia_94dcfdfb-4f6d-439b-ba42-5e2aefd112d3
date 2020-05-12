#ifndef L2AUTH_GAME_ACTION_VALIDATE_POSITION_RESPONSE_H
#define L2AUTH_GAME_ACTION_VALIDATE_POSITION_RESPONSE_H

#include <core/l2_packet.h>
#include <game/client.h>
#include <game/entity/location.h>

l2_packet* game_action_validate_position_response
(
        struct GameClient* client,
        struct GameEntityLocation location,
        int heading
);

#endif
