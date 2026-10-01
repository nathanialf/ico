/* libc.a member mlock.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <reent.h>
#include <libc_internal.h>

void __malloc_lock(Reent *ptr) {}

void __malloc_unlock(Reent *ptr) {}
