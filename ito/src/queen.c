#include "common.h"

/* Queen 0x7F0 view (local; 0x7F0 target is per-object-type) */
typedef struct { char _0[3]; signed char f_3; int f_4; char _pad8[0xC]; float f_14; } QGeo;

extern void *isysGObjSearchFromObjLayoutID(int id);
extern char *D_00629DE4;
extern void initializeQueenzSword(void *a0);

void scale_m34(void) {
    void *obj = isysGObjSearchFromObjLayoutID(0x2E);
    int *r = *(int **)(D_00629DE4 + 0x164);
    void *next = *(void **)((char *)r + 0x130);
    if (obj != 0) {
        int *p = *(int **)((char *)obj + 0x15C);
        QGeo *q = *(QGeo **)((char *)p + 0x7F0);
        q->f_4++;
    }
    if (next != 0) {
        initializeQueenzSword(next);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", func_001971B0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", queenBeforeFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", func_00197DE0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", func_00197EE0);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", subQueenBrainMain);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", func_00198080);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", InitQueenGeo);

extern void MakeRefractTexture(float a0);

void QueenGeo(void *a0)
{
    int q = *(int *)(*(int *)((char *)a0 + 0x15C) + 0x7F0);
    if (*(signed char *)(q + 0x12) != 0) {
        MakeRefractTexture(1.0f - (float)*(int *)(q + 0x18) / 5.0f);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", QueenDL);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", QueenBarrierGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", QueenBarrierDL);

extern void *isysGObjSearchFromObjLayoutID(int id);
extern void *isysGObjSearchFromObjKindID_begin(void *a0);

void QueenBallGeo(void) {
    void *o1 = isysGObjSearchFromObjLayoutID(0x2E);
    int *p1 = *(int **)((char *)o1 + 0x15C);
    char *q1 = *(char **)((char *)p1 + 0x7F0);
    void *o;
    q1[1] = 1;
    o = isysGObjSearchFromObjLayoutID(0x35);
    while (o != 0) {
        int *p = *(int **)((char *)o + 0x15C);
        char *q = *(char **)((char *)p + 0x7F0);
        q[0x12] = 1;
        o = isysGObjSearchFromObjKindID_begin(o);
    }
}

extern void *isysGObjSearchFromObjLayoutID(int id);

int QueenBallDL(void) {
    void *obj = isysGObjSearchFromObjLayoutID(0x2E);
    int *p = *(int **)((char *)obj + 0x15C);
    QGeo *q = *(QGeo **)((char *)p + 0x7F0);
    return q->f_3;
}

int actQueenStart(void) {
    void *obj = isysGObjSearchFromObjLayoutID(0x2E);
    int *p = *(int **)((char *)obj + 0x15C);
    QGeo *q = *(QGeo **)((char *)p + 0x7F0);
    return q->f_4;
}

float QueenStartAttack(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    QGeo *q = *(QGeo **)((char *)p + 0x7F0);
    return q->f_14;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", QueenInqDead);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", QueenBoysWeaponPower);

extern void *D_0062A310;
extern char D_00556850[];
extern void *iosFree(void *a0, int a1, char *a2, int a3);
extern int func_00260568(void *a0, int a1, int a2);
extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void actInitialize(void *a0);
extern void actInitialize_ext_charcter(void *a0);
extern void queen_barrier_set_damage(void);

void *QueenBarrierRadius(void *self) {
    int *p = *(int **)((char *)self + 0x15C);
    void *r = iosFree(D_0062A310, 0x30, D_00556850, 0x3B5);
    func_00260568(r, 0, 0x30);
    *(void **)((char *)p + 0x7F0) = r;
    *(float *)((char *)r + 0x14) = 300.0f;
    GetRootMatrixByDObj(r, self);
    actInitialize(self);
    actInitialize_ext_charcter(self);
    queen_barrier_set_damage();
    return r;
}

float QueenBarrierInqBreakable(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    QGeo *q = *(QGeo **)((char *)p + 0x7F0);
    return q->f_14 * 100.0f;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", queenBarrierBeforeFunc);

extern void *D_0062A310;
extern char D_00556850[];
extern void *iosFree(void *a0, int a1, char *a2, int a3);
extern int func_00260568(void *a0, int a1, int a2);
extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void actInitialize(void *a0);
extern void actInitialize_ext_charcter(void *a0);

void *InitQueenBarrierGeo(void *self) {
    int *p = *(int **)((char *)self + 0x15C);
    void *r = iosFree(D_0062A310, 0x20, D_00556850, 0x4CE);
    *(void **)((char *)p + 0x7F0) = r;
    func_00260568(r, 0, 0x20);
    *(int *)((char *)r + 0x14) = 0;
    GetRootMatrixByDObj(r, self);
    actInitialize(self);
    actInitialize_ext_charcter(self);
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", QueenBallRadius);

extern int D_0062C0CC;
extern char D_005568E0[];
extern void debug_assertMessage(char *a0);

void queenBallBeforeFunc(void) {
    D_0062C0CC = 0x3C;
    debug_assertMessage(D_005568E0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", InitQueenBallGeo);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00556830;  /* stride 0x4 */

/* end struct shapes */
