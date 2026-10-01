#include "DObj.h"
#include "memory.h"
#include "DisplayP2O.h"
#include "RegistPacket.h"
#include "quaternion.h"
#include <stdlib.h>
#include "sugiCommon.h"
#include "GsBase.h"
#include "sceneManager.h"
#include "enemyParts.h"
#include "GifPacket.h"
#include "main.h"
#include "matrixDrive.h"
#include "Matrix.h"
#include "ios.h"

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
    /* 0x34 */ int f34;
    /* 0x38 */ char _pad38[8];
} PointBlur;

extern void moveDataElements(PointBlur *p);

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

    if (currentScreenWidth != 0 || GlobalTimer != 0) {
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
    _OuterProduct(c, c, ZUnitVector);
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

/* enemyParts.o's whole .data run, in ROM order: the templates the loops and
   struct assignments copy out of. */

static PointBlur pointBlurTemplate = {2, 1, 0, 0, 0, {0, 0, 0, 0}, 0, {1.0f, 1.0f, 1.0f, 1.0f},
                                      1, 5};

static EnemyEye enemyEyeTemplate = {0};

static int enemyEyeBlurColor[4] = {0x32, 0x62, 0x80, 0x80};

static float enemyEyeBlurRate[4] = {0.3f, 0.7f, 1.0f, 0.0f};

static float enemyEyeScaleMatrix[4][4] = {{3.0f, 0.0f, 0.0f, 0.0f},
                                          {0.0f, 3.0f, 0.0f, 0.0f},
                                          {0.0f, 0.0f, 3.0f, 0.0f},
                                          {0.0f, 0.0f, 0.0f, 1.0f}};

static int enemyEyeBlurTint[4] = {0x00, 0x80, 0xFF, 0x80};

/* 0x10 bytes of zero at 4-byte alignment: ROM copies it with ldl/ldr plus
   sdl/sdr, gcc's unaligned block move. */
static EnemyFootPrintHead footPrintHeadTemplate = {0, 0, 0, 0};

static EnemyFootPrint footPrintVtxTemplate = {-1, 1.0f};

/* The display row's flag word is 64 bits wide: ROM sets and clears single
   bits in it with ld/or/sd and ld/and/sd, and reaches the 16-bit field two
   bytes into the same container with a plain sh. */

/* InitPointBlur is a public member of this TU with its own out-of-line body
   further down at its ROM slot; the January listing shows its rows (15-28)
   inlined whole into InitEnemyEye.  INTERIM: while the out-of-line copy has
   to stay where the ROM puts it, the call site gets this static stand-in,
   which carries the same body and emits no out-of-line code of its own. */
static inline PointBlur *initPointBlurAt(int num, int a1, int *col, void *pos)
{
    PointBlur *p = (PointBlur *)iosMallocDebug(ios_partition_sugipon, 0x40, "src/enemyParts.c", 16);
    *p = pointBlurTemplate;

    p->f0 = a1;
    p->fC = iosMallocDebug(ios_partition_sugipon, num << 5, "src/enemyParts.c", 20);
    p->f8 = iosMallocDebug(ios_partition_sugipon, num << 4, "src/enemyParts.c", 21);
    p->f10 = (Rgba *)iosMallocDebug(ios_partition_sugipon, num << 3, "src/enemyParts.c", 22);
    p->num = num;
    p->col.r = col[0];
    p->col.g = col[1];
    p->col.b = col[2];
    p->col.a = col[3];
    _CopyVector(p->pos, pos);
    return p;
}

EnemyEye *InitEnemyEye(int num, int a1, int a2)
{
    EnemyEye *p;

    p = iosMallocDebug(ios_partition_sugipon, 0x60, "src/enemyParts.c", 137);
    *p = enemyEyeTemplate;

    p->dobj[0] = (Sub15C *)CSVSYSTEM_InitDObj(0x52A, (float *)&InitialSObjSimpleSetting);
    p->dobj[0]->p_870->flags.ll |= 1;
    p->dobj[0]->p_870->fade = 1e-5f;
    p->dobj[0]->p_870->flags.ll |= 4;
    p->dobj[0]->p_870->scale[0] = p->dobj[0]->p_870->scale[1] = p->dobj[0]->p_870->scale[2] = 3.0f;
    p->dobj[0]->dispType = 2;

    p->dobj[1] = (Sub15C *)CSVSYSTEM_InitDObj(0x52B, (float *)&InitialSObjSimpleSetting);
    p->dobj[1]->p_870->flags.ll |= 1;
    p->dobj[1]->p_870->fade = 1e-5f;
    p->dobj[1]->p_870->flags.ll &= ~4;
    p->dobj[1]->p_870->scale[0] = p->dobj[0]->p_870->scale[1] = p->dobj[0]->p_870->scale[2] = 3.0f;
    p->dobj[1]->dispType = 2;

    p->dobj[2] = (Sub15C *)CSVSYSTEM_InitDObj(0x52C, (float *)&InitialSObjSimpleSetting);
    p->dobj[2]->p_870->flags.ll |= 1;
    p->dobj[2]->p_870->fade = 1e-5f;
    p->dobj[2]->p_870->flags.ll &= ~4;
    p->dobj[2]->p_870->scale[0] = p->dobj[0]->p_870->scale[1] = p->dobj[0]->p_870->scale[2] = 3.0f;
    p->dobj[2]->dispType = 2;

    if (num != 0) {
        p->blurOn = 1;
        p->blur = initPointBlurAt(num, a2, enemyEyeBlurColor, enemyEyeBlurRate);
    }
    return p;
}

EnemyFootPrintHead *InitEnemyFootPrint(int num)
{
    EnemyFootPrintHead *p;
    Sub15C *d;
    int i;
    int j;

    p = iosMallocDebug(ios_partition_sugipon, 0x10, "src/enemyParts.c", 226);
    *p = footPrintHeadTemplate;
    p->num = num;
    p->buf = iosMallocDebug(ios_partition_sugipon, num << 5, "src/enemyParts.c", 229);
    d = (Sub15C *)CSVSYSTEM_InitDObj(0x50F, (float *)&InitialSObjSimpleSetting);
    p->dobj = d;
    if (d->f_C != 0) {
        iosFree(d->f_C & 0xFFFFFFF);
    }
    if (p->dobj->f_10 != 0) {
        iosFree(p->dobj->f_10 & 0xFFFFFFF);
    }
    p->dobj->f_C = 0;
    p->dobj->f_10 = 0;
    p->dobj->f_C = (int)iosMallocDebug(ios_partition_seki, num << 6, "src/enemyParts.c", 232);
    p->dobj->f_10 = (int)iosMallocDebug(ios_partition_seki, num << 4, "src/enemyParts.c", 232);
    p->dobj->f_8 = num;
    if ((int)p->dobj->p_870 != 0) {
        iosFree((int)p->dobj->p_870 & 0xFFFFFFF);
    }
    p->dobj->p_870 = iosMallocDebug(ios_partition_seki, num * 0x50, "src/enemyParts.c", 232);
    for (i = 0; i < num; i++) {
        ((struct DObjNode *)(i * 80 + (int)p->dobj->p_870))->flags.ll &= ~1;
        ((struct DObjNode *)(i * 80 + (int)p->dobj->p_870))->flags.ll &= ~2;
        ((struct DObjNode *)(i * 80 + (int)p->dobj->p_870))->pos[0] = 0.0f;
        ((struct DObjNode *)(i * 80 + (int)p->dobj->p_870))->pos[1] = 0.0f;
        ((struct DObjNode *)(i * 80 + (int)p->dobj->p_870))->pos[2] = 0.0f;
        ((struct DObjNode *)(i * 80 + (int)p->dobj->p_870))->pos[3] = 1.0f;
        ((struct DObjNode *)(i * 80 + (int)p->dobj->p_870))->flags.ll &= ~4;
        ((struct DObjNode *)(i * 80 + (int)p->dobj->p_870))->fade = 0;
        ((struct DObjNode *)(i * 80 + (int)p->dobj->p_870))->alpha = 1.0f;
        *(short *)(i * 0x50 + (int)*(char **)((char *)p->dobj + 0x870) + 0x3A) = 0;
        ((struct DObjNode *)(i * 80 + (int)p->dobj->p_870))->scale[0] = 1.0f;
        ((struct DObjNode *)(i * 80 + (int)p->dobj->p_870))->scale[1] = 1.0f;
        ((struct DObjNode *)(i * 80 + (int)p->dobj->p_870))->scale[2] = 1.0f;
    }
    p->dobj->dispType = 2;
    for (j = 0; j < num; j++) {
        p->buf[j] = footPrintVtxTemplate;
        ((struct DObjNode *)(j * 80 + (int)p->dobj->p_870))->flags.ll |= 1;
        ((struct DObjNode *)(j * 80 + (int)p->dobj->p_870))->fade = 1.0f;
        ((struct DObjNode *)(j * 80 + (int)p->dobj->p_870))->flags.ll &= ~4;
        ((struct DObjNode *)(j * 80 + (int)p->dobj->p_870))->scale[0] =
            ((struct DObjNode *)(j * 80 + (int)p->dobj->p_870))->scale[1] =
                ((struct DObjNode *)(j * 80 + (int)p->dobj->p_870))->scale[2] = 0.0f;
    }
    return p;
}

int ExecEnemyFootPrints(EnemyFootPrintHead *self)
{
    int q[4];
    int i;
    EnemyFootPrint *base;

    base = self->buf;
    for (i = 0; i < self->num; i++) {
        EnemyFootPrint *fp = &base[i];
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

        if (fp->life < 0) {
            continue;
        }
        dl = (char *)(i * 0x50 + (int)self->dobj->p_870);
        *(float *)(dl + 0x30) = -(float)(fp->life + 1) / 30.0f;
        *(float *)(dl + 0x20) = *(float *)(dl + 0x20) + fp->speed;
        fp->speed = fp->speed * 0.9f;
        *(float *)(dl + 0x24) = *(float *)(dl + 0x28) = *(float *)(dl + 0x20);
        dead = -1;
        SetQuaternionByAxisRotateVWithNoRegularize(q, rand(), YUnitVector);
        GetMatrixFromQuaternionPos((char *)(self->dobj->f_C + i * 0x40), (char *)q, fp->pos);
        fp->life = fp->life + 1;
        if (fp->life == 30) {
            fp->life = dead;
            *(float *)(*(char **)((char *)self->dobj + 0x870) + 0x80) = 1.0f;
        }
    }
    return 1;
}

int EntryEnemyFootPrint(EnemyFootPrintHead *self, void *pos)
{
    int i = self->idx;
    /* the slot address as an int sum, offset first: the ROM's addu takes the
       scaled index as its first operand, which the subscript does not give */
    EnemyFootPrint *fp = (EnemyFootPrint *)(i * 32 + (int)self->buf);
    char *vt;

    fp->speed = 0.05f;
    fp->life = 0;
    _CopyVector(fp->pos, pos);

    self->buf[i].pos[1] += -5.0f;
    vt = (char *)(i * 0x50 + (int)self->dobj->p_870);
    *(float *)(vt + 0x20) = *(float *)(vt + 0x24) = *(float *)(vt + 0x28) = 0.0f;

    self->idx = self->idx + 1;
    if (self->idx == self->num) {
        self->idx = 0;
    }
    return 0;
}

int DispEnemyFootPrints(EnemyFootPrintHead *a0)
{
    p2o_DispVU1DObj(a0->dobj);
    return 1;
}

PointBlur *InitPointBlur(int num, int a1, int *col, void *pos)
{
    PointBlur *p = (PointBlur *)iosMallocDebug(ios_partition_sugipon, 0x40, "src/enemyParts.c", 16);
    *p = pointBlurTemplate;

    p->f0 = a1;
    p->fC = iosMallocDebug(ios_partition_sugipon, num << 5, "src/enemyParts.c", 20);
    p->f8 = iosMallocDebug(ios_partition_sugipon, num << 4, "src/enemyParts.c", 21);
    p->f10 = (Rgba *)iosMallocDebug(ios_partition_sugipon, num << 3, "src/enemyParts.c", 22);
    p->num = num;
    p->col.r = col[0];
    p->col.g = col[1];
    p->col.b = col[2];
    p->col.a = col[3];
    _CopyVector(p->pos, pos);
    return p;
}

int DispPointBlur(int *self)
{
    gif_StartPacketPri(self[0]);
    gif_SetAlpha(1, self[0xD], 0x80);
    gif_Draw2DStripG(self[3], self[4], self[1] * 2, 1);
    gif_EndPacket();
    return 1;
}

int UpdateEnemyEye(EnemyEye *a0, void *m, float f)
{
    _MulMatrix(a0->mtx, m, enemyEyeScaleMatrix);
    if (a0->blurOn != 0) {
        UpdatePointBlur(a0->blur, a0->mtx[3], enemyEyeBlurTint, f * 3.0f);
    }
    return 1;
}

int DispEnemyEye(EnemyEye *a0)
{
    _CopyMatrix(a0->dobj[0]->f_C, a0->mtx);
    reg_DispMultiPri(a0->dobj[0], 10);
    if (a0->blurOn != 0) {
        char *fobj = (char *)a0->blur;
        gif_StartPacketPri(*(int *)fobj);
        gif_SetAlpha(1, *(int *)(fobj + 0x34), 0x80);
        gif_Draw2DStripG(*(int *)(fobj + 0xC), *(int *)(fobj + 0x10), *(int *)(fobj + 0x4) << 1, 1);
        gif_EndPacket();
    }
    return 1;
}

int ResetEnemyEye(EnemyEye *self)
{
    char *p = (char *)self->blur;
    *(int *)(p + 0x30) = 1;
    return 1;
}

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
