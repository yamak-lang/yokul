/*
 * Creator: Naman Dixit
 * Notice: © Copyright 2023 Naman Dixit
 */

#if !defined(MACRO_H_INCLUDE_GUARD)

# define elemin(array) (sizeof(array)/sizeof((array)[0]))
# define containerof(ptr, type, member)                         \
    ((type*)(void*)(((Byte*)(ptr)) - offsetof(type, member)))

# define KiB(x) (   (x) * 1024ULL)
# define MiB(x) (KiB(x) * 1024ULL)
# define GiB(x) (MiB(x) * 1024ULL)
# define TiB(x) (GiB(x) * 1024ULL)

# define THOUSAND 1000L
# define MILLION  1000000L
# define BILLION  1000000000L

# define unused_variable(var) (void)var

# define global_variable   static
# define global_immutable  static const
# define persistent_value  static

# define internal_function static
# define header_function   static inline

# if defined(ENV_COMPILER_MSVC) || defined(ENV_COMPILER_CLANG_WITH_MSVC)
#  if defined(BUILD_DLL)
#   define exported_function __declspec(dllexport)
#  else
#   define exported_function __declspec(dllimport)
#  endif
# elif defined(ENV_COMPILER_GCC) || defined(ENV_COMPILER_CL)
#  define exported_function __attribute__((visibility("default")))
# endif

# if defined(ENV_COMPILER_MSVC)
#  define likely(x)   (x)
#  define unlikely(x) (x)
# elif defined(ENV_COMPILER_CLANG) || defined(ENV_COMPILER_GCC)
#  define likely(x)   __builtin_expect(!!(x), 1)
#  define unlikely(x) __builtin_expect(!!(x), 0)
# endif

# define macro_gensym_uniq(prefix) macro_gensym2_(prefix, __COUNTER__)
# define macro_gensym_line(prefix) macro_gensym2_(prefix, __LINE__)
# define macro_gensym_func(prefix) macro_gensym2_(prefix, __func__)
# define macro_gensym_file(prefix) macro_gensym2_(prefix, __FILE__)

# define macro_gensym2_(prefix, suffix) macro_gensym_cat_(prefix, suffix)
# define macro_gensym_cat_(prefix, suffix) prefix ## suffix

# define macro_entail(...)                             \
    goto macro_gensym_line(jump_to_else);             \
                                                \
    while (true)                                \
        if (true) {                             \
            __VA_ARGS__;                        \
            break;                              \
        } else macro_gensym_line(jump_to_else):

# define macro_envelop(cloak_arg_pre_action, cloak_arg_post_action)    \
    cloak_arg_pre_action;                                       \
    goto macro_gensym_line(jump_to_else);                             \
                                                                \
    while (true)                                                \
        if (true) {                                             \
            cloak_arg_post_action;                              \
            break;                                              \
        } else macro_gensym_line(jump_to_else):

# if defined(ENV_LANG_C)
#  define MACRO_NULL NULL
# elif defined(ENV_LANG_CPP)
#  define MACRO_NULL nullptr
# endif

# if defined(BUILD_DEBUG)
#  if defined(ENV_OS_WINDOWS)
#   define macro_breakpoint() __debugbreak()
#  elif defined(ENV_OS_LINUX)
#   if defined(ENV_ARCH_X86) || defined(ENV_ARCH_X64)
#    if defined(ENV_COMPILER_GCC) || defined(ENV_COMPILER_CLANG)
#     define macro_breakpoint() __asm__ volatile("int $0x03")
#    endif // !GCC && !Clang
#   endif // !x86 && !x64
#  endif // !window && !linux
# endif // !BUILD_DEBUG

#  if defined(BUILD_DEBUG)
#   define claim(cond)          claim_((cond), #cond, __FILE__, __LINE__)
header_function
void claim_ (Bool cond,
             Char const *cond_str,
             Char const *filename, U32 line_num)
{
    if (!cond) {
        macro_breakpoint();
    }
}
#  else // !BUILD_DEBUG
#   define claim(cond) ((void)(cond))
#  endif // BUILD_DEBUG

#define MACRO_H_INCLUDE_GUARD
#endif
