/* libc.a member strstr.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <reent.h>
#include <string.h>

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

char *strstr(const char *searchee, const char *lookfor)
{
    if (*searchee == 0) {
        if (*lookfor) {
            return (char *)0;
        }
        return (char *)searchee;
    }

    while (*searchee) {
        unsigned int i;
        i = 0;

        while (1) {
            if (lookfor[i] == 0) {
                return (char *)searchee;
            }
            if (lookfor[i] != searchee[i]) {
                break;
            }
            i++;
        }
        searchee++;
    }

    return (char *)0;
}
