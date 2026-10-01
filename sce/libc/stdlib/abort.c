/* libc.a member abort.o */
#include <reent.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void abort(void)
{
    for (;;) {
        raise(6);
        _exit(1);
    }
}
