#include "common.h"
#include "ico/types.h"

/* The packed colour word.  ROM copies it with lwl/lwr + swl/swr, which is
   gcc's unaligned block move: the type is a four-byte record of chars, so
   its alignment is 1 and the compiler cannot use lw/sw. */
typedef struct Rgba {
    unsigned char r, g, b, a;
} Rgba;

typedef struct PointBlur {
    /* 0x00 */ int f0;
    /* 0x04 */ int num;
    /* 0x08 */ void *f8;
    /* 0x0C */ void *fC;
    /* 0x10 */ Rgba *f10;
    /* 0x14 */ Rgba col;
    /* 0x18 */ long long _pad18; /* ROM proves 8-byte struct alignment: the
                                     0x40-byte template copy is ld/sd, not lw/sw */
    /* 0x20 */ float pos[4];
    /* 0x30 */ int dirty;
    /* 0x34 */ char _pad34[0xC];
} PointBlur;

extern int D_0063A06C;
extern int GlobalTimer;
extern char *matrixptr;
extern char D_0028FF30[];
extern void moveDataElements(PointBlur *p);
extern void _ApplyMatrix(void *dst, void *m, void *src);
extern void _SetCurrentMatrix(void *m);
extern void _RotTransPersCurrentMatrix(void *dst, void *src);
extern void _SubVector(void *d, void *a, void *b);
extern void _OuterProduct(void *d, void *a, void *b);
extern void _NormalizeVector(void *d, void *s);
extern void _ScaleVector(void *d, void *s, float k);
extern void _AddVectorXYZ(void *d, void *a, void *b);
extern void _SubVectorXYZ(void *d, void *a, void *b);
extern void _FTOI4Vector(void *d, void *s);
extern void _CopyVector(void *dst, void *src);
extern void _CopyIVector(void *d, void *s);

typedef struct IVec {
    float x, y, z, w;
} IVec;

/* Listing rows 66-70 sit inside UpdatePointBlur's span with no census entry
   and no out-of-line body of their own, so they are a helper above it that
   gcc inlined whole. */
static inline void resetPointBlurTrail(PointBlur *p)
{
    int i;
    Rgba *q;

    for (i = 1; i < p->num; i++) {
        _CopyVector(&((IVec *)p->f8)[i], p->f8);
        _CopyIVector(&((IVec *)p->fC)[i * 2], p->fC);
        _CopyIVector(&((IVec *)p->fC)[i * 2 + 1], &((IVec *)p->fC)[1]);
        q = (Rgba *)(i * 8 + (int)p->f10);
        q[1] = p->f10[0];
        q[0] = q[1];
    }
}

int UpdatePointBlur(PointBlur *p, void *mtx, void *a2, float f)
{
    float a[4];
    float b[4];
    float c[4];
    float scale;
    Rgba *t;

    if (D_0063A06C != 0 || GlobalTimer != 0) {
        p->dirty = 1;
    }
    if (p->dirty == 0) {
        moveDataElements(p);
    }
    _ApplyMatrix(a, matrixptr + 0x80, mtx);
    _SetCurrentMatrix(matrixptr + 0xC0);
    _RotTransPersCurrentMatrix(p->f8, a);
    a[0] = a[0] + f;
    _RotTransPersCurrentMatrix(b, a);
    scale = b[0] - *(float *)p->f8;
    _SubVector(c, (char *)p->f8 + 0x10, p->f8);
    c[2] = 0.0f;
    _OuterProduct(c, c, D_0028FF30);
    _NormalizeVector(c, c);
    _ScaleVector(c, c, scale);
    c[2] = 0.0f;
    _AddVectorXYZ(b, p->f8, c);
    _FTOI4Vector(p->fC, b);
    _SubVectorXYZ(b, p->f8, c);
    _FTOI4Vector((char *)p->fC + 0x10, b);
    t = p->f10;
    t[1] = p->col;
    t[0] = t[1];
    if (p->dirty != 0) {
        resetPointBlurTrail(p);
        p->dirty = 0;
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/enemyParts", InitEnemyEye);
/* InitEnemyEye is still asm and owns the first word of this TU's .lit4 pool
   (VMA 0x006394CC = 1e-5f).  The slot keeps the pool run contiguous and in
   ROM order while the owner is an INCLUDE_ASM; delete this line when
   InitEnemyEye lands in C and writes the literal itself. */
ASM_LIT4_SLOT(D_006394CC, 1e-5f);
INCLUDE_ASM("asm/nonmatchings/src/enemyParts", InitEnemyFootPrint);

/* --- su-b sweep decls --- */
extern char D_0028FF20[];
extern int rand(void);
extern void SetQuaternionByAxisRotateVWithNoRegularize(int *self, short ang, void *axis);
extern void GetMatrixFromQuaternionPos(char *m, char *q, char *pos);

int ExecEnemyFootPrints(char *self)
{
    int q[4];
    int i;
    char *base;

    base = (char *)*(int *)(self + 0xC);
    for (i = 0; i < *(int *)self; i++) {
        char *fp = base + i * 0x20;
        char *dl;
        /* The free marker is a statement of its own, not a constant folded
           into the store below.  ROM materialises it as `addiu $21,$0,-1`
           in THIS block, above all three calls, which costs a callee-saved
           register and its sd/ld pair.  A plain `fp->life = -1;` cannot
           produce that row: emit_move_insn on a `(mem) <- (const_int -1)`
           forces the constant into a register AT the store, so the `li`
           would land inside the `if` block.  The January listing puts the
           row at enemyParts.c:281, which is the line of the
           SetQuaternionByAxisRotateVWithNoRegularize call below, and that
           is where the assignment sits here. */
        int dead;

        if (*(int *)fp < 0) {
            continue;
        }
        dl = (char *)(i * 0x50 + *(int *)(*(char **)(self + 0x4) + 0x870));
        *(float *)(dl + 0x30) = -(float)(*(int *)fp + 1) / 30.0f;
        *(float *)(dl + 0x20) = *(float *)(dl + 0x20) + *(float *)(fp + 0x4);
        *(float *)(fp + 0x4) = *(float *)(fp + 0x4) * 0.9f;
        *(float *)(dl + 0x24) = *(float *)(dl + 0x28) = *(float *)(dl + 0x20);
        dead = -1;
        SetQuaternionByAxisRotateVWithNoRegularize(q, rand(), D_0028FF20);
        GetMatrixFromQuaternionPos((char *)(*(int *)(*(char **)(self + 0x4) + 0xC) + i * 0x40),
                                   (char *)q, fp + 0x10);
        *(int *)fp = *(int *)fp + 1;
        if (*(int *)fp == 30) {
            *(int *)fp = dead;
            *(float *)(*(char **)(*(char **)(self + 0x4) + 0x870) + 0x80) = 1.0f;
        }
    }
    return 1;
}

extern void _CopyVector(void *dst, void *src);

int EntryEnemyFootPrint(char *self, void *pos)
{
    int i = *(int *)(self + 0x8);
    char *fp = (char *)(i * 0x20 + *(int *)(self + 0xC));
    char *vt;

    *(float *)(fp + 0x4) = 0.05f;
    *(int *)(fp + 0x0) = 0;
    _CopyVector(fp + 0x10, pos);

    *(float *)((char *)(i * 0x20 + *(int *)(self + 0xC)) + 0x14) += -5.0f;
    vt = (char *)(i * 0x50 + *(int *)(*(char **)(self + 0x4) + 0x870));
    *(float *)(vt + 0x20) = *(float *)(vt + 0x24) = *(float *)(vt + 0x28) = 0.0f;

    *(int *)(self + 0x8) = *(int *)(self + 0x8) + 1;
    if (*(int *)(self + 0x8) == *(int *)self) {
        *(int *)(self + 0x8) = 0;
    }
    return 0;
}

extern void p2o_DispVU1DObj();

int DispEnemyFootPrints(int *a0)
{
    p2o_DispVU1DObj(a0[1]);
    return 1;
}

extern int D_0063A438;
extern const char D_0061F710[];
extern PointBlur D_004E78E0;
extern void *iosMallocDebug(int heap, int size, const char *file, int line);

PointBlur *InitPointBlur(int num, int a1, int *col, void *pos)
{
    PointBlur *p = (PointBlur *)iosMallocDebug(D_0063A438, 0x40, D_0061F710, 16);
    *p = D_004E78E0;

    p->f0 = a1;
    p->fC = iosMallocDebug(D_0063A438, num << 5, D_0061F710, 20);
    p->f8 = iosMallocDebug(D_0063A438, num << 4, D_0061F710, 21);
    p->f10 = (Rgba *)iosMallocDebug(D_0063A438, num << 3, D_0061F710, 22);
    p->num = num;
    p->col.r = col[0];
    p->col.g = col[1];
    p->col.b = col[2];
    p->col.a = col[3];
    _CopyVector(p->pos, pos);
    return p;
}

extern void gif_Draw2DStripG();
extern void gif_EndPacket();
extern void gif_SetAlpha();
extern void gif_StartPacketPri();

int DispPointBlur(int *self)
{
    gif_StartPacketPri(self[0]);
    gif_SetAlpha(1, self[0xD], 0x80);
    gif_Draw2DStripG(self[3], self[4], self[1] * 2, 1);
    gif_EndPacket();
    return 1;
}

extern char D_004E79A0[];
extern char D_004E79E0[];
extern void _MulMatrix(void *a0, int a1, void *a2);

int UpdateEnemyEye(char *a0, int a1, float f)
{
    _MulMatrix(a0 + 0x10, a1, D_004E79A0);
    if (*(int *)a0 != 0) {
        UpdatePointBlur(*(PointBlur **)(a0 + 0x4), a0 + 0x40, D_004E79E0, f * 3.0f);
    }
    return 1;
}

extern void _CopyMatrix();
extern void reg_DispMultiPri();

int DispEnemyEye(char *a0)
{
    _CopyMatrix(*(int *)(*(char **)(a0 + 0x50) + 0xC), a0 + 0x10);
    reg_DispMultiPri(*(int *)(a0 + 0x50), 0xA);
    if (*(int *)a0 != 0) {
        char *fobj = *(char **)(a0 + 0x4);
        gif_StartPacketPri(*(int *)fobj);
        gif_SetAlpha(1, *(int *)(fobj + 0x34), 0x80);
        gif_Draw2DStripG(*(int *)(fobj + 0xC), *(int *)(fobj + 0x10), *(int *)(fobj + 0x4) << 1, 1);
        gif_EndPacket();
    }
    return 1;
}

int ResetEnemyEye(char *self)
{
    char *p = *(char **)(self + 0x4);
    *(int *)(p + 0x30) = 1;
    return 1;
}

extern void _CopyIVector(void *dst, void *src);

/* Two strip vertices per footprint: fC holds the IVec positions (2 x 0x10),
 * f10 the packed RGBA words (2 x 4). The alpha lives in byte 3 of the word,
 * so it is reached through a plain unsigned char * -- that char store is what
 * kills the cached p->f10 load for the last statement. */

void moveDataElements(PointBlur *p)
{
    int i;
    float step;
    unsigned char *n;
    float a;

    step = 255.0f / p->num;

    for (i = p->num - 2; i >= 0; i--) {
        _CopyIVector(&((IVec *)p->fC)[i * 2 + 2], &((IVec *)p->fC)[i * 2]);
        _CopyIVector(&((IVec *)p->fC)[i * 2 + 3], &((IVec *)p->fC)[i * 2 + 1]);

        n = (unsigned char *)((unsigned int *)(i * 8 + (int)p->f10) + 2);
        ((unsigned int *)(i * 8 + (int)p->f10))[2] = ((unsigned int *)(i * 8 + (int)p->f10))[0];
        a = (float)((unsigned char *)(i * 8 + (int)p->f10))[3] - step;
        n[3] = (a < 0.0f) ? 0 : (int)a;
        ((unsigned int *)(i * 8 + (int)p->f10))[3] = ((unsigned int *)(i * 8 + (int)p->f10))[2];
    }
    _CopyVector((char *)p->f8 + 0x10, p->f8);
}
