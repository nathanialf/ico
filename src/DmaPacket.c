#include "common.h"

typedef struct {
    int cur;        /* 0x00 */
    int *buf[2];    /* 0x04 0x08 */
    int _0C;
    int *ptr;       /* 0x10 */
    int *_14;
    int *_18;
    int *_1C;
} DpkCtl;

INCLUDE_ASM("asm/nonmatchings/src/DmaPacket", dpk_Init);
extern DpkCtl D_004EE6F0;

void func_0020BB70(void)
{
    int i = D_004EE6F0.cur ^ 1;
    D_004EE6F0.cur = i;
    D_004EE6F0.ptr = D_004EE6F0.buf[i];
    D_004EE6F0._14 = 0;
    D_004EE6F0._18 = 0;
    D_004EE6F0._1C = 0;
}
extern int D_004EE6F0__pn[] __asm__("D_004EE6F0");

int dpk_CheckBufferSize(void)
{
    int idx = D_004EE6F0__pn[0];
    int adj_cur = D_004EE6F0__pn[4] - 0x80000;
    int end_off = (D_004EE6F0__pn + idx)[1];
    return (end_off - adj_cur) >> 4;
}
