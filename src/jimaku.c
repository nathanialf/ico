#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/jimaku", display_texture);
extern void iosCdvdBackGroundMgrSeek(char *self, int val);
extern void iosCdvdBackGroundRead();

void iosCdvdBackGroundReadJimaku(int self, int a1, int size)
{
    int large = size + 0x7FE;
    int v1 = size - 1;
    int neg_one = -1;
    if (neg_one < v1) large = v1;
    large = ((large >> 11) + 1) << 11;
    iosCdvdBackGroundRead(self, a1, large);
    iosCdvdBackGroundMgrSeek(self, *(int *)((char *)self + 0x110) + size);
}
INCLUDE_ASM("asm/nonmatchings/src/jimaku", jimakuHandler);
INCLUDE_ASM("asm/nonmatchings/src/jimaku", jimakuMgrBegin);
INCLUDE_ASM("asm/nonmatchings/src/jimaku", jimakuMgrNext);
INCLUDE_ASM("asm/nonmatchings/src/jimaku", jimakuMgrJump);
extern char D_006E5000[];
extern char D_006E5038[];
extern char D_006E5070[];
extern void iosCdvdBackGroundMgrDelete(char *self);
extern int iosSemaDelete(int *self);

void jimakuMgrEnd(int *p)
{
    int val = p[0x4C / 4];
    if (val != 0) {
        iosCdvdBackGroundMgrDelete(val);
    }
    iosSemaDelete(D_006E5070);
    iosSemaDelete(D_006E5038);
    iosSemaDelete(D_006E5000);
}
extern int D_002A5040[];
extern int iosMsgSend(int *self, int a1, int a2);

void jimakuBegin(int a0)
{
    *(int *)a0 = 0;
    iosMsgSend(D_002A5040, a0, 1);
}
extern int D_0028F4E8[];

void jimakuNext(int *p) {
    if (D_0028F4E8[0] != 0) {
        *p = 1;
        iosMsgSend(D_002A5040, p, 0);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/jimaku", jimakuJump);
extern void jimakuMgrEnd__pn() __asm__("jimakuMgrEnd");

void jimakuEnd(void)
{
    D_0028F4E8[0] = 0;
    jimakuMgrEnd__pn();
}
INCLUDE_ASM("asm/nonmatchings/src/jimaku", jimakuDisp);
INCLUDE_ASM("asm/nonmatchings/src/jimaku", func_0017D4D8);
INCLUDE_ASM("asm/nonmatchings/src/jimaku", func_0017D5D0);
