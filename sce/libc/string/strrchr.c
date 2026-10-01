/* libc.a member strrchr.o */
#include <reent.h>

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
