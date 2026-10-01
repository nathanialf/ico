/* libc.a member strtok.o */
#include <stdlib.h>
#include <string.h>
#include <reent.h>

int strtok(int a0, int a1)
{
    return strtok_r(a0, a1, (int)_impure_ptr + 0x5C);
}
