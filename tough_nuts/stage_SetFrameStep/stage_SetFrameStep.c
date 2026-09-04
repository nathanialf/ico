#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_MakeGObj);

extern void func_001180A8(void *a0);
extern void _SetCurrentMatrix(void *a0);
extern void func_00118108(void);
extern void _TransposeCurrentMatrix(void);
extern void _ApplyCurrentMatrix(void *a0, void *a1);
extern void _ScaleVector(void *a0, void *a1, float a2);
extern void _PopCurrentMatrix(void);
extern char *D_00629C70;

void stage_ApplyData(void *a0) {
    func_001180A8(a0);
    _SetCurrentMatrix(D_00629C70 + 0x80);
    func_00118108();
    _TransposeCurrentMatrix();
    _ApplyCurrentMatrix(a0, D_00629C70 + 0xB0);
    _ScaleVector(a0, a0, -1.0f);
    *(float *)((char *)a0 + 0xC) = 1.0f;
    _PopCurrentMatrix();
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_Init);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_SetAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_ContinueAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_ResetAnimation);

extern int D_0062A054;

void stage_CalcAnimationNoParent(int a0) {
    D_0062A054 = a0;
}

extern void *isysGObjGetExist_begin(int a0);
extern void *isysGObjGetExist_next(void *obj);

void stage_CalcAnimationParent(int a0, int a1) {
    void *obj;
    for (obj = isysGObjGetExist_begin(a0); obj != 0; obj = isysGObjGetExist_next(obj)) {
        void *node = *(void **)((char *)obj + 0x15C);
        if (node != 0) {
            void *dl = *(void **)((char *)node + 0x810);
            if (dl != 0) {
                void *x = *(void **)((char *)node + 0x814);
                if (x != 0) {
                    if (*(short *)((char *)dl + 0x30) == a0) {
                        *(long long *)((char *)x + 0x30) =
                            (*(long long *)((char *)x + 0x30) & ~0x04000000) |
                            ((long long)(a1 & 1) << 26);
                    }
                }
            }
        }
    }
}



typedef struct { char _0[0x3C]; float f3C; } AnimNode;
typedef struct { char _0[0x810]; AnimNode *f810; AnimNode *f814; } Stage;

void stage_DispAnimation(Stage *a0, float f) {
    if (f > 0.0f) {
        a0->f814->f3C = f;
    } else {
        a0->f814->f3C = a0->f810->f3C;
    }
}

extern int D_0062A050;

void stage_SetScale(void) {
    D_0062A050 = 0;
    D_0062A054 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_PlayBgAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_PlayBgAnimationDissolve);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_MakePlayBgAnimation);

extern char D_0066DBD8[];
extern int D_0062BF54;
extern void bga_resetObjectCounter(int *obj, int mode, int frame, int setFrameArg);
extern void bga_InitSdfCamera(int *a0, int a1, int a2, int a3);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_KillPlayBgAnimation);


extern char D_0066DBD8[];
extern int D_0062BF54;
extern char D_0054FFA8[];
extern char D_0062BF08[];
extern char D_00550160[];
extern int bga_SetCamFrame(int a0);
extern int font_CheckAlign(int a0);
extern void debug_StdPrintfDummy();
extern void func_001AAD00(void *a0, int a1);
extern void __assert(void *a0, int a1, void *a2);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

int stage_DispBgAnimation(int a0, int a1) {
    int i;
    char *e = (char *)D_0066DBD8;
    for (i = 0; i < D_0062BF54; i++, e += 0x290) {
        int *entry1 = *(int **)(e + 0x280);
        if (a0 == entry1[0x58 / 4]) {
            int mode = *(int *)(e + 0x28C) >> 30;
            switch (mode) {
                case 0:
                    if (bga_SetCamFrame(*(int *)(e + 0x284)) != 0) {
                        stage_KillPlayBgAnimation(a0, 0, -1);
                        stage_KillPlayBgAnimation(a1, 1, 0);
                        return 1;
                    }
                    return 0;
                case 1:
                    if (font_CheckAlign(*(int *)(e + 0x288)) != 0) {
                        stage_KillPlayBgAnimation(a0, 0, -1);
                        stage_KillPlayBgAnimation(a1, 1, 0);
                        return 1;
                    }
                    return 0;
            }
        }
    }
    debug_StdPrintfDummy(D_00550160);
    func_001AAD00(D_0054FFA8, 0x372);
    __assert(D_0054FFA8, 0x372, D_0062BF08);
    return 0;
}


extern void bga_ResetAnimation(void);

void stage_SetCameraForceOff(void) {
    bga_ResetAnimation();
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_CheckAnimationFinish);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_CheckAnimationFrame);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_SetLoopFlag);

void stage_SetFrameStep(int a0, float arg0) {
    int i;
    char *e = (char *)D_0066DBD8;
    for (i = 0; i < D_0062BF54; i++) {
        int *entry1 = *(int **)(e + 0x280);
        if (a0 == entry1[0x58 / 4] && (*(int *)(e + 0x28C) >> 30) == 0) {
            int j;
            int **objs = (int **)(e + 0x80);
            for (j = 0; j < ((*(int *)(e + 0x28C) << 22) >> 22); j++) {
                int k = 0;
                if ((*(int **)((char *)*(int **)(e + 0x80 + j * 4) + 0x15C))[0x8 / 4] > 0) {
                    do {
                        char *base = (char *)(k * 0x50) + (*(int **)((char *)objs[j] + 0x15C))[0x830 / 4];
                        *(float *)(base + 0x28) = arg0;
                        *(float *)(base + 0x24) = arg0;
                        *(float *)(base + 0x20) = arg0;
                        k++;
                    } while (k < (*(int **)((char *)*(int **)(e + 0x80 + j * 4) + 0x15C))[0x8 / 4]);
                }
            }
        }
        e += 0x290;
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_SetParentOfGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_SetParentOfGObjWithLocalRotationFlag);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_SetLocalizeGeometry);

extern int D_0062BF58;
extern int D_0062BF5C;
extern void resetmallocseki(int node);

void stage_KillPlayBgAnimationIfOverMaxCount(int *a0) {
    int node = *a0;
    if (node != 0) {
        int next = *(int *)(node + 0x10);
        if (next != 0) {
            *(int *)(next + 0x14) = *(int *)(node + 0x14);
        } else {
            D_0062BF58 = *(int *)(node + 0x14);
            node = *a0;
        }
        {
            int prev = *(int *)(node + 0x14);
            if (prev != 0) {
                *(int *)(prev + 0x10) = *(int *)(node + 0x10);
            }
        }
        if (D_0062BF58 != 0) {
            *(int *)(D_0062BF58 + 0x10) = 0;
        }
        {
            int arg = *a0;
            D_0062BF5C = D_0062BF5C - 1;
            resetmallocseki(arg);
        }
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_CheckAnimationFrameIn);

extern void font_GetWidth(void);

void func_0012A950(void) {
    font_GetWidth();
}

extern int D_0062BF54;
extern char D_0066DBD8[];
extern char D_00550128[];
extern char D_0054FFA8[];
extern char D_0062BF08[];
extern void debug_StdPrintfDummy();
extern int bga_SetCamFrame(int a0);
extern int font_CheckAlign(int a0);
extern void func_001AAD00(void *a0, int a1);
extern void __assert(void *a0, int a1, void *a2);

int func_0012A958(int a0) {
    int count = D_0062BF54;
    int i = 0;
    char *e = (char *)D_0066DBD8;
    if (count > 0) {
        do {
            int *entry1 = *(int **)(e + 0x280);
            if (a0 == entry1[0x58 / 4]) {
                int mode = *(int *)(e + 0x28C) >> 30;
                switch (mode) {
                    case 0:
                        return bga_SetCamFrame(*(int *)(e + 0x284));
                    case 1:
                        return font_CheckAlign(*(int *)(e + 0x288));
                }
            }
            i++;
            e += 0x290;
        } while (i < count);
    }
    debug_StdPrintfDummy(D_00550128);
    func_001AAD00(D_0054FFA8, 0x345);
    __assert(D_0054FFA8, 0x345, D_0062BF08);
    return 0;
}

extern int bga_CheckAnimationFinish(int a0, int a1, int a2);
extern int func_001F7578(int a0, int a1, int a2);

int func_0012AA28(int a0, int a1, int a2) {
    int i;
    char *e = (char *)D_0066DBD8;
    for (i = 0; i < D_0062BF54; i++, e += 0x290) {
        int *entry1 = *(int **)(e + 0x280);
        if (a0 == entry1[0x58 / 4]) {
            int mode = *(int *)(e + 0x28C) >> 30;
            switch (mode) {
                case 0:
                    return bga_CheckAnimationFinish(*(int *)(e + 0x284), a1, a2);
                case 1:
                    return func_001F7578(*(int *)(e + 0x288), a1, a2);
            }
        }
    }
    return -1;
}


extern int D_0062BF54;
extern char D_0066DBD8[];

void func_0012AAB8(int key, int a1)
{
    int count = *(volatile int *)&D_0062BF54;
    int i;
    char *e = (char *)D_0066DBD8;
    for (i = 0; i < count; i++, e += 0x290) {
        int *p = *(int **)(e + 0x280);
        if (key == p[0x58 / 4]) {
            p[0x50 / 4] = a1;
            p = &(*((volatile int *)(&D_0062BF54)));
            count = *p;
        }
    }
}


/* parked: needs real matching. See tough_nuts/func_0012AB00/notes.md */
void func_0012AB00(int target, int val)
{
    int n = D_0062BF54;
    char *p = (char *)D_0066DBD8;
    int i;
    if (n <= 0) return;
    i = n;
    do {
        int *entry1 = *(int **)(p + 0x280);
        if (target == entry1[0x58 / 4]) {
            float **entry2 = *(float ***)(p + 0x284);
            ((float *)entry2)[0x1C / 4] = (float)val;
        }
        p += 0x290;
    } while (--i);
}


struct B8 { char _b[8]; };

void func_0012AB48(int a0, void *a1) {
    int i;
    int one = 1;
    char *e = D_0066DBD8;
    for (i = 0; i < D_0062BF54; i++) {
        if (a0 == *(int *)(*(char **)(e + 0x280) + 0x58)) {
            *(struct B8 *)(*(char **)(*(char **)(e + 0x284) + 0x24) + 0x20) = *(struct B8 *)a1;
            *(int *)(*(char **)(*(char **)(e + 0x284) + 0x24) + 0x28) = one;
        }
        e += 0x290;
    }
}

extern char D_0066DBD8[];
extern int D_0062BF54;

typedef struct { char _b[8]; } Blob8;

void func_0012ABB0(int a0, void *a1, int a2) {
    int i;
    char *e = D_0066DBD8;
    for (i = 0; i < D_0062BF54; i++) {
        if (a0 == *(int *)(*(char **)(e + 0x280) + 0x58)) {
            *(Blob8 *)(*(char **)(*(char **)(e + 0x284) + 0x24) + 0x20) = *(Blob8 *)a1;
            *(int *)(*(char **)(*(char **)(e + 0x284) + 0x24) + 0x28) = a2;
        }
        e += 0x290;
    }
}


/* recovered struct shapes */
typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
    unsigned long long f_20;  /* 0x20 */
    unsigned long long f_28;  /* 0x28 */
    unsigned long long f_30;  /* 0x30 */
    unsigned long long f_38;  /* 0x38 */
} S_0054FF20;

typedef struct {
    unsigned int       f_40;  /* 0x40 */
    unsigned int       f_44;  /* 0x44 */
    unsigned int       f_48;  /* 0x48 */
    unsigned char      f_4C;  /* 0x4C */
    unsigned int       f_54;  /* 0x54 */
} S_005F88A8;  /* stride 0x5C */

typedef struct {
    unsigned int       f_280;  /* 0x280 */
    unsigned int       f_284;  /* 0x284 */
    unsigned int       f_28C;  /* 0x28C */
} S_0066DBD8;  /* stride 0x290 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0066DE58;  /* stride 0x-1 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_002725B0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054FDA4;  /* stride 0x10 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0054FD40;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0054FD70;  /* stride 0x4 */

/* end struct shapes */
