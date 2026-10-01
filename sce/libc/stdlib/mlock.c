/* libc.a member mlock.o */
#include <reent.h>
#include <libc_internal.h>

void __malloc_lock(Reent *ptr) {}

void __malloc_unlock(Reent *ptr) {}
