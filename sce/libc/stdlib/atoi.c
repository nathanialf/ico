/* libc.a member atoi.o */
#include <stdlib.h>
#include <string.h>
#include <reent.h>

int atoi(void *a0)
{
    return (int)strtol(a0, 0, 0xA);
}
