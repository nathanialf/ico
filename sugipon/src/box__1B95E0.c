#include "common.h"

typedef struct { int f_0; int f_4; char _8[0x14]; void (*f_1C)(int, int); } BoxB1B95E0;

extern void func_00102828(void *a0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1B95E0", pushStartSE);

void pullStartSE(void *self) {
    int *d = *(int **)((char *)self + 0x15C);
    BoxB1B95E0 *B = *(BoxB1B95E0 **)((char *)d + 0x7F0);
    int mode = B->f_4;
    if (mode != -1 && mode != 1) {
        void (*fp)(int, int) = B->f_1C;
        if (fp != 0)
            fp(d[0], 0);
    } else {
        void (*fp)(int, int) = B->f_1C;
        if (fp != 0)
            fp(d[0], B->f_4);
    }
    func_00102828(self);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1B95E0", wallHitSE);
