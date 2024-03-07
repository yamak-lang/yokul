/*
 * Creator: Naman Dixit
 * Notice: © Copyright 2024 Naman Dixit
 */

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#define NOGDI
#include <Windows.h>
#include <shellapi.h>

global_variable HANDLE GLOBAL_process_heap = NULL;

header_function
MEMORY_ALLOCATOR_FUNCTION(HeapMemoryAllocatorFunction)
{
    unused_variable(userdata);

    if (GLOBAL_process_heap == NULL) GLOBAL_process_heap = GetProcessHeap();

    pragma_clang("clang diagnostic push");
    pragma_clang("clang diagnostic ignored \"-Wunreachable-code-break\"");

    switch (mode) {
        case Memory_ALLOCATE: {
            void *memory = HeapAlloc(GLOBAL_process_heap, 0, new_size);
            return memory;
        } break;

        case Memory_REALLOCATE: {
            void *memory = HeapReAlloc(GLOBAL_process_heap, 0, old_ptr, new_size);
            return memory;
        } break;

        case Memory_DEALLOCATE: {
            HeapFree(GLOBAL_process_heap, 0, old_ptr);
            return NULL;
        } break;

        case Memory_DEALLOCATE_ALL: {
            return NULL;
        } break;
    }

    pragma_clang("clang diagnostic pop");

    return NULL;
}

global_variable Memory_Allocator GLOBAL_heap_memory_allocator = {&HeapMemoryAllocatorFunction, MEMORY_ALLOCATION_ALIGNMENT, NULL};

#define malloc(ns)     memAlloc  (&GLOBAL_heap_memory_allocator, ns)
#define realloc(p, ns) memRealloc(&GLOBAL_heap_memory_allocator, p, ns)
#define free(p)        memDealloc(&GLOBAL_heap_memory_allocator, p)

internal_function
Char8 * winUTF16ToUTF8 (LPWSTR wcstr, Size *cstr_length_out)
{
    Size cstr_length = (Size)WideCharToMultiByte(CP_UTF8, 0, wcstr, -1, NULL, 0, NULL, NULL);
    DWORD cstr_size = (DWORD)cstr_length * sizeof(Char);
    Char8 *cstr = malloc(cstr_size);

    pragma_clang("clang diagnostic push");
    pragma_clang("clang diagnostic ignored \"-Wpointer-sign\"");
    pragma_msvc("warning( push )");
    pragma_msvc("warning( disable : 4057)");
    WideCharToMultiByte(CP_UTF8, 0, wcstr, -1, cstr, (IntFix)cstr_length, NULL, NULL);
    pragma_clang("clang diagnostic pop");
    pragma_msvc("warning( pop )");

    if (cstr_length_out) *cstr_length_out = cstr_length;

    return cstr;
}

internal_function
LPWSTR winUTF8ToUTF16 (Char8 const *cstr, Size *wcstr_length_out)
{
    pragma_clang("clang diagnostic push");
    pragma_clang("clang diagnostic ignored \"-Wpointer-sign\"");
    pragma_msvc("warning( push )");
    pragma_msvc("warning( disable : 4057)");
    Size wcstr_length = (Size)MultiByteToWideChar(CP_UTF8, 0, cstr, -1, NULL, 0);
    DWORD wcstr_size = (DWORD)wcstr_length * sizeof(wchar_t);
    LPWSTR wcstr = malloc(wcstr_size);
    MultiByteToWideChar(CP_UTF8, 0, cstr, -1, wcstr, (IntFix)wcstr_length);
    pragma_clang("clang diagnostic pop");
    pragma_msvc("warning( pop )");

    if (wcstr_length_out) *wcstr_length_out = wcstr_length;

    return wcstr;
}

#if !defined(BUILD_DLL)
IntFix main(IntFix argc, Char *argv[]);

IntFix mainCRTStartup(void);
IntFix mainCRTStartup(void) {
    IntFix argc = 0;

    LPWSTR wcmdline = GetCommandLineW();
    LPWSTR *wargv = CommandLineToArgvW(wcmdline, &argc);

    Char8** uargv = NULL;
    if (wargv) {
        uargv = malloc(sizeof(*uargv) * (Size)argc);
        for (Size i = 0; i < (Size)argc; i++) {
            uargv[i] = winUTF16ToUTF8(wargv[i], NULL);
        }

        LocalFree(wargv);
    }

    IntFix result = main(argc, (Char**)uargv);

    for (Size i = 0; i < (Size)argc; i++) {
        free(uargv[i]);
    }
    free(uargv);

    return result;
}
#endif
