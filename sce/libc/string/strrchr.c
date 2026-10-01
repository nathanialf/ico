/* libc.a member strrchr.o */
#include <reent.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

char *strrchr(char *s, char c)
{
    char *last = 0;
    while (*s != 0) {
        if (*s == c) {
            last = s;
        }
        s++;
    }
    return (*s == c) ? s : last;
}
