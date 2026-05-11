#include "matching.h"

extern int    D_00632010;
extern char   D_0061A6D8[];
extern short *func_0013A0F8(int handle, int size, char *file, int line);
extern int    func_00264D60(void);

short *func_001F16A0(void)
{
    int  local_pad[4];
    short *buf = func_0013A0F8(D_00632010, 2, D_0061A6D8, 0xC);
    int v = func_00264D60();
    *buf = (short)v;
    if (v < 0) {
        KEEP_LIVE(v + 0xFFFF);
    }
    KEEP_LIVE(local_pad);
    return buf;
}
