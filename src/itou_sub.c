#include "common.h"



extern void stage_KillPlayBgAnimationIfOverMaxCount(int **self);
extern int stage_SetLocalizeGeometry();
extern void func_002439B0();
extern int func_00198438();
void m33_to_quat(float *dst, float *src) {
    dst[0] = -src[0];
    dst[1] = -src[1];
    dst[2] = -src[2];
    dst[3] = src[3];
}

INCLUDE_ASM("asm/nonmatchings/src/itou_sub", lw_pos_to_ico_pos);

int apply_matrix_w1(int a0)
{
    int buf[16];
    func_002439B0(buf);
    return func_00198438(a0, buf);
}

void ico_m33_to_quat(int *self, int *q)
{
    if (*self != 0) {
        stage_KillPlayBgAnimationIfOverMaxCount(self);
    }
    *self = stage_SetLocalizeGeometry(q);
}

INCLUDE_ASM("asm/nonmatchings/src/itou_sub", pbga_start);

INCLUDE_ASM("asm/nonmatchings/src/itou_sub", func_00198B70);

INCLUDE_ASM("asm/nonmatchings/src/itou_sub", func_00199620);

