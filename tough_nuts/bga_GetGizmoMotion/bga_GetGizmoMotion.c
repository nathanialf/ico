#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_SetCameraMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_InitData);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_initLightEnvelope);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_ApplyDObject);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_GetMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_GetExtMotion);

extern int D_00271240[];

#define GIZMO_SECS \
    ((float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1]) / 30.0f)
#define GIZMO_FRAMES(n) ((float)(n))

void bga_GetGizmoMotion(void *obj, int a1, float c, float d, int a2) {
    unsigned int n;

    if (a1 == 1) {
        if (0.0f <= d) {
            n = *(unsigned int *)((char *)obj + 8);
            {
                float r = d;
                if (GIZMO_FRAMES(n) * GIZMO_SECS < d) {
                    r = GIZMO_FRAMES(n) * GIZMO_SECS;
                }
                *(float *)((char *)obj + 0xC) = r;
            }
        } else {
            *(float *)((char *)obj + 0xC) = 0.0f;
        }
        return;
    }
    n = *(unsigned int *)((char *)obj + 8);
    *(float *)((char *)obj + 0xC) = *(float *)((char *)obj + 0xC) + c;
    if (GIZMO_FRAMES(n) * GIZMO_SECS < *(float *)((char *)obj + 0xC)) {
        if (a2 != 0) {
            *(int *)((char *)obj + 0xC) = 0;
            return;
        }
        *(float *)((char *)obj + 0xC) = GIZMO_FRAMES(n) * GIZMO_SECS;
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_setCounter);

extern void _TransCurrentMatrix(void *a0);
extern void _RotCurrentMatrixY(int a0);
extern void _RotCurrentMatrixX(int a0);
extern int _RotCurrentMatrixZ(int a0);

void bga_calcEnvelope(void *a0, short *a1) {
    _TransCurrentMatrix(a0);
    _RotCurrentMatrixY(a1[2]);
    _RotCurrentMatrixX(a1[0]);
    _RotCurrentMatrixZ(a1[4]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", _RotTransCurrentMatrixYXZ);

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


extern int D_00271240[];
extern int D_00629CF0;
extern void bga_SetFrame(void *a0, int a1, int a2);

#define BGA_FRAME_SECONDS \
    ((float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1]) / 30.0f)

#define BGA_CUR_FRAME(o)  (*(signed char *)((char *)(o) + 0xA))
#define BGA_STARTED(o)    (*(signed char *)((char *)(o) + 0xB))
#define BGA_FRAME_COUNT(o) (*(float *)((char *)(o) + 0x14))
#define BGA_HOLD_FRAME(o)  (*(float *)((char *)(o) + 0x18))
#define BGA_PLAY_TIME(o)   (*(float *)((char *)(o) + 0x20))

void bga_resetObjectCounter(void *obj, int mode, int frame, int setFrameArg) {
    int maxFrame;

    if (BGA_STARTED(obj) != 0) {
        D_00629CF0 = 1;
    }
    maxFrame = (int)BGA_FRAME_COUNT(obj);
    if (maxFrame <= -1) {
        maxFrame = 0;
    }
    switch (mode) {
    case 0:
        BGA_PLAY_TIME(obj) = (float)maxFrame * BGA_FRAME_SECONDS;
        BGA_CUR_FRAME(obj) = frame;
        break;
    case -1:
        BGA_PLAY_TIME(obj) = BGA_HOLD_FRAME(obj) * BGA_FRAME_SECONDS;
        BGA_CUR_FRAME(obj) = frame;
        break;
    case -2:
        BGA_PLAY_TIME(obj) = (float)maxFrame * BGA_FRAME_SECONDS;
        BGA_CUR_FRAME(obj) = -1;
        return;
    default:
        BGA_PLAY_TIME(obj) = (float)mode * BGA_FRAME_SECONDS;
        if (mode < maxFrame) {
            BGA_PLAY_TIME(obj) = (float)maxFrame * BGA_FRAME_SECONDS;
        } else if (BGA_HOLD_FRAME(obj) < (float)mode) {
            BGA_PLAY_TIME(obj) = BGA_HOLD_FRAME(obj) * BGA_FRAME_SECONDS;
        }
        BGA_CUR_FRAME(obj) = frame;
        break;
    }
    bga_SetFrame(obj, setFrameArg, 1);
}


INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_SetFrame);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_CalcAnimation);

extern void debug_StdPrintfDummy(char *msg);
extern void func_001AAD00(char *file, int line);
extern void __assert(char *file, int line, void *expr);
extern void *iosFree(int heap, int size, char *file, int line);
extern void mc_Init(void *a0);
extern void mc_TransMicroCode(void *a0, void *a1);
extern char D_006133E0[];
extern char D_00613600[];
extern int D_0062A324;
extern void *D_0062BAA4;
extern char D_0062D940[];

#define SDF_UNK10(n)  (*(int *)((char *)(n) + 0x10))
#define SDF_UNK30(n)  (*(int *)((char *)(n) + 0x30))
#define SDF_ID(n)     (*(int *)((char *)(n) + 0x140))
#define SDF_KEY(n)    (*(int *)((char *)(n) + 0x144))
#define SDF_UNK148(n) (*(int *)((char *)(n) + 0x148))
#define SDF_UNK14C(n) (*(float *)((char *)(n) + 0x14C))
#define SDF_UNK150(n) (*(void **)((char *)(n) + 0x150))
#define SDF_NEXT(n)   (*(void **)((char *)(n) + 0x154))

void bga_CalcSdfCamera(int type, short *p, void *mcArg, int key, float f, int a5) {
    void *node;

    node = D_0062BAA4;
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
                debug_StdPrintfDummy(D_00613600);
                func_001AAD00(D_006133E0, 0x8D2);
                __assert(D_006133E0, 0x8D2, D_0062D940);
                return;
            }
        }
        node = SDF_NEXT(node);
    }

    node = iosFree(D_0062A324, 0x160, D_006133E0, 0x8DA);
    SDF_KEY(node) = key;
    SDF_NEXT(node) = D_0062BAA4;
    SDF_ID(node) = 1;
    D_0062BAA4 = node;
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
        debug_StdPrintfDummy(D_00613600);
        func_001AAD00(D_006133E0, 0x8F3);
        __assert(D_006133E0, 0x8F3, D_0062D940);
        break;
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_addLightning);

extern int D_0062C254;

void bga_DispLightning(void) {
    D_0062C254 = 0;
}

extern int D_0062BA98;
extern int D_0062BAA0;
extern int D_0070A4B0[];
extern void _CopyMatrix(void *dst, void *src);

int bga_ResetCamera(void *p)
{
    int v = D_0062C254;
    if (v != 0) {
        _CopyMatrix(p, D_0070A4B0);
        v = D_0062C254;
    } else {
        D_0062BA98 = 0;
    }
    return v != 0 && D_0062BAA0 == 0;
}

extern int strncmp(void *a0, void *a1, int a2);
extern void debug_StdPrintfDummy();
extern void func_001AAD00(char *file, int line);
extern void __assert(char *file, int line, void *expr);
extern char D_0062D938[];
extern char D_0062D930[];
extern char D_006133E0[];
extern char D_00613428[];

void *bga_GetCameraMatrix(void *a0) {
    if (strncmp(a0, D_0062D938, 3) != 0) {
        debug_StdPrintfDummy(D_00613428);
        func_001AAD00(D_006133E0, 0x383);
        __assert(D_006133E0, 0x383, D_0062D930);
    }
    return a0;
}

extern int D_00629CF0;
extern int D_0062C254;

void bga_InitSdfCamera(int *a0, int a1, int a2) {
    a0[3] = a2;
    D_0062C254 = 1;
    D_00629CF0 = 1;
    if (a1 == -1) {
        *(float *)(a0 + 2) = (float)a0[1];
    } else {
        *(float *)(a0 + 2) = (float)a1;
    }
}

extern int D_00271240[];

int bga_SetCamFrame(void *a0) {
    int n = (0x3C - D_00271240[0] * 0xA) / D_00271240[1];
    float f1 = *(float *)((char *)a0 + 0x18);
    float f2 = *(float *)((char *)a0 + 0x20);
    return (f1 * ((float)n / 30.0f) < f2) || (*(signed char *)((char *)a0 + 0xA) != 1);
}

extern int D_00271240[];

int bga_CheckAnimationFinish(void *a0, int a1, int a2) {
    int n = (0x3C - D_00271240[0] * 0xA) / D_00271240[1];
    int cond = (float)a1 * ((float)n / 30.0f) < *(float *)((char *)a0 + 0x20)
            || *(signed char *)((char *)a0 + 0xA) != 1;
    if (cond && a2 != 0) {
        *(signed char *)((char *)a0 + 0xA) = 0;
    }
    return cond;
}

extern int D_00271240[];

int bga_CheckAnimationFrame(void *a0, int a1, int a2) {
    int n = 0x3C - D_00271240[0] * 0xA;
    return (float)a1 * ((float)(n / D_00271240[1]) / 30.0f) < *(float *)((char *)a0 + 0x20)
        && *(float *)((char *)a0 + 0x20) < (float)a2 * ((float)(n / D_00271240[1]) / 30.0f)
        && *(signed char *)((char *)a0 + 0xA) == 1;
}


/* recovered struct shapes */
typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
    unsigned long long f_20;  /* 0x20 */
    unsigned long long f_28;  /* 0x28 */
} S_004C3710;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00613400;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_006134D0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00613530;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_006135C0;  /* stride 0x4 */

/* end struct shapes */
