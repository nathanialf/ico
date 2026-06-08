#include "common.h"

typedef struct { int f_0; int f_4; char _8[0x14]; void (*f_1C)(int, int); } BoxB1B95E0;

extern void func_00102828(void *a0);

extern void *func_00105078(void);
extern void LocalizeDirectionOrient(void *buf, void *gobj);
extern void func_00104E38(int a0);
extern void func_00105108(float a0, float a1, float a2);
extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);

void pushStartSE(void *a0, void *a1) {
    void *box = *(void **)((char *)(*(void **)((char *)a1 + 0x15C)) + 0x7F0);
    void *m = func_00105078();
    LocalizeDirectionOrient(m, a1);
    func_00104E38(*(short *)((char *)box + 0x2));
    func_00105108(0.0f, -50.0f, 0.0f);
    MatrixDrive_TurnObjectMatrix(a0, (char *)func_00105078() + 0x30);
}

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
