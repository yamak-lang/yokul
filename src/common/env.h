/*
 * Creator: Naman Dixit
 * Notice: © Copyright 2023 Naman Dixit
 */

#if !defined(ENV_H_INCLUDE_GUARD)

/* COMMON ===================================================================== */

/* Platform Identification ---------------------------------------------------- */

# if defined(_MSC_VER)
#  if defined(__clang__)
#   define ENV_COMPILER_CLANG
#   define ENV_COMPILER_CLANG_WITH_MSVC
#  else
#   define ENV_COMPILER_MSVC
#  endif
# elif defined (__GNUC__)
#  if defined(__clang__)
#   define ENV_COMPILER_CLANG
#   define ENV_COMPILER_CLANG_WITH_GCC
#  else
#   define ENV_COMPILER_GCC
#  endif
# elif defined(__clang__)
#  define ENV_COMPILER_CLANG
# else
#  error Compiler not supported
# endif

# if defined(_WIN32)
#  if !defined(ENV_OS_WINDOWS) // Shlwapi.h defines it own ENV_OS_WINDOWS to 0. Thankfully, we only care
                           // whether it is defined or now.
#   define ENV_OS_WINDOWS
#  endif
# elif defined(__linux__)
#  define ENV_OS_LINUX
# else
#  error Operating system not supported
# endif

# if defined(ENV_COMPILER_MSVC) || defined(ENV_COMPILER_CLANG_WITH_MSVC)
#  if defined(_M_IX86)
#   define ENV_ARCH_X86
#  elif defined(_M_X64)
#   define ENV_ARCH_X64
#  endif
# elif defined(ENV_COMPILER_CLANG) || defined(ENV_COMPILER_GCC)
#  if defined(__i386__)
#   define ENV_ARCH_X86
#  elif defined(__x86_64__)
#   define ENV_ARCH_X64
#  endif
# endif

# if !defined(ENV_ARCH_X64)  // && !defined(ENV_ARCH_X86)
#  error Architecture not supported
# endif

# if defined(ENV_ARCH_X86)
#  define ENV_BITWIDTH_32
# elif defined(ENV_ARCH_X64)
#  define ENV_BITWIDTH_64
# else
#  error "Bitwidth not supported"
# endif

// TODO(naman): Check the state of C11 support for MSVC, and update this properly
# if defined(ENV_COMPILER_MSVC)
#  if defined(__cplusplus)
#   if __cplusplus == 199711L
#    define ENV_LANG_CPP 1998
#   elif __cplusplus == 201402L
#    define ENV_LANG_CPP 2014
#   elif __cplusplus == 201703L
#    define ENV_LANG_CPP 2017
#   elif __cplusplus == 202002L
#    define ENV_LANG_CPP 2020
#   else
#    define ENV_LANG_CPP 2020 // A future C++, assume the latest
#   endif
#  elif defined(__STDC_VERSION__)
#   if (__STDC_VERSION__ == 201112) || (__STDC_VERSION__ == 201710)
#    define ENV_LANG_C 2011
#   else
#    define ENV_LANG_C 2011 // Earliest C version for which MSVC supports __STDC_VERSION__
#   endif
#  elif defined(__STDC__) // All microsoft extensions are off [/Za (Disable Language Extensions), similar to pedantic]
#   define ENV_LANG_C 1989
#  else // /Za (Disable Language Extensions) is not provided, but MS never supported C99.
#   define ENV_LANG_C 1989
#  endif
# elif defined(ENV_COMPILER_CLANG) || defined(ENV_COMPILER_GCC)
#  if defined(__cplusplus)
#   if __cplusplus == 199711L
#    define ENV_LANG_CPP 1998
#   elif __cplusplus == 201103L
#    define ENV_LANG_CPP 2011
#   elif __cplusplus == 201402L
#    define ENV_LANG_CPP 2014
#   elif __cplusplus == 201703L
#    define ENV_LANG_CPP 2017
#   elif __cplusplus == 202002L
#    define ENV_LANG_CPP 2020
#   elif __cplusplus == 202302L
#    define ENV_LANG_CPP 2023
#   else
#    define ENV_LANG_CPP 2023 // A future C++, assume the latest
#   endif
#  elif defined(__STDC_VERSION__) // Using C Language >= 1994 (1989)
#   if (__STDC_VERSION__ == 199409)
#    define ENV_LANG_C 1989
#   elif (__STDC_VERSION__ == 199901)
#    define ENV_LANG_C 1999
#   elif (__STDC_VERSION__ == 201112) || (__STDC_VERSION__ == 201710)
#    define ENV_LANG_C 2011
#   else
#    define ENV_LANG_C 2011 // Atleast C99 (__STDC_VERSION__ is defined, C94 is too old to fallback on)
#   endif
#  elif defined(__STDC__) && !defined(__STDC_VERSION__)
#    define ENV_LANG_C 1989 // Since C89 doesn't require definition of __STDC_VERSION__
#  endif
# endif

# if !defined(ENV_LANG_C) && !defined(ENV_LANG_CPP)
#  error Language not supported
# endif

# if defined(ENV_OS_WINDOWS)
#  if defined(ENV_ARCH_X86) || defined(ENV_ARCH_X64)
#   define ENDIAN_LITTLE
#  else
#   error Could not determine endianness on Windows
#  endif
# elif defined(ENV_OS_LINUX)
#  include <endian.h>
#  if __BYTE_ORDER == __LITTLE_ENDIAN
#   define ENDIAN_LITTLE
#  elif __BYTE_ORDER == __BIG_ENDIAN
#   define ENDIAN_BIG
#  else
#   error Could not determine endianness on Linux
#  endif
# else
#   error Can not determine endianness, unknown environment
# endif

/* Less noisy pragmas */
# if defined(ENV_COMPILER_CLANG)
#  define pragma_msvc(P)
#  define pragma_clang(P) _Pragma(P)
#  define pragma_gcc(P)
# elif defined(ENV_COMPILER_GCC)
#  define pragma_msvc(P)
#  define pragma_clang(P)
#  define pragma_gcc(P) _Pragma(P)
# elif defined(ENV_COMPILER_MSVC)
#  define pragma_msvc(P) _Pragma(P)
#  define pragma_clang(P)
#  define pragma_gcc(P)
# endif

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <intrin.h>

#define ENV_H_INCLUDE_GUARD
#endif
