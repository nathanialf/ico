#include "regpin.h"
#include "matching.h"

extern int    D_00632010;
extern char   D_0061A6D8[];
extern short *func_0013A0F8(int handle, int size, char *file, int line);
extern int    func_00264D60(void);

short *func_001F17B0(int *self)
{
    register int s3 REG("$19");
    int  pad[8];
    int *p = (int *)self[0x15C / 4];
    int *q = (int *)p[0x820 / 4];
    int  count = *((signed char *)q + 0x2E);
    short *buf = func_0013A0F8(D_00632010, count * 2, D_0061A6D8, 0x23);
    if (count > 0) {
        short *b = buf;
        int i = count;
        do {
            *b = (short)func_00264D60();
            i--;
            b++;
        } while (i != 0);
    }
    KEEP_LIVE(pad);
    KEEP_LIVE(s3);
    return buf;
}

__asm__ (".skip 4");
