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

typedef struct PointBlur { /* field names derived */
    /* 0x00 */ int pri;
    /* 0x04 */ int num;
    /* 0x08 */ void *screenPos;
    /* 0x0C */ void *strip;
    /* 0x10 */ Rgba *stripCol;
    /* 0x14 */ Rgba col;
    /* 0x18 */ long long _pad18; /* ROM proves 8-byte struct alignment: the
                                     0x40-byte template copy is ld/sd, not lw/sw */
    /* 0x20 */ float pos[4];
    /* 0x30 */ int dirty;
    /* 0x34 */ int alpha;
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
        _CopyVector(&((IVec *)p->screenPos)[i], p->screenPos);
        _CopyIVector(&((IVec *)p->strip)[i * 2], p->strip);
        _CopyIVector(&((IVec *)p->strip)[i * 2 + 1], &((IVec *)p->strip)[1]);
        q = (Rgba *)(i * 8 + (int)p->stripCol);
        q[1] = p->stripCol[0];
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
    _RotTransPersCurrentMatrix(p->screenPos, a);
    a[0] = a[0] + f;
    _RotTransPersCurrentMatrix(b, a);
    scale = b[0] - *(float *)p->screenPos;
    _SubVector(c, (char *)p->screenPos + 0x10, p->screenPos);
    c[2] = 0.0f;
    _OuterProduct(c, c, ZUnitVector);
    _NormalizeVector(c, c);
    _ScaleVector(c, c, scale);
    c[2] = 0.0f;
    _AddVectorXYZ(b, p->screenPos, c);
    _FTOI4Vector(p->strip, b);
    _SubVectorXYZ(b, p->screenPos, c);
    _FTOI4Vector((char *)p->strip + 0x10, b);
    t = p->stripCol;
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

    p->pri = a1;
    p->strip = iosMallocDebug(ios_partition_sugipon, num << 5, "src/enemyParts.c", 20);
    p->screenPos = iosMallocDebug(ios_partition_sugipon, num << 4, "src/enemyParts.c", 21);
    p->stripCol = (Rgba *)iosMallocDebug(ios_partition_sugipon, num << 3, "src/enemyParts.c", 22);
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

    p->dobj[0] = CSVSYSTEM_InitDObj(1322, &InitialSObjSimpleSetting);
    p->dobj[0]->nodes->flags.ll |= 1;
    p->dobj[0]->nodes->fade = 1e-5f;
    p->dobj[0]->nodes->flags.ll |= 4;
    p->dobj[0]->nodes->scale[0] = p->dobj[0]->nodes->scale[1] = p->dobj[0]->nodes->scale[2] = 3.0f;
    p->dobj[0]->dispType = 2;

    p->dobj[1] = CSVSYSTEM_InitDObj(1323, &InitialSObjSimpleSetting);
    p->dobj[1]->nodes->flags.ll |= 1;
    p->dobj[1]->nodes->fade = 1e-5f;
    p->dobj[1]->nodes->flags.ll &= ~4;
    p->dobj[1]->nodes->scale[0] = p->dobj[0]->nodes->scale[1] = p->dobj[0]->nodes->scale[2] = 3.0f;
    p->dobj[1]->dispType = 2;

    p->dobj[2] = CSVSYSTEM_InitDObj(1324, &InitialSObjSimpleSetting);
    p->dobj[2]->nodes->flags.ll |= 1;
    p->dobj[2]->nodes->fade = 1e-5f;
    p->dobj[2]->nodes->flags.ll &= ~4;
    p->dobj[2]->nodes->scale[0] = p->dobj[0]->nodes->scale[1] = p->dobj[0]->nodes->scale[2] = 3.0f;
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
    d = CSVSYSTEM_InitDObj(1295, &InitialSObjSimpleSetting);
    p->dobj = d;
    if (d->nodeMtx != 0) {
        iosFree(d->nodeMtx & 0xFFFFFFF);
    }
    if (p->dobj->nodeQuat != 0) {
        iosFree(p->dobj->nodeQuat & 0xFFFFFFF);
    }
    p->dobj->nodeMtx = 0;
    p->dobj->nodeQuat = 0;
    p->dobj->nodeMtx = (int)iosMallocDebug(ios_partition_seki, num << 6, "src/enemyParts.c", 232);
    p->dobj->nodeQuat = (int)iosMallocDebug(ios_partition_seki, num << 4, "src/enemyParts.c", 232);
    p->dobj->nodeNum = num;
    if ((int)p->dobj->nodes != 0) {
        iosFree((int)p->dobj->nodes & 0xFFFFFFF);
    }
    p->dobj->nodes = iosMallocDebug(ios_partition_seki, num * 0x50, "src/enemyParts.c", 232);
    for (i = 0; i < num; i++) {
        p->dobj->nodes[i].flags.ll &= ~1;
        p->dobj->nodes[i].flags.ll &= ~2;
        p->dobj->nodes[i].pos[0] = 0.0f;
        p->dobj->nodes[i].pos[1] = 0.0f;
        p->dobj->nodes[i].pos[2] = 0.0f;
        p->dobj->nodes[i].pos[3] = 1.0f;
        p->dobj->nodes[i].flags.ll &= ~4;
        p->dobj->nodes[i].fade = 0;
        p->dobj->nodes[i].alpha = 1.0f;
        *(short *)(i * 0x50 + (int)*(char **)((char *)p->dobj + 0x870) + 0x3A) = 0;
        p->dobj->nodes[i].scale[0] = 1.0f;
        p->dobj->nodes[i].scale[1] = 1.0f;
        p->dobj->nodes[i].scale[2] = 1.0f;
    }
    p->dobj->dispType = 2;
    for (j = 0; j < num; j++) {
        p->buf[j] = footPrintVtxTemplate;
        p->dobj->nodes[j].flags.ll |= 1;
        p->dobj->nodes[j].fade = 1.0f;
        p->dobj->nodes[j].flags.ll &= ~4;
        p->dobj->nodes[j].scale[0] = p->dobj->nodes[j].scale[1] = p->dobj->nodes[j].scale[2] = 0.0f;
    }
    return p;
}

int ExecEnemyFootPrints(EnemyFootPrintHead *self)
{
    float q[4];
    int i;
    EnemyFootPrint *base;

    base = self->buf;
    for (i = 0; i < self->num; i++) {
        EnemyFootPrint *fp = &base[i];
        struct DObjNode *dl; /* the node address as an int sum, as EntryEnemyFootPrint's slot */
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
        dl = (struct DObjNode *)(i * 80 + (int)self->dobj->nodes);
        dl->fade = -(float)(fp->life + 1) / 30.0f;
        dl->scale[0] = dl->scale[0] + fp->speed;
        fp->speed = fp->speed * 0.9f;
        dl->scale[1] = dl->scale[2] = dl->scale[0];
        dead = -1;
        SetQuaternionByAxisRotateVWithNoRegularize(q, rand(), YUnitVector);
        GetMatrixFromQuaternionPos((char *)(self->dobj->nodeMtx + i * 0x40), q, fp->pos);
        fp->life = fp->life + 1;
        if (fp->life == 30) {
            fp->life = dead;
            /* node 1's fade, whichever footprint ran out (the ROM's fixed 0x80) */
            self->dobj->nodes[1].fade = 1.0f;
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
    struct DObjNode *vt;

    fp->speed = 0.05f;
    fp->life = 0;
    _CopyVector(fp->pos, pos);

    self->buf[i].pos[1] += -5.0f;
    vt = (struct DObjNode *)(i * 80 + (int)self->dobj->nodes);
    vt->scale[0] = vt->scale[1] = vt->scale[2] = 0.0f;

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

    p->pri = a1;
    p->strip = iosMallocDebug(ios_partition_sugipon, num << 5, "src/enemyParts.c", 20);
    p->screenPos = iosMallocDebug(ios_partition_sugipon, num << 4, "src/enemyParts.c", 21);
    p->stripCol = (Rgba *)iosMallocDebug(ios_partition_sugipon, num << 3, "src/enemyParts.c", 22);
    p->num = num;
    p->col.r = col[0];
    p->col.g = col[1];
    p->col.b = col[2];
    p->col.a = col[3];
    _CopyVector(p->pos, pos);
    return p;
}

int DispPointBlur(PointBlur *self)
{
    gif_StartPacketPri(self->pri);
    gif_SetAlpha(1, self->alpha, 0x80);
    gif_Draw2DStripG(self->strip, self->stripCol, self->num * 2, 1);
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
    _CopyMatrix(a0->dobj[0]->nodeMtx, a0->mtx);
    reg_DispMultiPri(a0->dobj[0], 10);
    if (a0->blurOn != 0) {
        PointBlur *fobj = a0->blur;
        gif_StartPacketPri(fobj->pri);
        gif_SetAlpha(1, fobj->alpha, 0x80);
        gif_Draw2DStripG(fobj->strip, fobj->stripCol, fobj->num << 1, 1);
        gif_EndPacket();
    }
    return 1;
}

int ResetEnemyEye(EnemyEye *self)
{
    self->blur->dirty = 1;
    return 1;
}

/* Two strip vertices per footprint: strip holds the IVec positions (2 x 0x10),
 * stripCol the packed RGBA words (2 x 4). The alpha lives in byte 3 of the word,
 * so it is reached through a plain unsigned char * -- that char store is what
 * kills the cached p->stripCol load for the last statement. */

void moveDataElements(PointBlur *p)
{
    int i;
    float step;
    unsigned char *n;
    float a;

    step = 255.0f / p->num;

    for (i = p->num - 2; i >= 0; i--) {
        _CopyIVector(&((IVec *)p->strip)[i * 2 + 2], &((IVec *)p->strip)[i * 2]);
        _CopyIVector(&((IVec *)p->strip)[i * 2 + 3], &((IVec *)p->strip)[i * 2 + 1]);

        n = (unsigned char *)((unsigned int *)(i * 8 + (int)p->stripCol) + 2);
        ((unsigned int *)(i * 8 + (int)p->stripCol))[2] =
            ((unsigned int *)(i * 8 + (int)p->stripCol))[0];
        a = (float)((unsigned char *)(i * 8 + (int)p->stripCol))[3] - step;
        n[3] = (a < 0.0f) ? 0 : (int)a;
        ((unsigned int *)(i * 8 + (int)p->stripCol))[3] =
            ((unsigned int *)(i * 8 + (int)p->stripCol))[2];
    }
    _CopyVector((char *)p->screenPos + 0x10, p->screenPos);
}
