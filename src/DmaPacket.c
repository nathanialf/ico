#include "common.h"


extern int D_00633F70;
void dpk_SwapBuffer(int a0)
{
    if (a0 < 0) {
        D_00633F70 = 0;
    } else if (a0 >= 0xD) {
        D_00633F70 = 0xC;
    } else {
        D_00633F70 = a0;
    }
}

extern int D_00710D10[];
extern int dl_GetPri(void);

void dpk_Init(int a0, int a1, int a2) {
    int *entry = &D_00710D10[D_00633F70 * 10];
    int old;
    if (entry[0]) {
        dl_GetPri();
    }
    old = entry[9];
    *(long long *)(entry + 6) = a0;
    entry[4] = a2;
    entry[0] = 1;
    *(long long *)(entry + 2) = (long long)a1 & 0xFFFFFFFLL;
    entry[1] = old;
    entry[9] = old + 0x10;
}

int dpk_CheckBufferSize(void) {
    return D_00633F70;
}

INCLUDE_ASM("asm/nonmatchings/src/DmaPacket", func_001FBB48);

typedef struct {
    int cur;        /* 0x00 */
    int *buf[2];    /* 0x04 0x08 */
    int _0C;
    int *ptr;       /* 0x10 */
    int *_14;
    int *_18;
    int *_1C;
} DpkCtl;

extern DpkCtl D_004C7710;

void func_001FBBE0(void)
{
    int i = D_004C7710.cur ^ 1;
    D_004C7710.cur = i;
    D_004C7710.ptr = D_004C7710.buf[i];
    D_004C7710._14 = 0;
    D_004C7710._18 = 0;
    D_004C7710._1C = 0;
}

