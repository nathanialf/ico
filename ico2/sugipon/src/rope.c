#include "common.h"
#include "rope.h"
#include "debug.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "memory.h"
#include "sugiCommon.h"
#include <libvu0.h>

/* kept local: this TU's uses of GetChainCollision do not fit the prototype in clothAnimation.h */
extern float GetChainCollision(void *a0, void *a1, float w);
extern void *D_00639EA4;
extern IosMemPart *D_0063A438;
extern IosMemPart *D_0063A44C;
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_TransMatrix(float x, float y, float z);
extern void MatrixDrive_RotMatrixY(short a);
extern void sceVu0UnitMatrix(void *m);
extern void sceVu0ApplyMatrix(void *d, void *m, void *v);
extern void ClipWall(void *w);
extern int InitChains(void *c);

/* The chain template block the rope copies out of .rodata at 0x004ECEF0: two
   0x50-byte records, copied whole, so the record carries 8-byte alignment. */
typedef struct {
    long long d[10];
} RopeTemplate;

extern RopeTemplate D_004ECEF0[];

typedef struct {
    int a;
    int b;
} RopePair;

/* The chain system record the rope allocates (0xA0 bytes, two template halves). */
typedef struct {
    /* 0x00 */ int n;
    /* 0x04 */ int _04[4];
    /* 0x14 */ float f14;
    /* 0x18 */ int _18[2];
    /* 0x20 */ float f20;
    /* 0x24 */ float f24;
    /* 0x28 */ float f28;
    /* 0x2C */ int _2c[5];
    /* 0x40 */ float f40;
    /* 0x44 */ int _44[23];
} RopeChainSys;

/* The wall-clip request, the same record ico2/omori/src/chain.c hands to
   ClipWall (endpoints at 0x00 and 0x10, hit flag at 0x88); the rope also reads
   the 8 bytes at 0x80. */
typedef struct {
    /* 0x00 */ float from[4];
    /* 0x10 */ float to[4];
    /* 0x20 */ char _20[0x60];
    /* 0x80 */ RopePair out;
    /* 0x88 */ void *hit; /* the wall hit; fieldCollision.c reads it as a pointer */
    /* 0x8C */ char _8c[0x34];
} RopeClipWork;

typedef struct {
    /* 0x00 */ int f0;
    /* 0x04 */ int f4;
    /* 0x08 */ RopePair f8;
    /* 0x10 */ void *f10;
} RopeGeoWork;

void *InitRopeGeo(char *o, const float *p)
{
    RopeChainSys *c;
    char *sub;
    RopeGeoWork *w;
    int i;

    sub = *(char **)(o + 0x15C);
    w = (RopeGeoWork *)iosMallocDebug(D_0063A438, 0x14, __FILE__, 38);
    c = (RopeChainSys *)iosMallocDebug(D_0063A438, 0xA0, __FILE__, 39);

    ((RopeTemplate *)c)[0] = D_004ECEF0[0];
    ((RopeTemplate *)c)[1] = D_004ECEF0[1];
    c->f20 = p[0];
    c->f24 = p[1];
    c->f28 = p[2];
    c->f14 = p[10];
    c->f40 = p[8];
    c->n = (int)(p[9] / c->f14);
    if (c->n == 0) {
        /* "The rope is too short. Change scale-y in the table." (EUC-JP) */
        debug_StdPrintfDummy("ロープの長さが短"
                             "すぎます。表のscale-y"
                             "を変更してくださ"
                             "い。\n");
        debug_assert(__FILE__, 51);
        __assert(__FILE__, 51, "0");
    }

    if (p[4] != 0.0f) {
        sceVu0FVECTOR v0 = {0.0f, 0.0f, -10.0f, 1.0f};
        sceVu0FVECTOR v1 = {0.0f, 0.0f, 10.0f, 1.0f};
        RopeClipWork cw;

        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrix(p[0], p[1] + 10.0f, p[2]);
        MatrixDrive_RotMatrixY(p[5] * 10430.378f);
        sceVu0ApplyMatrix(cw.from, MatrixDrive_GetMatrix(), &v0);
        sceVu0ApplyMatrix(cw.to, MatrixDrive_GetMatrix(), &v1);
        ClipWall(&cw);
        if (cw.hit == 0) {
            /* "Cannot find the wall above the rope. Is the direction wrong, or
               is it placed where there is no wall?" (EUC-JP, in yellow) */
            debug_StdPrintfDummy("\033[33m鎖の上の壁を見"
                                 "付けることができ"
                                 "ません。\n方向が間"
                                 "違っているか、壁"
                                 "が無いところに置"
                                 "いていませんか?\033[m\n");
            debug_assert(__FILE__, 69);
            __assert(__FILE__, 69, "0");
        }
        w->f8 = cw.out;
        w->f10 = cw.hit;
        w->f4 = 1;
    } else {
        w->f8.a = 0;
        w->f8.b = 0;
        w->f10 = 0;
        w->f4 = 0;
    }

    if (*(int *)(sub + 0xC) != 0) {
        iosFree((void *)(*(int *)(sub + 0xC) & 0x0FFFFFFF));
    }
    if (*(int *)(sub + 0x10) != 0) {
        iosFree((void *)(*(int *)(sub + 0x10) & 0x0FFFFFFF));
    }
    *(void **)(sub + 0xC) = 0;
    *(void **)(sub + 0x10) = 0;
    *(void **)(sub + 0xC) = iosMallocDebug(D_0063A44C, (c->n - 1) * 64, __FILE__, 82);
    *(void **)(sub + 0x10) = iosMallocDebug(D_0063A44C, (c->n - 1) * 16, __FILE__, 82);
    *(int *)(sub + 8) = *(int *)c - 1;
    if (*(int *)(sub + 0x870) != 0) {
        iosFree((void *)(*(int *)(sub + 0x870) & 0x0FFFFFFF));
    }
    *(void **)(sub + 0x870) = iosMallocDebug(D_0063A44C, (c->n - 1) * 0x50, __FILE__, 82);
    for (i = 0; i < c->n - 1; i++) {
        {
            char *e = (char *)(i * 80 + (int)*(char **)(sub + 0x870));
            ((DlFlag *)(e + 0x38))->ll &= ~1;
        }
        {
            char *e = (char *)(i * 80 + (int)*(char **)(sub + 0x870));
            ((DlFlag *)(e + 0x38))->ll &= ~2;
        }
        {
            char *e = (char *)(i * 80 + (int)*(char **)(sub + 0x870));
            *(float *)(e + 0x40) = 0.0f;
        }
        {
            char *e = (char *)(i * 80 + (int)*(char **)(sub + 0x870));
            *(float *)(e + 0x44) = 0.0f;
        }
        {
            char *e = (char *)(i * 80 + (int)*(char **)(sub + 0x870));
            *(float *)(e + 0x48) = 0.0f;
        }
        {
            char *e = (char *)(i * 80 + (int)*(char **)(sub + 0x870));
            *(float *)(e + 0x4C) = 1.0f;
        }
        {
            char *e = (char *)(i * 80 + (int)*(char **)(sub + 0x870));
            ((DlFlag *)(e + 0x38))->ll &= ~4;
        }
        {
            char *e = (char *)(i * 80 + (int)*(char **)(sub + 0x870));
            /* float, where the other expansions of this reset write an int: the
               ROM loads the loop bound c->n (an int) ahead of this store, which
               it may do only if the two do not alias */
            *(float *)(e + 0x30) = 0.0f;
        }
        {
            char *e = (char *)(i * 80 + (int)*(char **)(sub + 0x870));
            *(float *)(e + 0x34) = 1.0f;
        }
        {
            char *e = (char *)(i * 80 + (int)*(char **)(sub + 0x870));
            *(short *)(e + 0x3A) = 0;
        }
        {
            char *e = (char *)(i * 80 + (int)*(char **)(sub + 0x870));
            *(float *)(e + 0x20) = 1.0f;
        }
        {
            char *e = (char *)(i * 80 + (int)*(char **)(sub + 0x870));
            *(float *)(e + 0x24) = 1.0f;
        }
        {
            char *e = (char *)(i * 80 + (int)*(char **)(sub + 0x870));
            *(float *)(e + 0x28) = 1.0f;
        }
    }
    *(short *)(sub + 0x84C) = 2;
    w->f0 = InitChains(c);
    *(float *)(*(char **)(sub + 0x870) + 0x20) = *(float *)(*(char **)(sub + 0x870) + 0x24) =
        *(float *)(*(char **)(sub + 0x870) + 0x28) = 1.0f;
    *(int *)(*(char **)(sub + 0x870) + 0x0) = *(int *)(*(char **)(sub + 0x870) + 0x4) =
        *(int *)(*(char **)(sub + 0x870) + 0x8) = 0;
    return w;
}

inline int CheckRopeUpperWallClimbable(int a0, char *a1)
{
    return *(int *)(*(char **)(*(char **)(a1 + 0x15C) + 0x830) + 4);
}

void SetRopeFixPoint(char *a0, void *a1)
{
    CopyVector(**(char ***)(*(char **)(*(char **)(a0 + 0x15C) + 0x830)) + 0x20, a1);
}

/* The actor's 0x15C sub-object slot: the engine stores a different per-actor
   struct pointer in it depending on the actor, so it is a union of pointers.
   (ROM proves the union read: it may-alias the float chain-node writes in
   HoldRope, which a plain typed pointer read would not.) */
typedef union {
    char *b;
    float *f;
    int *i;
} Sub15CRef;

/* kept local: this TU's uses of GetChainNodeID do not fit the prototype in clothAnimation.h */
extern float GetChainNodeID(void *n);
/* kept local: this TU's uses of SetChainExtendedWeight do not fit the prototype in clothAnimation.h */
extern int SetChainExtendedWeight(void *a0, int a1, float f12, float f13);
extern char D_004ECEE0[];

void HoldRope(void *a0, void *a1)
{
    float v[4];
    float u[4];
    void **p = *(void ***)((char *)*(void **)((char *)a0 + 0x15C) + 0x830);
    void **sys = (void **)p[0];
    int n = (int)GetChainNodeID(sys[0]);
    int w1 = SetChainExtendedWeight(sys[2], n, 0.0f, 100.0f);
    int w2 = SetChainExtendedWeight(sys[2], n, 100.0f, 300.0f);

    GetRootPosition(v, a1);
    CopyVector(u, *(char **)((char *)a1 + 0x15C) + 0x130);
    CopyVector((float *)((char *)sys[2] + (w1 * 0x50 + 0x10)) + 12, u);
    CopyVector((float *)((char *)sys[2] + (w2 * 0x50 + 0x10)) + 12, u);
    CopyVector((float *)((char *)sys[2] + (w1 * 0x50 + 0x10)) + 4, v);
    CopyVector((float *)((char *)sys[2] + (w2 * 0x50 + 0x10)) + 4, v);
    CopyVector((float *)((char *)sys[2] + (w1 * 0x50 + 0x10)) + 8, v);
    CopyVector((float *)((char *)sys[2] + (w2 * 0x50 + 0x10)) + 8, v);
    {
        float *q = (float *)((char *)sys[2] + w1 * 0x50);
        q[9] -= 100.0f;
        q[13] -= 100.0f;
    }
    CopyVector(((Sub15CRef *)((char *)a1 + 0x15C))->b + 0x130, D_004ECEE0);
    debug_StdPrintfDummy("HOLD ROPE\n");
}

inline void ReleaseRope(void) {}

/* kept local: this TU's uses of GetChainAnimation do not fit the prototype in clothAnimation.h */
extern void GetChainAnimation(void *sys, int obj, void *mtx);

void ropeGeo(void *a0)
{
    void **obj = *(void ***)((char *)*(void **)((char *)a0 + 0x15C) + 0x830);

    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    if (**(int **)((char *)a0 + 0x15C) != 0) {
        sceVu0MulMatrix(MatrixDrive_GetMatrix(),
                        *(char **)(*(char **)(**(char ***)((char *)a0 + 0x15C) + 0x15C) + 0xC) +
                            (*(int *)(*(char **)((char *)a0 + 0x15C) + 4) << 6),
                        MatrixDrive_GetMatrix());
    }
    GetChainAnimation(obj[0], 0, MatrixDrive_GetMatrix());
}

/* The listing inlines rope.c:215-221 into RopeGeo: the chain-length update
   is a static helper defined above it (its name is not recoverable). */

static inline void ropeChainCollision(void *a0)
{
    void *g = D_00639EA4;
    void **obj = *(void ***)((char *)*(void **)((char *)a0 + 0x15C) + 0x830);
    float m[4];
    float w;

    GetRootPosition(m, g);
    w = GetChainCollision(obj[0], m, 200.0f);
    do {
        if (0.0f < w) {
            *(float *)((char *)*(void **)((char *)g + 0x15C) + 0x618) = w;
        }
    } while (0);
}

inline void RopeGeo(void *a0)
{
    ropeGeo(a0);
    ropeChainCollision(a0);
}

/* kept local: this TU's uses of p2o_SetDefaultEnviroment do not fit the prototype in DisplayP2O.h */
extern void p2o_SetDefaultEnviroment(void *a0);
/* kept local: this TU's uses of p2o_DispVU1DObjMulti do not fit the prototype in DisplayP2O.h */
extern void p2o_DispVU1DObjMulti(void *a0);
/* kept local: this TU's uses of TestDispChainAnimation do not fit the prototype in clothAnimation.h */
extern void TestDispChainAnimation(void *a0);
extern int D_0063B148;

void RopeDL(void *a0)
{
    unsigned short ax;
    unsigned short az;
    char *sub = *(char **)((char *)a0 + 0x15C);
    void **p = *(void ***)(sub + 0x830);
    char *set = (char *)p[0];
    int i;
    int j;
    int n;
    float (*v)[4];

    p2o_SetDefaultEnviroment(a0);
    for (i = 0; i < *(int *)(set + 4); i++) {
        n = *(int *)(*(char **)set + i * 0x50);
        v = (float (*)[4]) * (int *)(*(char **)(set + 8) + i * 0x1A0);
        for (j = 1; j < n; j++) {
            sceVu0UnitMatrix(MatrixDrive_GetMatrix());
            MatrixDrive_TransMatrix(v[j][0], v[j][1], v[j][2]);
            MatrixDrive_GetTurnYAngleXZ(&ax, &az, v[j][0] - v[j - 1][0], v[j][1] - v[j - 1][1],
                                        v[j][2] - v[j - 1][2]);
            MatrixDrive_RotMatrixX(-ax);
            MatrixDrive_RotMatrixZ(-az);
            MatrixDrive_RotMatrixX(-0x8000);
            MatrixDrive_ScaleMatrix(1.0f, 1.0f, 1.0f);
            CopyMatrix(*(char **)(sub + 0xC) + (j * 0x40 - 0x40), MatrixDrive_GetMatrix());
        }
        p2o_DispVU1DObjMulti(sub);
    }
    if (D_0063B148 != 0) {
        TestDispChainAnimation(p[0]);
    }
}
