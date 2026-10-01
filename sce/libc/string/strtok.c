/* libc.a member strtok.o */
#include <stdlib.h>
#include <string.h>
#include <reent.h>

int strtok(int s, int sep)
{
    return strtok_r(s, sep, (int)_impure_ptr + 0x5C);
}
