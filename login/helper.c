#ifndef L2AUTH_LOGIN_HELPER_C
#define L2AUTH_LOGIN_HELPER_C

#include <string.h>

void login_helper_username_from_packet
(
        unsigned char *decrypted_packet,
        unsigned char *dest
)
{
        memcpy(dest, decrypted_packet + 0x62, 14);
}

void login_helper_password_from_packet
(
        unsigned char *decrypted_packet,
        unsigned char* dest
)
{
        memcpy(dest, decrypted_packet + 0x70, 16);
}

#endif