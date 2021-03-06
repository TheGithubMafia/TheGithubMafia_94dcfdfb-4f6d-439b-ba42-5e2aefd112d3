#ifndef INCLUDE_UTIL_H
#define INCLUDE_UTIL_H

#include <sys/types.h>
#include <stdint.h>

#define PREVENT_UNUSED_WARNING(var) var = var

#define arr_size(a) (sizeof(a) / sizeof(a[0]))

// Returns min number between a and b
#ifndef min
#define min(a, b) ((a) > (b) ? (b) : (a))
#endif

// Returns highes number between a and b
#ifndef max
#define max(a, b) ((a) > (b) ? (a) : (b))
#endif

// Absolute value
// #ifndef abs
// #define abs(a) ((a) < 0 ? -(a) : (a))
// #endif

// Ensures x is higher/equal than low and lower/equal than high.
#ifndef clamp
#define clamp(x, low, high) \
        (((x) > (high)) ? (high) : (((x) < (low)) ? (low) : (x)))
#endif

// Copy n bytes from src to dest and advance src.
#define byte_read_n(dest, src, n)                                  \
        do {                                                       \
                bytes_cpy((byte_t *) (dest), (byte_t *) (src), n); \
                src += n;                                          \
        } while (0)

#define byte_read(dest, src) byte_read_n(dest, src, sizeof(dest))

#define byte_read_val(dest, src) byte_read_n(&(dest), src, sizeof(dest))

#define bytes_cpy_str(dest, src, n) \
        bytes_cpy_until(            \
                (unsigned char *) (dest), (unsigned char *) (src), 0, n);

typedef unsigned char byte_t;

typedef int8_t i8_t;
typedef int16_t i16_t;
typedef int32_t i32_t;
typedef int64_t i64_t;
typedef uint8_t u8_t;
typedef uint16_t u16_t;
typedef uint32_t u32_t;
typedef uint64_t u64_t;

// Copy n bytes from src to dest.
void bytes_cpy(byte_t *dest, byte_t *src, size_t n);

// Copy up to n bytes or c byte from src to dest.
void bytes_cpy_until(byte_t *dest, byte_t *src, byte_t c, size_t n);

// Zero n bytes from dest.
void bytes_zero(byte_t *dest, size_t n);

u32_t decode32le(byte_t *buf);

u32_t decode32be(byte_t *buf);

void encode32le(byte_t *buf, u32_t val);

void encode32be(byte_t *buf, u32_t val);

#endif
