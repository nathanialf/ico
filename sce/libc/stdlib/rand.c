/* libc.a member rand.o */
#include <stdlib.h>
#include <string.h>
#include <reent.h>

void srand(int seed)
{
    char *p = (char *)_impure_ptr;
    *(int *)(p + 0x58) = seed;
}

int rand(void)
{
    char *p = (char *)_impure_ptr;
    int s = *(int *)(p + 0x58) * 0x41C64E6D + 0x3039;
    *(int *)(p + 0x58) = s;
    return s & 0x7fffffff;
}
