#include "common.h"

typedef struct bgaGizmo {
    int unk0;
    void *unk4;
} bgaGizmo;
typedef struct bgaObj {
    unsigned char pad[0x28];
    bgaGizmo *unk28;
    struct bgaObj *unk2C;
    struct bgaObj *unk30;
    int unk34;
} bgaObj;



extern int D_006337B8;
extern void func_001185A8(void *dst, void *src);
extern int D_00710BE0[];
extern int D_006337B0;
extern int D_00633F64;
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F6E28);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F71D0);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F74E8);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", func_001F77A0);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_GetMotion);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_GetExtMotion);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_GetGizmoMotion);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_setCounter);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_calcEnvelope);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", _RotTransCurrentMatrixYXZ);

extern void bga_GetGizmoMotion(void *a0, int a1, float c, float d, int a2);

void bga_CalcObject(bgaObj *obj, float f, int a1) {
    bgaGizmo *g = obj->unk28;
    if (g != 0 && g->unk4 != 0) {
        do {
            bga_GetGizmoMotion(g->unk4, 1, 0.0f, f, a1);
            g++;
        } while (g->unk4 != 0);
    }
    if (obj->unk2C != 0) {
        bga_CalcObject(obj->unk2C, f, a1);
    }
    if (obj->unk30 != 0) {
        bga_CalcObject(obj->unk30, f, a1);
    }
    bga_GetGizmoMotion(&obj->unk34, 1, 0.0f, f, a1);
}

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_resetObjectCounter);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_SetFrame);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_CalcAnimation);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_CalcSdfCamera);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_addLightning);

void bga_DispLightning(void) {
    D_00633F64 = 0;
}

int bga_ResetCamera(void *p)
{
    int v = D_00633F64;
    if (v != 0) {
        func_001185A8(p, D_00710BE0);
        v = D_00633F64;
    } else {
        D_006337B0 = 0;
    }
    return v != 0 && D_006337B8 == 0;
}

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_GetCameraMatrix);

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_InitSdfCamera);

extern int D_00274EC0[];

int bga_SetCamFrame(void *a0) {
    int n = (0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1];
    float f1 = *(float *)((char *)a0 + 0x18);
    float f2 = *(float *)((char *)a0 + 0x20);
    return (f1 * ((float)n / 30.0f) < f2) || (*(signed char *)((char *)a0 + 0xA) != 1);
}

int bga_CheckAnimationFinish(void *a0, int a1, int a2) {
    int n = (0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1];
    int cond = (float)a1 * ((float)n / 30.0f) < *(float *)((char *)a0 + 0x20)
            || *(signed char *)((char *)a0 + 0xA) != 1;
    if (cond && a2 != 0) {
        *(signed char *)((char *)a0 + 0xA) = 0;
    }
    return cond;
}

INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_CheckAnimationFrame);

