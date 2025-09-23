/* uboot_compat.h
 *
 * Minimal compatibility shims for small subsets of:
 *   <linux/types.h>, <asm/types.h>, <linux/bitops.h>
 * when porting U-Boot helper code into NuttX.
 *
 * Drop this into your board/arch include path and #include it where needed.
 */

#ifndef __UBOOT_COMPAT_H
#define __UBOOT_COMPAT_H

/* Standard C headers */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <endian.h>   /* for __BYTE_ORDER, __LITTLE_ENDIAN etc if available */

/* --- Basic linux-style integer type aliases --- */
/* Common kernel-style short names used by many drivers */
typedef uint8_t   u8;
typedef int8_t    s8;
typedef uint16_t  u16;
typedef int16_t   s16;
typedef uint32_t  u32;
typedef int32_t   s32;
typedef uint64_t  u64;
typedef int64_t   s64;
typedef unsigned long ulong;

/* linux sometimes uses __u32 etc. Provide those as well */
typedef u32       __u32;
typedef u16       __u16;
typedef u8        __u8;

#ifndef __iomem
#define __iomem
#endif

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))


/* size_t already exists; provide kernel-style size type if necessary */
typedef uintptr_t phys_addr_t;

/* --- BIT helpers --- */
#ifndef BIT
#define BIT(n) (1UL << (n))
#endif

/* Create a contiguous mask from l..h inclusive (like GENMASK in kernel) */
#ifndef GENMASK
/* Usage: GENMASK(h, l) */
#define GENMASK(h, l) \
    (((~0UL) << (l)) & (~0UL >> (sizeof(unsigned long) * 8 - 1 - (h))))
#endif

/* --- Simple bitops (non-atomic) ---
 *
 * Note: these are simple read/modify/write macros. If you need atomic
 * semantics on SMP/interrupt contexts replace with appropriate primitives.
 */
/* #define set_bit(n, addr)     ((*(addr)) |= (1UL << (n))) */
/* #define clear_bit(n, addr)   ((*(addr)) &= ~(1UL << (n))) */
/* #define test_bit(n, addr)    (((*(addr)) & (1UL << (n))) != 0) */
#define test_and_set_bit(n, addr) \
    ({ unsigned long _old = *(addr); set_bit((n), (addr)); _old & (1UL << (n)); })
#define test_and_clear_bit(n, addr) \
    ({ unsigned long _old = *(addr); clear_bit((n), (addr)); _old & (1UL << (n)); })

/* For code that expects byte-oriented bitops (char *), provide helpers */
#define set_bit_byte(n, addr)    set_bit((n), (unsigned long *)(addr))
#define clear_bit_byte(n, addr)  clear_bit((n), (unsigned long *)(addr))
#define test_bit_byte(n, addr)   test_bit((n), (unsigned long *)(addr))

/* --- simple min/max/clamp if required by ported code --- */
#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif

/* --- Endianness helpers (common linux-style macros) --- */
/* Provide the typical le32_to_cpu / cpu_to_le32 etc.
 * On little-endian targets these are no-ops; on big-endian they byteswap.
 */
#if defined(__BYTE_ORDER) && (__BYTE_ORDER == __BIG_ENDIAN) || \
    defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)

#include <byteswap.h>

static inline uint16_t le16_to_cpu(uint16_t x) { return bswap_16(x); }
static inline uint32_t le32_to_cpu(uint32_t x) { return bswap_32(x); }
static inline uint64_t le64_to_cpu(uint64_t x) { return bswap_64(x); }
static inline uint16_t cpu_to_le16(uint16_t x) { return bswap_16(x); }
static inline uint32_t cpu_to_le32(uint32_t x) { return bswap_32(x); }
static inline uint64_t cpu_to_le64(uint64_t x) { return bswap_64(x); }

#else  /* assume little-endian (typical for ARM) */

static inline uint16_t le16_to_cpu(uint16_t x) { return x; }
static inline uint32_t le32_to_cpu(uint32_t x) { return x; }
static inline uint64_t le64_to_cpu(uint64_t x) { return x; }
static inline uint16_t cpu_to_le16(uint16_t x) { return x; }
static inline uint32_t cpu_to_le32(uint32_t x) { return x; }
static inline uint64_t cpu_to_le64(uint64_t x) { return x; }

#endif

/* --- small helpers for boolean names some code expects --- */
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif

/* --- Debug / VERIFY macros (optional) --- */
#ifndef BUILD_BUG_ON
#define BUILD_BUG_ON(cond) ((void)sizeof(char[1 - 2*!!(cond)]))
#endif

#endif /* __UBOOT_COMPAT_H */
