#include "common.h"
#include "ico/types.h"

/* actressLight 0x164 actor-state view (local) */
typedef struct {
    char      _0[0x20];
    long long f_20;   /* 0x20 */
    char      _28[0x8];
    int       f_30;   /* 0x30 */
    char      _34[0x58];
    int       f_8C;   /* 0x8C */
} ALState;
typedef struct { float m[4]; } Vec4;
typedef struct { float m[16]; } Mtx44;

extern void SetAP1DeadStatus(int a0, int a1);

extern GObj *D_00629DE4;
extern void GetRootMatrixByDObj(void *out, GObj *g);
extern void MatrixDrive_TransMatrix(void *out, void *src);
extern void func_00118A70(void *out, void *m, void *v);
extern void MatrixDrive_TurnObjectMatrix(void *dst, void *src);

void SetActressLight(GObj *a0) {
    Vec4 r;
    Mtx44 m;
    Vec4 v;
    char *o = (char *)GOBJ_SUB(a0)->p_7F0;
    int *p10 = (int *)(o + 0x10);
    int *p60 = (int *)(o + 0x60);
    GetRootMatrixByDObj(&r, D_00629DE4);
    MatrixDrive_TransMatrix(&m, o + 0x230);
    func_00118A70(&v, &m, &r);
    MatrixDrive_TurnObjectMatrix(o + 0x30, &v);
    p10[1] = 0;
    *(int *)(o + 0x10) = 0;
    MatrixDrive_TurnObjectMatrix(o + 0x80, &v);
    *(int *)(o + 0x60) = 0;
    p60[1] = 0;
}

extern int walkMot(GObj *a0, int a1);
extern float D_0062942C;

int func_001B7E50(GObj *a0) {
    char *o = (char *)GOBJ_SUB(a0)->p_7F0;
    int r = walkMot(a0, 0);
    if (r == -1) {
        float f = *(float *)(o + 0x1C8) + D_0062942C;
        *(int *)(o + 0x1C0) = 0;
        *(int *)(o + 0x1C4) = 0;
        *(float *)(o + 0x1C8) = f;
        if (1.0f < f) {
            *(int *)(o + 0x64) = 0;
            *(int *)(o + 0x10) = 2;
            *(int *)(o + 0x14) = 0;
            *(int *)(o + 0x60) = 2;
            return 0;
        }
        return 3;
    }
    return r;
}

extern short D_0062C1E4, D_0062C1E6, D_0062C1F0;
extern float D_0062C1E0, D_0062C1EC;
extern int AP1BeforeFunc(GObj *self, int a1);
extern int hitProc(GObj *self, int a1);

int func_001B7ED8(GObj *a0) {
    GObj *self = a0;
    ALState *st = (ALState *)self->p_164;
    short r3;
    int r2, r5;

    if ((int)(st->f_20 << 25 >> 32) & 1) {
        r3 = D_0062C1E6;
        goto Lclamp;
    }
    r2 = st->f_8C;
    if (!(D_0062C1E0 < 500.0f)) goto L7FD8;
    if (r2 != 0) {
        if (AP1BeforeFunc(self, 1) != 0) return 1;
    }
    if (100.0f < D_0062C1EC) {
        if (AP1BeforeFunc(self, 1) != 0) return 1;
    }
    r2 = D_0062C1E4;
    if (r2 < 0x4000 && 300.0f < D_0062C1E0) {
        r3 = D_0062C1E6;
        if (r3 < 0x1001) {
            r5 = (short)(r3 < -0x1000 ? -0x1000 : r3);
        } else {
            r5 = 0x1000;
        }
        goto Lhit;
    }
    if (AP1BeforeFunc(self, 1) != 0) return 1;
    r2 = st->f_8C;
L7FD8:
    if (r2 != 0) {
        if (D_0062C1EC < 50.0f) {
            r3 = D_0062C1F0;
            goto Lclamp;
        }
        if (AP1BeforeFunc(self, 1) != 0) return 1;
    }
    if (!(D_0062C1EC < 100.0f)) goto L8060;
    r3 = D_0062C1E6;
Lclamp:
    if (r3 < 0x801) {
        r5 = (short)(r3 < -0x800 ? -0x800 : r3);
    } else {
        r5 = 0x800;
    }
Lhit:
    hitProc(self, r5);
    return -1;
L8060:
    return AP1BeforeFunc(self, 1) ? 1 : -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/actressLight", func_001B8090);

extern void *D_004BA2B8[];
extern void debug_assertMessage(void *a0);
void func_001B8408(void *a0) {
    ALState *p = *(ALState **)((char *)a0 + 0x164);
    debug_assertMessage(D_004BA2B8[p->f_30]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/actressLight", func_001B8428);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/actressLight", func_001B8470);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/actressLight", func_001B84F8);

void func_001B88B8(int a0) {
    SetAP1DeadStatus(a0, 5);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/actressLight", func_001B88C0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/actressLight", func_001B8908);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/actressLight", func_001B8BD8);

int func_001B8D08(void *a0) {
    int *p = *(int **)((char *)a0 + 0x164);
    long long v = ((unsigned int *)p)[7];
    return ((int)v & 1) ^ 1;
}

void func_001B8D28(int **a0, int a1) {
    int *p = a0[0x59];
    p[0x22] = a1;
}

void func_001B8D38(int **a0, int a1) {
    int *p = a0[0x59];
    p[0x23] = a1;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_004BA2B8;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_004BA2A0;  /* stride 0x4 */

/* end struct shapes */
