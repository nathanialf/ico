/* libc.a member assert.o */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <reent.h>

void __assert(const char *file, int line, const char *failedexpr)
{
    fiprintf(_impure_ptr->errs, "assertion \"%s\" failed: file \"%s\", line %d\n", failedexpr, file,
             line);
    abort();
}
