#include <assert.h>
#include "include/util.h"
#include "include/l2_string.h"
#include "include/packet.h"
#include "include/gs_types.h"
#include "include/gs_packet_user_info.h"

void gs_packet_user_info_set_char(
        gs_packet_user_info_t *dest,
        struct gs_character *src)
{
        assert(dest);
        assert(src);

        l2_string_from_char(dest->name, src->name, sizeof(dest->name));

        dest->heading       = src->heading;
        dest->x             = src->position.x;
        dest->y             = src->position.y;
        dest->z             = src->position.z;
        dest->id            = src->session->id;
        dest->race_id       = src->race;
        dest->sex           = src->sex;
        dest->class_id      = src->_class;
        dest->level         = src->level;
        dest->exp           = src->exp;
        dest->str           = src->stats.str;
        dest->dex           = src->stats.dex;
        dest->con           = src->stats.con;
        dest->_int          = src->stats._int;
        dest->wit           = src->stats.wit;
        dest->men           = src->stats.men;
        dest->hp            = src->stats.hp;
        dest->mp            = src->stats.mp;
        dest->max_hp        = src->stats.max_hp;
        dest->max_mp        = src->stats.max_mp;
        dest->cp            = src->stats.cp;
        dest->max_cp        = src->stats.max_cp;
        dest->sp            = src->sp;
        dest->exp           = src->exp;
        dest->sp            = src->sp;
        dest->p_attack      = src->stats.p_attack;
        dest->m_attack      = src->stats.m_attack;
        dest->p_def         = src->stats.p_def;
        dest->m_def         = src->stats.m_def;
        dest->evasion_rate  = src->stats.evasion_rate;
        dest->accuracy      = src->stats.accuracy;
        dest->critical_hit  = src->stats.critical_hit;
        dest->hair_style_id = src->hair_style;
        dest->hair_color_id = src->hair_color;
        dest->face          = src->face;
        // dest->access_level    = 1;
        dest->inventory_limit = 42;

        dest->run_speed                 = src->stats.run_speed;
        dest->walk_speed                = src->stats.walk_speed;
        dest->p_attack_speed            = src->stats.p_attack_speed;
        dest->m_attack_speed            = src->stats.m_attack_speed;
        dest->movement_speed_multiplier = src->stats.movement_speed_multiplier;
        dest->attack_speed_multiplier   = src->stats.attack_speed_multiplier;
        dest->collision_radius          = src->collision_radius;
        dest->collision_height          = src->collision_height;
        dest->name_color                = src->name_color;
        dest->current_load              = 1;
        dest->max_load                  = src->max_load;
        dest->unknown                   = 0x28;
        dest->name_color                = 0xFFFFFF;
}

void gs_packet_user_info_pack(packet_t *dest, gs_packet_user_info_t *src)
{
        byte_t type = 0x00;

        size_t name_size  = 0;
        size_t title_size = 0;

        assert(dest);
        assert(src);

        type = 0x04;

        name_size  = l2_string_bytes(src->name);
        title_size = l2_string_bytes(src->title);

        packet_append_val(dest, type);
        packet_append_val(dest, src->x);
        packet_append_val(dest, src->y);
        packet_append_val(dest, src->z);
        packet_append_val(dest, src->heading);
        packet_append_val(dest, src->id);
        packet_append_n(dest, (byte_t *) src->name, name_size);
        packet_append_val(dest, src->race_id);
        packet_append_val(dest, src->sex);
        packet_append_val(dest, src->class_id);
        packet_append_val(dest, src->level);
        packet_append_val(dest, src->exp);
        packet_append_val(dest, src->str);
        packet_append_val(dest, src->dex);
        packet_append_val(dest, src->con);
        packet_append_val(dest, src->_int);
        packet_append_val(dest, src->wit);
        packet_append_val(dest, src->men);
        packet_append_val(dest, src->max_hp);
        packet_append_val(dest, src->hp);
        packet_append_val(dest, src->max_mp);
        packet_append_val(dest, src->mp);
        packet_append_val(dest, src->sp);
        packet_append_val(dest, src->current_load);
        packet_append_val(dest, src->max_load);
        packet_append_val(dest, src->unknown);

        packet_append_val(dest, src->paperdoll_under);
        packet_append_val(dest, src->paperdoll_r_ear);
        packet_append_val(dest, src->paperdoll_l_ear);
        packet_append_val(dest, src->paperdoll_neck);
        packet_append_val(dest, src->paperdoll_r_finger);
        packet_append_val(dest, src->paperdoll_l_finger);

        packet_append_val(dest, src->paperdoll_head);

        packet_append_val(dest, src->paperdoll_r_hand);
        packet_append_val(dest, src->paperdoll_l_hand);
        packet_append_val(dest, src->paperdoll_gloves);
        packet_append_val(dest, src->paperdoll_chest);
        packet_append_val(dest, src->paperdoll_legs);
        packet_append_val(dest, src->paperdoll_feet);
        packet_append_val(dest, src->paperdoll_back);
        packet_append_val(dest, src->paperdoll_lr_hand);
        packet_append_val(dest, src->paperdoll_hair);

        packet_append_val(dest, src->paperdoll_under);
        packet_append_val(dest, src->paperdoll_r_ear);
        packet_append_val(dest, src->paperdoll_l_ear);
        packet_append_val(dest, src->paperdoll_neck);
        packet_append_val(dest, src->paperdoll_r_finger);
        packet_append_val(dest, src->paperdoll_l_finger);

        packet_append_val(dest, src->paperdoll_head);
        packet_append_val(dest, src->paperdoll_r_hand);
        packet_append_val(dest, src->paperdoll_l_hand);
        packet_append_val(dest, src->paperdoll_gloves);
        packet_append_val(dest, src->paperdoll_chest);
        packet_append_val(dest, src->paperdoll_legs);
        packet_append_val(dest, src->paperdoll_feet);
        packet_append_val(dest, src->paperdoll_back);
        packet_append_val(dest, src->paperdoll_lr_hand);
        packet_append_val(dest, src->paperdoll_hair);

        packet_append_val(dest, src->p_attack);
        packet_append_val(dest, src->p_attack_speed);
        packet_append_val(dest, src->p_def);
        packet_append_val(dest, src->evasion_rate);
        packet_append_val(dest, src->accuracy);
        packet_append_val(dest, src->critical_hit);
        packet_append_val(dest, src->m_attack);
        packet_append_val(dest, src->m_attack_speed);
        packet_append_val(dest, src->p_attack_speed);
        packet_append_val(dest, src->m_def);
        packet_append_val(dest, src->pvp_flag); // 0 = normal, 1 = violet
        packet_append_val(dest, src->karma);
        packet_append_val(dest, src->run_speed);
        packet_append_val(dest, src->walk_speed);
        packet_append_val(dest, src->run_speed);  // swim_run_speed
        packet_append_val(dest, src->walk_speed); // swim_walk_speed
        packet_append_val(dest, src->run_speed);  // fly_run_speed
        packet_append_val(dest, src->walk_speed); // fly_walk_speed
        packet_append_val(dest, src->run_speed);  // fly_run_speed
        packet_append_val(dest, src->walk_speed); // fly_walk_speed
        packet_append_val(dest, src->movement_speed_multiplier);
        packet_append_val(dest, src->attack_speed_multiplier);
        packet_append_val(dest, src->collision_radius);
        packet_append_val(dest, src->collision_height);
        packet_append_val(dest, src->hair_style_id);
        packet_append_val(dest, src->hair_color_id);
        packet_append_val(dest, src->face);
        packet_append_val(dest, src->access_level);
        packet_append_n(dest, (byte_t *) src->title, title_size);
        packet_append_val(dest, src->clan_id);
        packet_append_val(dest, src->clan_crest_id);
        packet_append_val(dest, src->ally_id);
        packet_append_val(dest, src->ally_crest_id);
        packet_append_val(dest, src->clan_leader);
        packet_append_val(dest, src->mount_type);
        packet_append_val(dest, src->private_store_type);
        packet_append_val(dest, src->dwarven_craft);
        packet_append_val(dest, src->pk_kills);
        packet_append_val(dest, src->pvp_kills);
        packet_append_val(dest, src->cubics);
        packet_append_val(dest, src->party_members); // 1 find party
        packet_append_val(dest, src->abnormal_effect);
        packet_append_n(dest, src->char_empty, 1);
        packet_append_val(dest, src->clan_privileges);
        packet_append_n(dest, (byte_t *) src->int_empty, sizeof(i32_t) * 7);
        packet_append_val(dest, src->recommendation_left);
        packet_append_val(dest, src->recommendation_have);
        packet_append_val(dest, src->int_empty[0]);
        packet_append_val(dest, src->inventory_limit);
        packet_append_val(dest, src->class_id);
        packet_append_val(dest, src->int_empty[0]);
        packet_append_val(dest, src->max_cp);
        packet_append_val(dest, src->cp);
        packet_append_val(dest, src->mounted);
        packet_append_val(dest, src->char_empty[0]); // 1 = blue, 2 = red
        packet_append_val(dest, src->clan_crest_large_id);
        packet_append_val(dest, src->hero_symbol);
        packet_append_val(dest, src->hero);
        packet_append_n(dest, src->char_empty, 1);
        packet_append_val(dest, src->fish_x);
        packet_append_val(dest, src->fish_y);
        packet_append_val(dest, src->fish_z);
        packet_append_val(dest, src->name_color);
}
