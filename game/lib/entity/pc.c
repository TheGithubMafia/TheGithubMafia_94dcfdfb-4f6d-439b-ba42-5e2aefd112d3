#include <math.h>
#include <string.h>
#include <log/log.h>
#include <core/l2_packet.h>
#include <core/l2_string.h>
#include "../dto/character.h"
#include "../request_handler/action/my_target_selected_response.h"
#include "../request_handler/action/action_fail_response.h"
#include "../request_handler/say/response.h"
#include "../client.h"
#include "../dto/pc.h"

static void player_send_fail_action_response(struct Client *client)
{
        l2_packet *response = action_fail_response(client);

        client_encrypt_packet(client, response);
        client_queue_response(client, response);

        client_free_mem(client, response);
}

static void player_send_select_target_response
(
        struct Client *client,
        struct Character *target
)
{
        struct Pc *player = client_player(client);
        struct Character player_character = player->character;

        double dx = target->x - player_character.x;
        double dy = target->y - player_character.y;
        double d = sqrt(dx * dx + dy * dy);

        // char message[] = "Bro";
        char *message = client_alloc_mem(client, 10);
        l2_string *l2_message = NULL;

        l2_packet *response = NULL;

        strcat(message, "Foo");

        if (d > 300) {
                l2_message = client_alloc_mem(
                        client,
                        l2_string_calculate_space_from_char(strlen(message) + 1)
                );
                l2_string_from_char(l2_message, message, strlen(message) + 1);
                response = say_response(client, l2_message);
                
                client_encrypt_packet(client, response);
                client_queue_response(client, response);

                client_free_mem(client, l2_message);
                client_free_mem(client, response);

                response = my_target_selected_response(client, target->id, 2);
        } else {
                log_info("Seems fine");
                response = my_target_selected_response(client, target->id, 2);
        }

        client_encrypt_packet(client, response);
        client_queue_response(client, response);

        client_free_mem(client, player);
        client_free_mem(client, response);
}

void player_entity_action(struct Client *client, struct Character *target)
{
        if (!target) {
                player_send_fail_action_response(client);
                return;
        }

        player_send_select_target_response(client, target);
}
