/* libc.a member atoi.o */
#include <stdlib.h>
#include <string.h>
#include <reent.h>

int atoi(void *str)
{
    return (int)strtol(str, 0, 0xA);
}
