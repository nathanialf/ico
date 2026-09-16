#include "common.h"

typedef struct {
    int cur;     /* 0x00 */
    int *buf[2]; /* 0x04 0x08 */
    int _0C;
    int *ptr; /* 0x10 */
    int *_14;
    int *_18;
    int *_1C;
} DpkCtl;

extern DpkCtl D_004EE6F0;
extern int D_0063A43C;

void dpk_Init(void)
{
    D_004EE6F0.cur = 0;
    D_004EE6F0.buf[0] =
        (int *)((int)iosMallocDebug(D_0063A43C, 0x80000, "src/DmaPacket.c", 134) | 0x30000000);
    D_004EE6F0.buf[1] =
        (int *)((int)iosMallocDebug(D_0063A43C, 0x80000, "src/DmaPacket.c", 135) | 0x30000000);
    D_004EE6F0.ptr = D_004EE6F0.buf[D_004EE6F0.cur];
}

void dpk_SwapBuffer(void)
{
    int i = D_004EE6F0.cur ^ 1;
    D_004EE6F0.cur = i;
    D_004EE6F0.ptr = D_004EE6F0.buf[i];
    D_004EE6F0._14 = 0;
    D_004EE6F0._18 = 0;
    D_004EE6F0._1C = 0;
}

int dpk_CheckBufferSize(void)
{
    int idx = ((int *)&D_004EE6F0)[0];
    int adj_cur = ((int *)&D_004EE6F0)[4] - 0x80000;
    int end_off = ((int *)&D_004EE6F0 + idx)[1];
    return (end_off - adj_cur) >> 4;
}
