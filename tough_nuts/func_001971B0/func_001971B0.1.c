#include "common.h"
#define flags (*(char **)(*(char **)(self + 0x15C) + 0x7F0))

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

extern void GatherEffect_Proc(int a0, void *a1, void *a2, void *a3, void *a4, float a5);
extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void debug_StdPrintfDummy(char *a0, ...);
extern char D_002724B0[];
extern char D_00556780[];
extern char D_00556790[];
extern void scale_m34(void);

typedef struct { char _b[0x20]; } QBlk32;
typedef struct { float x, y, z, w; } QVec;
typedef struct { int type; void *arg; } QEnt;

void func_001971B0(char *self) {
    float buf[8];
    int *list = (int *)(self + 0x54);
    char *p164 = *(char **)(self + 0x164);
    char *fl = flags;
    int i = 0;

    if (i < list[1]) {
        QEnt *entries = (QEnt *)(self + 0x5C);
        do {
            switch ((unsigned int)(short)entries[i].type) {
            case 0x2D:
                fl[0] = 1;
                break;
            case 0x2E:
                fl[0] = 0;
                break;
            case 0xD:
                debug_StdPrintfDummy(D_00556780);
                fl[2] = 1;
                break;
            case 0x12:
                {
                    int *r = *(int **)(D_00629DE4 + 0x164);
                    void *m = *(void **)((char *)r + 0x130);
                    debug_StdPrintfDummy(D_00556790, m);
                    if (entries[i].arg != 0 && m != 0) {
                        GetRootMatrixByDObj(buf, entries[i].arg);
                        GetRootMatrixByDObj(buf + 4, m);
                        GatherEffect_Proc(0xC, buf, D_002724B0, buf + 4, scale_m34, 2.5f);
                    }
                }
                break;
            }
            i++;
        } while (i < list[1]);
    }
    list[1] = 0;
    *(QBlk32 *)(p164 + 0x610) = *(QBlk32 *)((char *)(*(int *)(self + 0x15C)) + 0x170);
}


INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", queenBeforeFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", func_00197DE0);

extern void *D_0062A310;
extern char D_00556850[];
extern char D_006CDC10[];
extern char D_00287380[], D_00288A10[], D_00287E80[];
extern void *iosFree(void *a0, int a1, char *a2, int a3);
extern int memset(void *a0, int a1, int a2);
extern int DispCloth4D(void *a0, void *a1, void *a2);
extern void func_001E1A18(void *a0, int a1, int a2, int a3, int a4, int a5);
extern void func_001D1ED8(void *a0, int a1);
extern void actInitialize(void *a0);
extern void actInitialize_ext_charcter(void *a0);

void *func_00197EE0(void *self) {
    int *p = *(int **)((char *)self + 0x15C);
    void *r = iosFree(D_0062A310, 0x18, D_00556850, 0x2C5);
    int i;
    int t;
    memset(r, 0, 0x18);
    for (i = 3; i >= 0; i--) {
        ((int *)D_006CDC10)[i] = 0;
    }
    *(int *)((char *)r + 0xC) = 1;
    *(int *)((char *)r + 0x10) = DispCloth4D(self, D_00287380, D_00288A10);
    t = DispCloth4D(self, D_00287E80, 0);
    *(void **)((char *)p + 0x7F0) = r;
    *(int *)((char *)r + 0x14) = t;
    func_001E1A18(self, 0x820, 0x82E, 0xC, 0x18, 0x3F5);
    func_001D1ED8(self, 2);
    actInitialize(self);
    actInitialize_ext_charcter(self);
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", subQueenBrainMain);

extern void GetClothAnimation(int a0, int a1, int a2);
extern void func_0010F068(void);
extern void func_0010F048(int a0);

void func_00198080(char *a0) {
    char *cloth;
    int x;
    func_0010F068();
    func_0010F048((int)a0);
    cloth = *(char **)(*(char **)(a0 + 0x15C) + 0x7F0);
    if (*(int *)(cloth + 0xC) != 0) {
        GetClothAnimation(*(int *)(cloth + 0x10),
                          *(int *)(*(char **)(a0 + 0x15C) + 0x834) + 0x40,
                          *(int *)(*(char **)(a0 + 0x15C) + 0x834));
    }
    x = *(int *)(*(char **)(a0 + 0x15C) + 0x834);
    GetClothAnimation(*(int *)(cloth + 0x14), x + 0x40, x);
}

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

extern void *actInitialize_q(void *a0) __asm__("actInitialize");
extern void _ACTWait(int a0);
extern void actCreateSubThread(void *entry, int prio);
extern int ExecMotionOrient(void *a0, int a1, void *a2);
extern char D_001976B0[];
extern void QueenBallRadius();
extern void queenBeforeFunc();

void QueenBarrierDL(void *self)
{
    void *r = actInitialize_q(self);
    actInitialize_ext_charcter(self);
    _ACTWait(1);
    actCreateSubThread(D_001976B0, 0x14);
    actCreateSubThread((void *)QueenBallRadius, 0x15);
    actCreateSubThread((void *)queenBeforeFunc, 0x15);
    *(int *)((char *)r + 0x110) = ExecMotionOrient(self, 0xEC, (char *)r + 0x610);
    *(int *)(*(int *)((char *)self + 0x15C) + 0x7C) = 1;
}

extern void *isysGObjSearchFromObjLayoutID(int id);
extern void *isysGObjSearchFromObjKindID_next(void *a0);

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
        o = isysGObjSearchFromObjKindID_next(o);
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

int QueenInqDead(void) {
    int ret = 0;
    void *obj = isysGObjSearchFromObjLayoutID(0x2E);
    int *p = *(int **)((char *)obj + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    if (q[1] > 0 || q[2] > 0)
        ret = 1;
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", QueenBoysWeaponPower);

extern void *D_0062A310;
extern char D_00556850[];
extern void *iosFree(void *a0, int a1, char *a2, int a3);
extern int memset(void *a0, int a1, int a2);
extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void actInitialize(void *a0);
extern void actInitialize_ext_charcter(void *a0);
extern void queen_barrier_set_damage(void);

void *QueenBarrierRadius(void *self) {
    int *p = *(int **)((char *)self + 0x15C);
    void *r = iosFree(D_0062A310, 0x30, D_00556850, 0x3B5);
    memset(r, 0, 0x30);
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
extern int memset(void *a0, int a1, int a2);
extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void actInitialize(void *a0);
extern void actInitialize_ext_charcter(void *a0);

void *InitQueenBarrierGeo(void *self) {
    int *p = *(int **)((char *)self + 0x15C);
    void *r = iosFree(D_0062A310, 0x20, D_00556850, 0x4CE);
    *(void **)((char *)p + 0x7F0) = r;
    memset(r, 0, 0x20);
    *(int *)((char *)r + 0x14) = 0;
    GetRootMatrixByDObj(r, self);
    actInitialize(self);
    actInitialize_ext_charcter(self);
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", QueenBallRadius);

extern int D_0062C0CC;
extern char D_005568E0[];
extern void debug_StdPrintfDummy(char *a0, ...);

void queenBallBeforeFunc(void) {
    D_0062C0CC = 0x3C;
    debug_StdPrintfDummy(D_005568E0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", InitQueenBallGeo);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00556830;  /* stride 0x4 */

/* end struct shapes */
