#ifndef L2AUTH_LOGIN_HANDLER_REQUEST_LOGIN_SERVER_C
#define L2AUTH_LOGIN_HANDLER_REQUEST_LOGIN_SERVER_C

#include <log/log.h>
#include <core/l2_packet.c>
#include <login/session_key.c>
#include <login/packet/play_ok.c>

l2_packet* login_handler_request_login_server(struct LoginSessionKey *session_key)
{
        log_info("Client wants to log into server");
        return login_packet_play_ok(session_key);
}

#endif
