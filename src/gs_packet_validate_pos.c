#include <assert.h>
#include "include/util.h"
#include "include/packet.h"
#include "include/gs_types.h"
#include "include/gs_packet_validate_pos.h"

void gs_packet_validate_pos(
        gs_packet_validate_pos_t *dest,
        struct gs_character *src)
{
        assert(dest);
        assert(src);

        dest->id      = src->id;
        dest->x       = src->position.x;
        dest->y       = src->position.y;
        dest->z       = src->position.z;
        dest->heading = src->heading;
}

void gs_packet_validate_pos_pack(packet_t *dest, gs_packet_validate_pos_t *src)
{
        byte_t type = 0x00;

        assert(dest);
        assert(src);

        type = 0x61;

        packet_append_val(dest, type);
        packet_append_val(dest, src->id);
        packet_append_val(dest, src->x);
        packet_append_val(dest, src->y);
        packet_append_val(dest, src->z);
        packet_append_val(dest, src->heading);
}
