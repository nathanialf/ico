#include "regpin.h"
#include "matching.h"

extern int func_002450C8(int *self, int tag);

void func_00245178(int *self, int tag)
{
    register int r;
    register int *p;
    register int tag_v REG("$16");

    tag_v = tag;
    r = func_002450C8(self, tag_v);
    p = (int *)self[0];
    KEEP_LIVE(p);
    tag_v |= 0x70000000;
    KEEP_LIVE(tag_v);
    self[2] = r;
    *p++ = tag_v;
    self[3] = 0;
    self[0] = (int)(p + 1);
    *p = 0;
}
