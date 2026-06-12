#include "common.h"
#include "ico/types.h"

/* actressLight 0x164 actor-state view (local) */
typedef struct { char _0[0x30]; int f_30; } ALState;
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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/actressLight", func_001B7E50);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/actressLight", func_001B7ED8);

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
