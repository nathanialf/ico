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

extern void *D_0063A438;
extern void *D_0063A44C;
extern const char D_0061F710[];
extern void *iosMallocDebug(void *heap, int size, const char *file, int line);
extern void iosFree(int p);
extern char *CSVSYSTEM_InitDObj(int kind, void *arg);
extern char D_004E45C0[];
extern PointBlur D_004E78E0;
extern int D_004E7980[];
extern float D_004E7990[];

/* The display row's flag word is 64 bits wide: ROM sets and clears single
   bits in it with ld/or/sd and ld/and/sd, and reaches the 16-bit field two
   bytes into the same container with a plain sh. */
typedef union DlFlag {
    int i;
    long long ll;
} DlFlag;

/* The 0x60-byte eye record's initialiser.  ROM copies it with the MIPS
   back end's block-move LOOP (four ld / four sd per turn, 0x20 at a time),
   which is what a 0x60-byte 8-aligned struct assignment expands to. */
typedef struct EnemyEyeTmpl {
    long long d[12];
} EnemyEyeTmpl;

extern EnemyEyeTmpl D_004E7920;

/* InitPointBlur is a public member of this TU with its own out-of-line body
   further down at its ROM slot; the January listing shows its rows (15-28)
   inlined whole into InitEnemyEye.  INTERIM: while the out-of-line copy has
   to stay where the ROM puts it, the call site gets this static stand-in,
   which carries the same body and emits no out-of-line code of its own. */
static inline PointBlur *initPointBlurAt(int num, int a1, int *col, void *pos)
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

char *InitEnemyEye(int num, int a1, int a2)
{
    char *p;

    p = (char *)iosMallocDebug(D_0063A438, 0x60, D_0061F710, 137);
    *(EnemyEyeTmpl *)p = D_004E7920;

    *(char **)(p + 0x50) = CSVSYSTEM_InitDObj(0x52A, D_004E45C0);
    ((DlFlag *)(*(int *)(*(char **)(p + 0x50) + 0x870) + 0x38))->ll |= 1;
    *(float *)(*(int *)(*(char **)(p + 0x50) + 0x870) + 0x30) = 1e-5f;
    ((DlFlag *)(*(int *)(*(char **)(p + 0x50) + 0x870) + 0x38))->ll |= 4;
    *(float *)(*(int *)(*(char **)(p + 0x50) + 0x870) + 0x20) =
        *(float *)(*(int *)(*(char **)(p + 0x50) + 0x870) + 0x24) =
            *(float *)(*(int *)(*(char **)(p + 0x50) + 0x870) + 0x28) = 3.0f;
    *(short *)(*(char **)(p + 0x50) + 0x84C) = 2;

    *(char **)(p + 0x54) = CSVSYSTEM_InitDObj(0x52B, D_004E45C0);
    ((DlFlag *)(*(int *)(*(char **)(p + 0x54) + 0x870) + 0x38))->ll |= 1;
    *(float *)(*(int *)(*(char **)(p + 0x54) + 0x870) + 0x30) = 1e-5f;
    ((DlFlag *)(*(int *)(*(char **)(p + 0x54) + 0x870) + 0x38))->ll &= ~4;
    *(float *)(*(int *)(*(char **)(p + 0x54) + 0x870) + 0x20) =
        *(float *)(*(int *)(*(char **)(p + 0x50) + 0x870) + 0x24) =
            *(float *)(*(int *)(*(char **)(p + 0x50) + 0x870) + 0x28) = 3.0f;
    *(short *)(*(char **)(p + 0x54) + 0x84C) = 2;

    *(char **)(p + 0x58) = CSVSYSTEM_InitDObj(0x52C, D_004E45C0);
    ((DlFlag *)(*(int *)(*(char **)(p + 0x58) + 0x870) + 0x38))->ll |= 1;
    *(float *)(*(int *)(*(char **)(p + 0x58) + 0x870) + 0x30) = 1e-5f;
    ((DlFlag *)(*(int *)(*(char **)(p + 0x58) + 0x870) + 0x38))->ll &= ~4;
    *(float *)(*(int *)(*(char **)(p + 0x58) + 0x870) + 0x20) =
        *(float *)(*(int *)(*(char **)(p + 0x50) + 0x870) + 0x24) =
            *(float *)(*(int *)(*(char **)(p + 0x50) + 0x870) + 0x28) = 3.0f;
    *(short *)(*(char **)(p + 0x58) + 0x84C) = 2;

    if (num != 0) {
        *(int *)p = 1;
        *(PointBlur **)(p + 0x4) = initPointBlurAt(num, a2, D_004E7980, D_004E7990);
    }
    return p;
}

/* The two templates the loops copy out of.  D_004E79F0 is 0x10 bytes of
   zero at 4-byte alignment (ROM copies it with ldl/ldr + sdl/sdr, gcc's
   unaligned block move); D_004E7A00 is 0x20 bytes at 8-byte alignment
   (plain ld/sd).  Both live in the shared data blob and are reached by
   %hi/%lo, so they stay blob-owned. */
typedef struct EnemyFootPrintHead {
    int num;    /* 0x00 */
    char *dobj; /* 0x04 */
    int idx;    /* 0x08 */
    char *buf;  /* 0x0C */
} EnemyFootPrintHead;

typedef struct DlVtxTemplate {
    long long d[4];
} DlVtxTemplate;

extern EnemyFootPrintHead D_004E79F0;
extern DlVtxTemplate D_004E7A00;

char *InitEnemyFootPrint(int num)
{
    char *p;
    char *d;
    int i;
    int j;

    p = (char *)iosMallocDebug(D_0063A438, 0x10, D_0061F710, 226);
    *(EnemyFootPrintHead *)p = D_004E79F0;
    *(int *)p = num;
    *(int *)(p + 0xC) = (int)iosMallocDebug(D_0063A438, num << 5, D_0061F710, 229);
    d = CSVSYSTEM_InitDObj(0x50F, D_004E45C0);
    *(char **)(p + 0x4) = d;
    if (*(int *)(d + 0xC) != 0) {
        iosFree(*(int *)(d + 0xC) & 0xFFFFFFF);
    }
    if (*(int *)(*(char **)(p + 0x4) + 0x10) != 0) {
        iosFree(*(int *)(*(char **)(p + 0x4) + 0x10) & 0xFFFFFFF);
    }
    *(int *)(*(char **)(p + 0x4) + 0xC) = 0;
    *(int *)(*(char **)(p + 0x4) + 0x10) = 0;
    *(int *)(*(char **)(p + 0x4) + 0xC) =
        (int)iosMallocDebug(D_0063A44C, num << 6, D_0061F710, 232);
    *(int *)(*(char **)(p + 0x4) + 0x10) =
        (int)iosMallocDebug(D_0063A44C, num << 4, D_0061F710, 232);
    *(int *)(*(char **)(p + 0x4) + 0x8) = num;
    if (*(int *)(*(char **)(p + 0x4) + 0x870) != 0) {
        iosFree(*(int *)(*(char **)(p + 0x4) + 0x870) & 0xFFFFFFF);
    }
    *(int *)(*(char **)(p + 0x4) + 0x870) =
        (int)iosMallocDebug(D_0063A44C, num * 0x50, D_0061F710, 232);
    for (i = 0; i < num; i++) {
        ((DlFlag *)(i * 0x50 + (int)*(char **)(*(char **)(p + 0x4) + 0x870) + 0x38))->ll &= ~1;
        ((DlFlag *)(i * 0x50 + (int)*(char **)(*(char **)(p + 0x4) + 0x870) + 0x38))->ll &= ~2;
        *(float *)(i * 0x50 + (int)*(char **)(*(char **)(p + 0x4) + 0x870) + 0x40) = 0.0f;
        *(float *)(i * 0x50 + (int)*(char **)(*(char **)(p + 0x4) + 0x870) + 0x44) = 0.0f;
        *(float *)(i * 0x50 + (int)*(char **)(*(char **)(p + 0x4) + 0x870) + 0x48) = 0.0f;
        *(float *)(i * 0x50 + (int)*(char **)(*(char **)(p + 0x4) + 0x870) + 0x4C) = 1.0f;
        ((DlFlag *)(i * 0x50 + (int)*(char **)(*(char **)(p + 0x4) + 0x870) + 0x38))->ll &= ~4;
        *(int *)(i * 0x50 + (int)*(char **)(*(char **)(p + 0x4) + 0x870) + 0x30) = 0;
        *(float *)(i * 0x50 + (int)*(char **)(*(char **)(p + 0x4) + 0x870) + 0x34) = 1.0f;
        *(short *)(i * 0x50 + (int)*(char **)(*(char **)(p + 0x4) + 0x870) + 0x3A) = 0;
        *(float *)(i * 0x50 + (int)*(char **)(*(char **)(p + 0x4) + 0x870) + 0x20) = 1.0f;
        *(float *)(i * 0x50 + (int)*(char **)(*(char **)(p + 0x4) + 0x870) + 0x24) = 1.0f;
        *(float *)(i * 0x50 + (int)*(char **)(*(char **)(p + 0x4) + 0x870) + 0x28) = 1.0f;
    }
    *(short *)(*(char **)(p + 0x4) + 0x84C) = 2;
    for (j = 0; j < num; j++) {
        *(DlVtxTemplate *)(j * 0x20 + *(int *)(p + 0xC)) = D_004E7A00;
        ((DlFlag *)(j * 0x50 + (int)*(char **)(*(char **)(p + 0x4) + 0x870) + 0x38))->ll |= 1;
        *(float *)(j * 0x50 + (int)*(char **)(*(char **)(p + 0x4) + 0x870) + 0x30) = 1.0f;
        ((DlFlag *)(j * 0x50 + (int)*(char **)(*(char **)(p + 0x4) + 0x870) + 0x38))->ll &= ~4;
        *(float *)(j * 0x50 + (int)*(char **)(*(char **)(p + 0x4) + 0x870) + 0x20) =
            *(float *)(j * 0x50 + (int)*(char **)(*(char **)(p + 0x4) + 0x870) + 0x24) =
                *(float *)(j * 0x50 + (int)*(char **)(*(char **)(p + 0x4) + 0x870) + 0x28) = 0.0f;
    }
    return p;
}

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

extern const char D_0061F710[];
extern PointBlur D_004E78E0;

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
