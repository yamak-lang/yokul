/*
 * Creator: Naman Dixit
 * Notice: © Copyright 2024 Naman Dixit
 */

#if !defined(TYPE_H_INCLUDE_GUARD)

# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>
# include <inttypes.h>
# include <uchar.h>
# include <float.h>

typedef int8_t               Int8;
typedef int16_t              Int16;
typedef int32_t              Int32;
typedef int64_t              Int64;
typedef int                  IntFix;

typedef uint8_t              Nat8;
typedef uint16_t             Nat16;
typedef uint32_t             Nat32;
typedef uint64_t             Nat64;
typedef unsigned             NatFix;

typedef size_t               Size;

typedef uintptr_t            Uptr;
typedef intptr_t             Sptr;
typedef ptrdiff_t            Dptr;

typedef float                BFloat32;
typedef double               BFloat64;

typedef bool                 Bool;

typedef unsigned char        Byte; // Also use for padding structs, etc.

typedef char                 Char;

typedef unsigned char        Char8; // FIXME(naman): Change to char8_t with C23
typedef char16_t             Char16;
typedef char32_t             Char32;


#define TYPE_H_INCLUDE_GUARD
#endif
