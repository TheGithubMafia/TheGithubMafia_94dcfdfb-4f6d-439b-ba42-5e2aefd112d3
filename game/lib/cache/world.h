#ifndef WORLD_H
#define WORLD_H

#include "../../shared/l2_server.h"
#include "../entity/pc.h"

struct World;

struct World *world_new(struct L2Server *server);

void world_update_player(struct World *world, int id, struct Pc *player);

struct Player *world_get_player(struct World *world, int id);

#endif