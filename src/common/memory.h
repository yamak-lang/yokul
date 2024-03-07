/*
 * Creator: Naman Dixit
 * Notice: © Copyright 2023 Naman Dixit
 */

#if !defined(MEMORY_H_INCLUDE_GUARD)

#include "env.h"
#include "macro.h"

#  define MEM_MAX_ALIGN_MINUS_ONE (alignof(max_align_t) - 1u)
#  define memAlignUp(p) (((p) + MEM_MAX_ALIGN_MINUS_ONE) & (~ MEM_MAX_ALIGN_MINUS_ONE))
#  define memAlignDown(p) (memAlignUp((p) - MEM_MAX_ALIGN_MINUS_ONE))

// TODO(naman): Should we add some sample allocators too? Or should they always be applications' concern?

typedef enum Memory_Allocator_Mode {
    Memory_ALLOCATE,
    Memory_REALLOCATE,
    Memory_DEALLOCATE,
    Memory_DEALLOCATE_ALL,
} Memory_Allocator_Mode;

#  define MEMORY_ALLOCATOR_FUNCTION(allocator)          \
    void* allocator (Memory_Allocator_Mode mode,        \
                     size_t new_size,                   \
                     void* old_ptr,                     \
                     void *userdata)

typedef MEMORY_ALLOCATOR_FUNCTION(Memory_Allocator_Function);

// NOTE(naman): This struct should only contain data that can be safely copied around. Any other kind of data should be contained in userdata member.
typedef struct Memory_Allocator {
    Memory_Allocator_Function *function;
    size_t alignment;

    void *userdata;
} Memory_Allocator;

#  define memAlloc(m, ns)      ((m)->function(Memory_ALLOCATE,   ns, MACRO_NULL, (m)->userdata))
#  define memRealloc(m, p, ns) ((m)->function(Memory_REALLOCATE, ns, p,          (m)->userdata))
#  define memDealloc(m, p)     ((m)->function(Memory_DEALLOCATE, 0,  p,          (m)->userdata))

#define MEMORY_H_INCLUDE_GUARD
#endif
