/* libc.a member strrchr.o */
#include <reent.h>
#include <string.h>

char *strrchr(const char *s, int i)
{
    const char *last = 0;
    char c = i;

    while (*s) {
        if (*s == c) {
            last = s;
        }
        s++;
    }

    if (*s == c) {
        last = s;
    }

    return (char *)last;
}
