#include "common.h"
#include "ico/types.h"

typedef struct {
    float f_0;
    float f_4;
    float f_8;
    char _C[0x14];
    float f_20;
    char _24[0xC];
    int f_30;
    char _34[0xC];
} __attribute__((aligned(8))) SEParams;

extern SEParams D_004B8C40;
extern void MoveNextStage_Clear(int a0, int a1, int a2, int a3, void *buf, int a5, int a6, int a7);

void landingSE(void *a0, float f0, float f1, float f2, float f3) {
    SEParams buf = D_004B8C40;
    buf.f_0 = f0;
    buf.f_4 = f1;
    buf.f_8 = f2;
    buf.f_20 = f3;
    buf.f_30 = (int)a0;
    *(int *)a0 = 0;
    MoveNextStage_Clear(0x3D, 0x44, -1, 0, &buf, -1, 7, 1);
}

int fallDownStartSE(void *a0) {
    return GOBJ_SUB(a0)->p_7F0->f_8;
}
