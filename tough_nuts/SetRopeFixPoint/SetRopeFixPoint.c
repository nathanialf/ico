#include "common.h"
#include "ico/types.h"

void InitRopeGeo(void) {
}

typedef struct { long long a, b; } Blk10;
typedef struct { long long w[10]; } Blk50;
typedef struct { Blk50 m0, m1; } TwoBlk;
typedef struct { char c[8]; } Blk8;

typedef struct RopeNode_s {
    char _0[0x20];
    float f20, f24, f28;     /* 0x20, 0x24, 0x28 */
    char _2c[0x4];
    int f30;                 /* 0x30 */
    float f34;               /* 0x34 */
    long long f38;           /* 0x38 — flags qword */
    int f40, f44, f48;       /* 0x40, 0x44, 0x48 */
    float f4C;               /* 0x4C */
} RopeNode;                  /* 0x50 */

typedef struct {
    char _0[0x8];
    int f8;                  /* 0x8 */
    int fC;                  /* 0xC — alloc handle */
    int f10;                 /* 0x10 — alloc handle */
    char _14[0x7F4];
    short f808;              /* 0x808 */
    char _80a[0x26];
    struct RopeNode_s *nodes; /* 0x830 — node array */
} RopeSub;

typedef struct {
    int f0;                  /* 0x0 */
    int f4;                  /* 0x4 */
    int f8;                  /* 0x8 */
    int fC;                  /* 0xC */
    int f10;                 /* 0x10 */
} RopeFix;                   /* 0x14 */

extern char D_004C20F0[];
extern char D_004C20F0_2d[][0x50] __asm__("D_004C20F0");
extern char D_006128D0[];
extern char D_006128E0[];
extern char D_00612920[];
extern char D_00612930[];
extern char D_00612940[];
extern char D_0062D720[];
extern float D_006296A0;
extern int D_0062A310;
extern int D_0062A324;

extern void *iosFree(int a0, int a1, char *a2, int a3);
extern void iosMallocCheckLeak2(int a0);
extern void debug_StdPrintfDummy(char *a0, ...);
extern void func_001AAD00(char *a0, int a1);
extern void __assert(char *a0, int a1, char *a2);
extern int func_00105078(void);
extern void sceVu0UnitMatrix(int a0);
extern void func_00105108(float a0, float a1, float a2);
extern void MatrixDrive_RotMatrixY(int a0);
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);
extern int ClipWallBoxStop(void *a0);
extern int bind2(void *a0);

void *SetRopeFixPoint(void *a0, void *a1) {
    char *p = (char *)a1;
    RopeSub *r = (RopeSub *)*(int *)((char *)a0 + 0x15C);
    char *b;
    char *b2;
    RopeFix *s;
    int n;
    char m0[0x20];
    char res[0xC0];

    s = (RopeFix *)iosFree(D_0062A310, 0x14, D_006128D0, 0x26);
    b = (char *)iosFree(D_0062A310, 0xA0, D_006128D0, 0x27);
    b2 = b + 0x50;

    ((TwoBlk *)b)->m0 = ((TwoBlk *)D_004C20F0)->m0;
    ((TwoBlk *)b)->m1 = ((TwoBlk *)D_004C20F0)->m1;

    {
        float d28;
        *(float *)(b + 0x20) = *(float *)(p + 0x00);
        *(float *)(b + 0x24) = *(float *)(p + 0x04);
        *(float *)(b + 0x28) = *(float *)(p + 0x08);
        d28 = *(float *)(p + 0x28);
        *(float *)(b + 0x14) = d28;
        *(float *)(b + 0x40) = *(float *)(p + 0x20);
        n = (int)(*(float *)(p + 0x24) / d28);
    }
    *(int *)(b + 0x00) = n;
    if (n == 0) {
        debug_StdPrintfDummy(D_006128E0);
        func_001AAD00(D_006128D0, 0x33);
        __assert(D_006128D0, 0x33, D_0062D720);
    }

    if (*(float *)(p + 0x10) != 0.0f) {
        *(Blk10 *)(m0 + 0x00) = *(Blk10 *)(D_00612920);
        *(Blk10 *)(m0 + 0x10) = *(Blk10 *)(D_00612930);
        sceVu0UnitMatrix(func_00105078());
        func_00105108(*(float *)(p + 0x00), *(float *)(p + 0x04) + 10.0f,
                      *(float *)(p + 0x08));
        MatrixDrive_RotMatrixY((short)(int)(*(float *)(p + 0x14) * D_006296A0));
        sceVu0ApplyMatrix(res + 0x00, func_00105078(), m0 + 0x00);
        sceVu0ApplyMatrix(res + 0x10, func_00105078(), m0 + 0x10);
        ClipWallBoxStop(res + 0x00);
        if (*(int *)(res + 0x88) == 0) {
            debug_StdPrintfDummy(D_00612940);
            func_001AAD00(D_006128D0, 0x45);
            __assert(D_006128D0, 0x45, D_0062D720);
        }
        *(Blk8 *)&s->f8 = *(Blk8 *)(res + 0x80);
        s->f4 = 1;
        s->f10 = *(int *)(res + 0x88);
    } else {
        s->f8 = 0;
        s->fC = 0;
        s->f10 = 0;
        s->f4 = 0;
    }

    if (r->fC != 0) {
        iosMallocCheckLeak2(r->fC & 0xFFFFFFF);
    }
    if (r->f10 != 0) {
        iosMallocCheckLeak2(r->f10 & 0xFFFFFFF);
    }
    r->fC = 0;
    r->f10 = 0;
    r->fC = (int)iosFree(D_0062A324, (*(int *)(b + 0x00) - 1) << 6, D_006128D0, 0x52);
    r->f10 = (int)iosFree(D_0062A324, (*(int *)(b + 0x00) - 1) << 4, D_006128D0, 0x52);
    r->f8 = *(int *)(b + 0x00) - 1;
    if (r->nodes != 0) {
        iosMallocCheckLeak2((int)r->nodes & 0xFFFFFFF);
    }
    r->nodes = (RopeNode *)iosFree(D_0062A324, (*(int *)(b + 0x00) - 1) * 0x50, D_006128D0, 0x52);
    {
        int i;
        RopeNode *nd = r->nodes;
        for (i = 0; i < *(int *)(b + 0x00) - 1; i++) {
            nd[i].f38 &= ~1LL;
            nd[i].f38 &= ~2LL;
            nd[i].f40 = 0;
            nd[i].f44 = 0;
            nd[i].f38 &= ~4LL;
            nd[i].f48 = 0;
            nd[i].f4C = 1.0f;
            nd[i].f28 = 1.0f;
            nd[i].f30 = 0;
            nd[i].f34 = 1.0f;
            *(short *)((char *)&nd[i] + 0x3A) = 0;
            nd[i].f20 = 1.0f;
            nd[i].f24 = 1.0f;
        }
    }
    r->f808 = 2;
    s->f0 = bind2(b);
    {
        RopeNode *e = r->nodes;
        e->f20 = 1.0f;
        *(int *)((char *)e + 0x00) = 0;
        e->f28 = 1.0f;
        e->f24 = 1.0f;
        *(int *)((char *)e + 0x08) = 0;
        *(int *)((char *)e + 0x04) = 0;
    }
    return s;
}


extern void MatrixDrive_TurnObjectMatrix(int a0, void *a1);

void HoldRope(void *a0, void *a1) {
    Obj7F0 *q = GOBJ_SUB(a0)->p_7F0;
    int *r = *(int **)q;
    int *s = *(int **)r;
    MatrixDrive_TurnObjectMatrix((int)((char *)s + 0x20), a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", ropeGeo);

extern int func_00105078(void);
extern void sceVu0UnitMatrix(int a0);
extern void func_0023FE08(int a0, int a1, int a2);
extern void func_001C1560(int a0, int a1, int a2);

void RopeDL(char *a0)
{
    char *q = *(char **)(*(char **)(a0 + 0x15C) + 0x7F0);
    sceVu0UnitMatrix(func_00105078());
    {
        char *p = *(char **)(a0 + 0x15C);
        if (*(int *)p != 0) {
            int r1 = func_00105078();
            char *p2 = *(char **)(a0 + 0x15C);
            char *sub = *(char **)(*(int *)p2 + 0x15C);
            int addr = *(int *)(sub + 0xC) + *(int *)(p2 + 4) * 0x40;
            func_0023FE08(r1, addr, func_00105078());
        }
    }
    func_001C1560(*(int *)q, 0, func_00105078());
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", CheckRopeUpperWallClimbable);

int ReleaseRope(int a0, void *a1) {
    return GOBJ_SUB(a1)->p_7F0->f_4;
}
