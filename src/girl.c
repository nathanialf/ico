#include "common.h"

extern int D_0063B250;
extern int D_0063B254;
extern int D_0063B258;
extern int D_0063B25C;
extern char D_0028FF30[];
extern int GetSkeltonFocusNode(char *obj, int kind);
extern void SetQuaternionByAxisRotateV(void *self, short ang, void *axis);
extern void GetCloth4D(void *cloth, float x, float y);
extern void GetCloth4DWithTight(void *cloth, float x, float y, float z, float w, void *a1,
                                void *a2);

/* census: sugipon/src/girl.c:706 `execClothes` (a TU-static; the name here is
 * splat's placeholder, which is what this repo's symbol table carries). */
void func_001DD128(char *gobj)
{
    int q[4];
    char *w;
    int n;

    n = GetSkeltonFocusNode(gobj, 35);
    w = *(char **)(*(char **)(gobj + 0x15C) + 0x830);
    SetQuaternionByAxisRotateV(q, -D_0063B258 * 16, D_0028FF30);
    if (*(void **)(w + 0x18) != 0) {
        *(int *)(*(char **)(w + 0x18) + 0x2F8) = D_0063B25C;
    }
    switch (*(int *)(w + 0xC)) {
    default:
    case 1:
        if (*(void **)(w + 0x10) != 0) {
            GetCloth4D(*(void **)(w + 0x10), 4.0f, 0.98f);
        }
        if (*(void **)(w + 0x14) != 0) {
            GetCloth4D(*(void **)(w + 0x14), 4.0f, 0.98f);
        }
        if (*(void **)(w + 0x18) != 0) {
            GetCloth4DWithTight(*(void **)(w + 0x18), D_0063B254 * 0.002f, 1.0f, D_0063B250 * 0.01f,
                                1.0f, *(char **)(*(char **)(gobj + 0x15C) + 0x10) + n * 16, q);
        }
        break;
    case 2:
        if (*(void **)(w + 0x10) != 0) {
            GetCloth4D(*(void **)(w + 0x10), 0.0f, 0.98f);
        }
        if (*(void **)(w + 0x14) != 0) {
            GetCloth4D(*(void **)(w + 0x14), 4.0f, 0.98f);
        }
        if (*(void **)(w + 0x18) != 0) {
            GetCloth4DWithTight(*(void **)(w + 0x18), D_0063B254 * 0.002f, 1.0f, D_0063B250 * 0.01f,
                                1.0f, *(char **)(*(char **)(gobj + 0x15C) + 0x10) + n * 16, q);
        }
        break;
    case 0:
        break;
    }
    if (*(int *)(w + 0x4) != 0) {
        if (*(void **)(w + 0x8) != 0) {
            GetCloth4D(*(void **)(w + 0x8), 3.0f, 0.98f);
        }
    }
    if (*(int *)(w + 0x1C) != 0) {
        if (*(void **)(w + 0x20) != 0) {
            GetCloth4D(*(void **)(w + 0x20), 4.0f, 0.98f);
        }
    }
}

extern int GetSkeltonFocusNode(char *obj, int kind);
extern void *MatrixDrive_GetMatrix(void);
extern void CopyMatrix(void *dst, void *src);
extern void MatrixDrive_ScaleMatrix(float x, float y, float z);
extern void reg_DispAccessoryWithShadow(char *o, char *src);

/* census: sugipon/src/girl.c:763 `dispCrown` (a TU-static; the name here is
 * splat's placeholder, which is what this repo's symbol table carries). */
void func_001DD340(char *gobj, char *acc)
{
    char *w;
    int n;

    w = *(char **)(*(char **)(gobj + 0x15C) + 0x830);
    n = GetSkeltonFocusNode(gobj, 35);
    CopyMatrix(MatrixDrive_GetMatrix(), *(char **)(*(char **)(gobj + 0x15C) + 0xC) + n * 0x40);
    MatrixDrive_ScaleMatrix(1.1111112f, 1.1111112f, 1.1111112f);
    if (*(int *)(w + 0x28) != 0) {
        CopyMatrix(*(char **)(*(char **)(w + 0x2C) + 0xC), MatrixDrive_GetMatrix());
        CopyMatrix(*(char **)(*(char **)(w + 0x30) + 0xC), MatrixDrive_GetMatrix());
        reg_DispAccessoryWithShadow(*(char **)(w + 0x30), *(char **)(gobj + 0x15C));
        reg_DispAccessoryWithShadow(*(char **)(w + 0x2C), *(char **)(gobj + 0x15C));
    } else {
        CopyMatrix(*(char **)(acc + 0xC), MatrixDrive_GetMatrix());
        reg_DispAccessoryWithShadow(acc, *(char **)(gobj + 0x15C));
    }
}

extern void DispCloth4D(void *cloth, void *a1, void *a2);
extern void DispCloth4DWithAdd(void *cloth, void *a1, void *a2);
extern void func_001DD340(char *gobj, char *acc);

/* census: sugipon/src/girl.c:787 `dispClothes` (a TU-static; the name here is
 * splat's placeholder). */
void func_001DD440(char *gobj)
{
    char *w;
    char *x;
    char *y;

    w = *(char **)(*(char **)(gobj + 0x15C) + 0x830);
    x = *(char **)(*(char **)(gobj + 0x15C) + 0x874);
    y = x + 0x40;
    if (*(int *)(w + 0x24) != 0) {
        func_001DD340(gobj, *(char **)(w + 0x24));
    }
    if (*(int *)(w + 0xC) != 0) {
        if (*(int *)(w + 0x28) != 0) {
            if (*(int *)(w + 0x10) != 0) {
                DispCloth4DWithAdd(*(void **)(w + 0x10), y, x);
            }
            if (*(int *)(w + 0x14) != 0) {
                DispCloth4DWithAdd(*(void **)(w + 0x14), y, x);
            }
        } else {
            if (*(int *)(w + 0x10) != 0) {
                DispCloth4D(*(void **)(w + 0x10), y, x);
            }
            if (*(int *)(w + 0x14) != 0) {
                DispCloth4D(*(void **)(w + 0x14), y, x);
            }
            if (*(int *)(w + 0x18) != 0) {
                DispCloth4D(*(void **)(w + 0x18), y, x);
            }
        }
    }
    if (*(int *)(w + 0x4) != 0) {
        /* Two separate tests, not `>= 642 || < 639`: gcc's fold_range_test
         * merges a disjunction over one operand into `(unsigned)(v - 639) < 3`,
         * which ROM does not have — ROM keeps both `slti`s. */
        if (*(int *)(*(char **)(gobj + 0x15C) + 0x4A0) < 642) {
            if (*(int *)(*(char **)(gobj + 0x15C) + 0x4A0) >= 639) {
                goto skip;
            }
        }
        if (*(int *)(w + 0x8) != 0) {
            DispCloth4D(*(void **)(w + 0x8), y, x);
        }
    skip:;
    }
    if (*(int *)(w + 0x1C) != 0) {
        if (*(int *)(w + 0x20) != 0) {
            DispCloth4D(*(void **)(w + 0x20), y, x);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/girl", InitGirlGeo);

extern char *D_00639EA4;
extern void HandManager(char *gobj);
extern void ExecMotionOrient(char *gobj);
extern void SetActressLight(char *gobj, int a1, int a2, int a3);
extern int CylinderCollision(char *gobj, int no, float r, float h, float y);
extern void iosOmSendMail(void *a0, int a1, void *a2);
extern int ACTGame_FLAG_TETSUNAGI(void);
extern void GirlAct_BoyAndMeCollisionMail(char *gobj);
extern int GetSkeltonFocusNode(char *obj, int kind);
extern void sceVu0SubVector(void *out, void *a, void *b);
extern float sceVu0InnerProduct(void *a0, void *a1);
extern float FSqrt(float a0);
extern void SetMotionPlaySpeedRatio(char *gobj, float ratio);

void GirlGeo(char *a0)
{
    float v[4];
    int n0;
    int n1;
    float len;
    float ratio;
    char *w;

    HandManager(a0);
    ExecMotionOrient(a0);
    SetActressLight(a0, 0x23, 0x2C, 0x1D6);
    if (CylinderCollision(a0, 4, 50.0f, 50.0f, 0.0f)) {
        iosOmSendMail(a0, 6, a0);
    }
    if (CylinderCollision(a0, 1, ACTGame_FLAG_TETSUNAGI() ? 15.0f : 30.0f, 50.0f, 0.3f)) {
        iosOmSendMail(a0, 6, a0);
        GirlAct_BoyAndMeCollisionMail(a0);
    } else {
        w = *(char **)(a0 + 0x15C);
        if (*(int *)(w + 0x310) == 4 && *(int *)(w + 0x7C) != 0 && *(int *)(w + 0x3C8) != 0) {
            n0 = GetSkeltonFocusNode(D_00639EA4, 6);
            n1 = GetSkeltonFocusNode(a0, 0x16);
            sceVu0SubVector(v, *(char **)(*(char **)(D_00639EA4 + 0x15C) + 0xC) + n0 * 64 + 0x30,
                            *(char **)(*(char **)(a0 + 0x15C) + 0xC) + n1 * 64 + 0x30);
            len = FSqrt(sceVu0InnerProduct(v, v));
            if (10.0f < len) {
                ratio = 1.0f - len / 50.0f;
                ratio = ratio < 0.75f ? 0.75f : ratio;
                SetMotionPlaySpeedRatio(D_00639EA4, ratio);
            }
        }
    }
    func_001DD128(a0);
}

extern char D_0061F910[];
extern char D_0061F930[];
extern char D_0061F948[];
extern char D_0061F960[];
extern char D_0061F980[];
extern char D_0061F998[];
extern char D_0061F9B0[];
extern char D_0061F9C8[];
extern void debug_StdPrintfDummy(char *p);
extern void scpGirlHintVoiceReady(int no);
extern void scpGirlHintVoicePlay(void);
extern void scpGirlHintVoiceCancel(void);

void GirlAI(char *a0)
{
    char *work = *(char **)(a0 + 0x15C);
    int mode = *(int *)(work + 0x4A0);
    char *cloth = *(char **)(work + 0x830);
    int hint = *(int *)(work + 0x4C8);

    if (mode == 0x297) {
        if (hint != 0) {
            if (*(int *)(cloth + 0x38) != 0) {
                debug_StdPrintfDummy(D_0061F910);
                scpGirlHintVoiceCancel();
            }
            scpGirlHintVoiceReady(0x65);
            *(int *)(cloth + 0x34) = 1;
            debug_StdPrintfDummy(D_0061F930);
        }
        if (*(int *)(cloth + 0x34) != 0 && *(int *)(cloth + 0x3C) == 0 &&
            47.0f < *(float *)(*(char **)(a0 + 0x15C) + 0x4AC)) {
            scpGirlHintVoicePlay();
            *(int *)(cloth + 0x3C) = 1;
            debug_StdPrintfDummy(D_0061F948);
        }
    }
    if (mode == 0x29A) {
        if (hint != 0) {
            if (*(int *)(cloth + 0x34) != 0) {
                debug_StdPrintfDummy(D_0061F960);
                scpGirlHintVoiceCancel();
            }
            scpGirlHintVoiceReady(0x67);
            *(int *)(cloth + 0x38) = 1;
            debug_StdPrintfDummy(D_0061F980);
        }
        if (*(int *)(cloth + 0x38) != 0 && *(int *)(cloth + 0x40) == 0 &&
            107.0f < *(float *)(*(char **)(a0 + 0x15C) + 0x4AC)) {
            scpGirlHintVoicePlay();
            *(int *)(cloth + 0x40) = 1;
            debug_StdPrintfDummy(D_0061F998);
        }
    }
    if (*(int *)(cloth + 0x34) != 0) {
        if (mode != 0x297 && mode != 0x298) {
            debug_StdPrintfDummy(D_0061F9B0);
            *(int *)(cloth + 0x34) = 0;
            *(int *)(cloth + 0x3C) = 0;
            scpGirlHintVoiceCancel();
        }
    }
    if (*(int *)(cloth + 0x38) != 0) {
        if (mode != 0x29A && mode != 0x29B) {
            debug_StdPrintfDummy(D_0061F9C8);
            *(int *)(cloth + 0x38) = 0;
            *(int *)(cloth + 0x40) = 0;
            scpGirlHintVoiceCancel();
        }
    }
}

extern int matrixptr;
extern void GetRootPosition(void *dst, void *self);
extern void sceVu0TransposeMatrix(void *dst, void *src);
extern void *MatrixDrive_GetMatrix(void);
extern void _UnitMatrix(void *m);
extern void MatrixDrive_TransMatrixV(void *v);
extern void _MulMatrix(void *dst, void *a, void *b);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void MatrixDrive_TransMatrix(float x, float y, float z);
extern void DispWireString(char *s);
extern char *D_004EB420[];

/* static helper the listing places at girl.c line(s) 1082; never emitted out
 * of line, so it has no MAIN.MAP symbol and this name is ours. */
static inline int *getGirlCloth(char *gobj)
{
    return *(int **)(*(char **)(gobj + 0x15C) + 0x830);
}

void debugWireStringGirl(char *a0)
{
    float m[16];
    float pos[4];
    int *cloth = getGirlCloth(a0);

    GetRootPosition(pos, a0);
    sceVu0TransposeMatrix(m, (void *)(matrixptr + 0x80));
    m[3] = m[7] = m[11] = 0.0f;
    _UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrixV(pos);
    _MulMatrix(MatrixDrive_GetMatrix(), MatrixDrive_GetMatrix(), m);
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrix(0.0f, -50.0f, 0.0f);
    DispWireString(D_004EB420[cloth[0]]);
    MatrixDrive_PopMatrix();
}

extern void p2o_DispVU1(int a0);
extern void p2o_SetDefaultEnviroment(int a0);

void GirlDL(int a0)
{
    p2o_SetDefaultEnviroment(a0);
    p2o_DispVU1(a0);
    func_001DD440((char *)a0);
    return debugWireStringGirl((char *)a0);
}

void SetGirlClothDispSwitch(char *a0, int a1, int a2)
{
    char *cloth = (char *)*(int *)(*(int *)(a0 + 0x15C) + 0x830);
    switch (a1) {
    case 0:
        *(int *)(cloth + 0x4) = a2;
        break;
    case 1:
        *(int *)(cloth + 0xC) = a2;
        break;
    case 2:
        *(int *)(cloth + 0x1C) = a2;
        break;
    }
}

void SetGirlHairDispSwitch(char *a0, int a1)
{
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x28) = a1;
}

extern char D_0061F8D0[];
extern char D_0061F8E8[];

typedef struct {
    int unk0;
    int unk4;
    int unk8;
    int unkC;
} GirlClothSetting;

extern GirlClothSetting D_004EB400;
extern GirlClothSetting D_004EB410;
extern int D_0063B250;
extern int D_0063B254;
extern int D_0063B258;
extern int D_0063B25C;

/* static helper the listing places at girl.c line(s) 864-868; never emitted out
 * of line, so it has no MAIN.MAP symbol and this name is ours. */
static inline void setGirlClothParam(GirlClothSetting *p)
{
    D_0063B250 = p->unk0;
    D_0063B254 = p->unk4;
    D_0063B258 = p->unk8;
    D_0063B25C = p->unkC;
}

void setGirlClothSetting(int a0)
{
    if (a0 == 0) {
        debug_StdPrintfDummy(D_0061F8D0);
        setGirlClothParam(&D_004EB400);
    } else {
        debug_StdPrintfDummy(D_0061F8E8);
        setGirlClothParam(&D_004EB410);
    }
}
