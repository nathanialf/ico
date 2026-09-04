#include "common.h"

#include "vu0.h"



extern void stage_KillPlayBgAnimationIfOverMaxCount(int **self);
extern int stage_SetLocalizeGeometry();
extern void sceVu0TransposeMatrix();
extern int m33_to_quat();
void lw_pos_to_ico_pos(float *dst, float *src) {
    dst[0] = -src[0];
    dst[1] = -src[1];
    dst[2] = -src[2];
    dst[3] = src[3];
}

void apply_matrix_w1(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x10, 5);
    VU0_LSV(lqc2, 6, 0x20, 5);
    VU0_LSV(lqc2, 7, 0x30, 5);
    VU0_LSV(lqc2, 8, 0x0, 6);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 9, 7, 0, w);
    VU0_LSV(sqc2, 9, 0x0, 4);
    VU0_NOP();
}

int ico_m33_to_quat(int a0)
{
    int buf[16];
    sceVu0TransposeMatrix(buf);
    return m33_to_quat(a0, buf);
}

void pbga_start(int *self, int *q)
{
    if (*self != 0) {
        stage_KillPlayBgAnimationIfOverMaxCount(self);
    }
    *self = stage_SetLocalizeGeometry(q);
}

INCLUDE_ASM("asm/nonmatchings/src/itou_sub", set_vertex);

INCLUDE_ASM("asm/nonmatchings/src/itou_sub", DrawLightning2);

INCLUDE_ASM("asm/nonmatchings/src/itou_sub", DrawLightningN);

