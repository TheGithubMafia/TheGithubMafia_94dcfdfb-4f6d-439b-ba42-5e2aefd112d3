#ifndef LIB_UTIL_SESSION_CRYPT
#define LIB_UTIL_SESSION_CRYPT

#include <headers.h>
#include <db/conn.h>

/**
 * Encrypt and update/save session encrypt key.
 */
void util_session_encrypt_packet(
        db_conn_t *db,
        int        session_id,
        byte_t *   dest,
        packet *   src,
        size_t     src_size);

/**
 * Decrypt and update/save session decrypt key.
 */
void util_session_decrypt_packet(
        db_conn_t *db,
        int        session_id,
        byte_t *   dest,
        packet *   src,
        size_t     src_size);

/**
 * Mark session connection as encrypted and save it.
 * New packets/requests handled by the session will
 * then be decrypted.
 */
void util_session_encrypt_connection(db_conn_t *db, int session_id);

/**
 * Updates account associated to session.
 * Account being the username used by the client to log in.
 */
void util_session_update_account(db_conn_t *db, int id, char *account);

/**
 * Updates the session's state and saves it to the database.
 */
void util_session_update_state(db_conn_t *db, int id, session_state_t state);

#endif
