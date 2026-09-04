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

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", func_001971B0);


INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", queenBeforeFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", func_001976B0);

extern void BeforeFunc2(void *a0, void *a1);
extern void GetOrientOfWallOfGObj(void *a0, void *a1);
extern int actBoyRun(void *a0, void *a1);
extern void iosPadActRequest(void *a0, void *a1, int a2, int a3, int a4, int a5);
extern void iosPadNormalizeStick(void *a0);
extern int iosPadStickCameraCoord(void *a0, int a1, int a2, void *a3);
extern float D_00629360;
extern void *D_00629E00;
extern void *D_00629E10;

void func_00197DE0(void *a0) {
    char *ctrl = *(char **)((char *)a0 + 0x164);
    if (a0 == D_00629E00) {
        char *p2C8 = ctrl + 0x2C8;
        char *p328 = ctrl + 0x328;
        int buf[4];
        iosPadStickCameraCoord(p2C8, 0, 0, ctrl + 0x1D8);
        iosPadNormalizeStick(p2C8);
        iosPadActRequest(p2C8, p328, 0, 2, 2, 0);
        GetOrientOfWallOfGObj(buf, a0);
        *(int *)(ctrl + 0x330) = actBoyRun(buf, p328);
        if (*(float *)(ctrl + 0x33C) > D_00629360) {
            BeforeFunc2(ctrl + 0x100, p328);
        }
    } else if (a0 == D_00629E10) {
        iosPadStickCameraCoord(ctrl + 0x2C8, 0, 1, ctrl + 0x1D8);
    } else {
        iosPadStickCameraCoord(ctrl + 0x2C8, 0, 1, ctrl + 0x1D8);
    }
}


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
extern char func_001976B0[];
extern void QueenBallRadius();
extern void queenBeforeFunc();

void QueenBarrierDL(void *self)
{
    void *r = actInitialize_q(self);
    actInitialize_ext_charcter(self);
    _ACTWait(1);
    actCreateSubThread(func_001976B0, 0x14);
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

void QueenBallRadius(void *volatile a0) {
    int p = *(int *)((char *)a0 + 0x15C);
    char *s0 = *(char **)(p + 0x7F0);
    _ACTWait(1);
    while (1) {
        if (*s0 == 0) {
            func_00197DE0(a0);
        }
        _ACTWait(1);
    }
}

extern void _ACTWait(int a0);

void func_00199380(volatile int a0) {
    _ACTWait(1);
    for (;;) {
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/queen", func_001993A8);

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
