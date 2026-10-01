/* libc.a member signalr.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <stdlib.h>
#include <string.h>
#include <reent.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>

int _kill_r(Reent *ptr, int pid, int sig)
{
    int ret;
    errno = 0;
    ret = kill(pid, sig);
    if (ret == -1) {
        if (errno != 0) {
            ptr->err = errno;
        }
    }
    return ret;
}

int _getpid_r(void)
{
    return getpid();
}
