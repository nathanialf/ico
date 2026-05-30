#include "regpin.h"
extern void func_00245318(int *self, int a1, int a2);

void func_002451D0(int *self, int flag)
{
    register int *p;        /* a1 */
    register int *new_p REG("$3");    /* v1 */
    register int tag;       /* a0 */
    register int tag_alt REG("$2");   /* v0 */
    func_00245318(self, 2, 3);
    p = (int *)self[0];
    new_p = (int *)((char *)p + 4);
    tag_alt = (int)0xD0000000;
    tag = (int)0x50000000;
    if (flag) tag = tag_alt;
    self[0] = (int)new_p;
    self[3] = (int)p;
    *p = tag;
}
