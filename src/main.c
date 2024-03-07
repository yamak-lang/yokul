/*
 * Creator: Naman Dixit
 * Notice: © Copyright 2024 Naman Dixit
 */

#include "common/env.h"
#include "common/macro.h"
#include "common/type.h"
#include "common/memory.h"

#if defined(ENV_OS_WINDOWS)
# include "win32.c"
#endif

#if !defined(BUILD_DLL)
IntFix main (IntFix argc, Char *argv[])
{
    unused_variable(argc);
    unused_variable(argv);
    return 0;
}
#endif
