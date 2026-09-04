#include "common.h"

#include "vu0.h"

/* header prototypes (order fixes the inline tail) */
void lw_pos_to_ico_pos(float *dst, float *src);
void apply_matrix_w1(void *a0, void *a1, void *a2);
int ico_m33_to_quat(int a0);
void pbga_start(int *self, int *q);
extern int m33_to_quat();
extern void sceVu0TransposeMatrix();
extern void stage_KillPlayBgAnimation(int **self);
extern int stage_MakePlayBgAnimation();
inline void lw_pos_to_ico_pos(float *dst, float *src) {
    dst[0] = -src[0];
    dst[1] = -src[1];
    dst[2] = -src[2];
    dst[3] = src[3];
}
inline void apply_matrix_w1(void *a0, void *a1, void *a2) {
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
INCLUDE_ASM("asm/nonmatchings/src/itou_sub", m33_to_quat);
inline int ico_m33_to_quat(int a0)
{
    int buf[16];
    sceVu0TransposeMatrix(buf);
    return m33_to_quat(a0, buf);
}
inline void pbga_start(int *self, int *q)
{
    if (*self != 0) {
        stage_KillPlayBgAnimation(self);
    }
    *self = stage_MakePlayBgAnimation(q);
}
