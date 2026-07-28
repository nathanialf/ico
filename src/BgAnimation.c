#include "common.h"
#define SDF_UNK10(n)  (*(int *)((char *)(n) + 0x10))
#define SDF_UNK30(n)  (*(int *)((char *)(n) + 0x30))
#define SDF_ID(n)     (*(int *)((char *)(n) + 0x140))
#define SDF_KEY(n)    (*(int *)((char *)(n) + 0x144))
#define SDF_UNK148(n) (*(int *)((char *)(n) + 0x148))
#define SDF_UNK14C(n) (*(float *)((char *)(n) + 0x14C))
#define SDF_UNK150(n) (*(void **)((char *)(n) + 0x150))
#define SDF_NEXT(n)   (*(void **)((char *)(n) + 0x154))

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

extern char D_0061A8D8[];
extern char D_0061AAF0[];
extern int D_00632024;
extern void *D_006337BC;
extern char D_006337D8[];
extern void debug_assertMessage(char *msg);
extern void *func_0013A0F8(int heap, int size, char *file, int line);
extern void func_001AD768(char *file, int line);
extern void func_00263FF0(char *file, int line, void *expr);
extern void mc_Init(void *a0);
extern void mc_TransMicroCode(void *a0, void *a1);

void bga_CalcSdfCamera(int type, short *p, void *mcArg, int key, float f, int a5) {
    void *node;

    node = D_006337BC;
    while (node != 0) {
        if (SDF_KEY(node) == key) {
            switch (type) {
            case 0xF:
                p[1] = -1;
                /* fallthrough */
            case 0xE:
                SDF_UNK150(node) = p;
                SDF_UNK14C(node) = f;
                SDF_UNK148(node) = a5;
                SDF_UNK10(node) = -1;
                mc_TransMicroCode(node, mcArg);
                return;
            case 0x10:
                *(int *)((char *)node + (SDF_ID(node) << 5) + 0x10) = p[1];
                mc_TransMicroCode((char *)node + (SDF_ID(node) << 5), mcArg);
                SDF_ID(node)++;
                return;
            default:
                debug_assertMessage(D_0061AAF0);
                func_001AD768(D_0061A8D8, 0x9D5);
                func_00263FF0(D_0061A8D8, 0x9D5, D_006337D8);
                return;
            }
        }
        node = SDF_NEXT(node);
    }

    node = func_0013A0F8(D_00632024, 0x160, D_0061A8D8, 0x9DD);
    SDF_KEY(node) = key;
    SDF_NEXT(node) = D_006337BC;
    SDF_ID(node) = 1;
    D_006337BC = node;
    switch (type) {
    case 0xF:
        p[1] = -1;
        /* fallthrough */
    case 0xE:
        SDF_UNK150(node) = p;
        SDF_UNK14C(node) = f;
        SDF_UNK148(node) = a5;
        mc_TransMicroCode(node, mcArg);
        break;
    case 0x10:
        SDF_UNK30(node) = p[1];
        mc_TransMicroCode((char *)node + (*(volatile int *)((char *)node + 0x140) << 5), mcArg);
        SDF_UNK150(node) = 0;
        mc_Init(node);
        SDF_ID(node)++;
        break;
    default:
        debug_assertMessage(D_0061AAF0);
        func_001AD768(D_0061A8D8, 0x9F7);
        func_00263FF0(D_0061A8D8, 0x9F7, D_006337D8);
        break;
    }
}

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

extern char D_0061A8D8[];
extern char D_0061A918[];
extern char D_006337C8[];
extern char D_006337D0[];
extern void debug_assertMessage(char *msg);
extern void func_001AD768(char *file, int line);
extern void func_00263FF0(char *file, int line, void *expr);
extern int func_002653B8(void *a0, void *a1, int a2);

void *bga_GetCameraMatrix(void *a0) {
    if (func_002653B8(a0, D_006337D0, 3) != 0) {
        debug_assertMessage(D_0061A918);
        func_001AD768(D_0061A8D8, 0x3E4);
        func_00263FF0(D_0061A8D8, 0x3E4, D_006337C8);
    }
    return a0;
}

extern int D_006319F0;
extern int D_00710C10[];
extern int D_00710C20[];

void bga_InitSdfCamera(int *a0, int a1, int a2) {
    a0[3] = a2;
    D_00633F64 = 1;
    if (a2 == 1) {
        D_006319F0 = a2;
        mc_TransMicroCode(D_00710C20, D_00710C10);
    }
    if (a1 == -1) {
        *(float *)(a0 + 2) = (float)a0[1];
    } else {
        *(float *)(a0 + 2) = (float)a1;
    }
}

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

