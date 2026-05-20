/* file_off 0x03CD30 — func_0013CD30: scan slot[0x40] array for first byte==0 */
#include "regpin.h"

void *func_0013CD30(int *l)
{
    int count;
    int i;
    register char *p REG("$3");
    count = *l;
    i = 0;
    if (count <= 0) {
        return (void *)0;
    }
    p = (char *)l[1];
    do {
        if (*(unsigned char *)p == 0) {
            return p;
        }
        i++;
        p += 0x40;
    } while (i < count);
    return (void *)0;
}
