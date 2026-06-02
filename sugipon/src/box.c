#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box", landingSE);

int fallDownStartSE(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return q[2];
}
