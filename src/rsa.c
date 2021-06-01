#include <openssl/bn.h>
#include <openssl/rsa.h>
#include "include/config.h"
#include "include/util.h"
#include "include/rsa.h"

typedef struct {
        BIGNUM *e;

        RSA *key;
} rsa_pack_t;

static rsa_pack_t keys[MAX_CLIENTS] = { 0 };
static size_t     key_count         = 0;

static void rsa_scramble_modulo(byte_t *n)
{
        byte_t temp = 0;

        int i = 0;

        for (i = 0; i < 4; i++) {
                temp        = n[0x00 + i];
                n[0x00 + i] = n[0x4d + i];
                n[0x4d + i] = temp;
        };

        // step 2 xor first 0x40 bytes with last 0x40 bytes
        for (i = 0; i < 0x40; i++) {
                n[i] = (byte_t)(n[i] ^ n[0x40 + i]);
        };

        // step 3 xor bytes 0x0d-0x10 with bytes 0x34-0x38
        for (i = 0; i < 4; i++) {
                n[0x0d + i] = (byte_t)(n[0x0d + i] ^ n[0x34 + i]);
        };

        // step 4 xor last 0x40 bytes with first 0x40 bytes
        for (i = 0; i < 0x40; i++) {
                n[0x40 + i] = (byte_t)(n[0x40 + i] ^ n[i]);
        };
}

rsa_t *rsa_new()
{
        rsa_pack_t *instance = 0;

        instance = &keys[key_count];

        instance->e   = BN_new();
        instance->key = RSA_new();

        BN_dec2bn(&instance->e, "65537");
        RSA_generate_key_ex(instance->key, 1024, instance->e, NULL);

        key_count += 1;

        return (rsa_t *) instance;
}

size_t rsa_size(rsa_t *rsa)
{
        rsa_pack_t *instance = 0;

        instance = (rsa_pack_t *) rsa;

        return (size_t) RSA_size(instance->key);
}

void rsa_modulus(rsa_t *rsa, byte_t *dest)
{
        rsa_pack_t *instance = 0;

        const BIGNUM *n = 0;

        instance = (rsa_pack_t *) rsa;

        RSA_get0_key(instance->key, &n, NULL, NULL);
        BN_bn2bin(n, dest);
        rsa_scramble_modulo(dest);
}

int rsa_decrypt(rsa_t *rsa, byte_t *dest, byte_t *src)
{
        rsa_pack_t *instance = 0;

        int size = 0;

        instance = (rsa_pack_t *) rsa;
        size     = (int) rsa_size(rsa);

        return RSA_private_decrypt(
                size, src, dest, instance->key, RSA_NO_PADDING);
}
