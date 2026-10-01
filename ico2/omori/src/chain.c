#include "debug.h"
#include "DisplayP2O.h"
#include "matrixDrive.h"
#include "quaternion.h"
#include "tableSin.h"
#include <libvu0.h>
#include <string.h>
#include <math.h>
#include "geometryManager.h"
#include "motionOrientManager.h"
#include "motionFileManager.h"
#include "Matrix.h"
#include "debug_exception.h"
#include "motionManager2.h"
#include "main.h"
#include "fieldCollision.h"
#include "gv.h"

typedef struct {
    float x, y, z, w;
    float vx, vy, vz, vw;
} ChainNode;

/* One word of a chain record or of a chain vector: the chain code writes these
 * slots as float and reads them as int (and the other way round), so the word
 * itself is a union.  ROM re-loads the record pointer before every store
 * through one, which only an alias-set-0 union member does. */
typedef union ChainVal {
    int i;
    float f;
} ChainVal;

/* The pendulum block at 0x20 of a chain record: the swing orientation, the
 * swing state, the swing period at 0x48 (360 at every restart), the swing
 * limit at 0x4C and the swinging flag at 0x50.  Reconstructed from the offsets
 * the chain code uses; the vector makes it 16-aligned and 0x40 long. */
typedef struct {
    /* 0x20 */ sceVu0FVECTOR orient;
    /* 0x30 */ float f30;
    /* 0x34 */ float f34;
    /* 0x38 */ float f38;
    /* 0x3C */ float f3C;
    /* 0x40 */ float f40;
    /* 0x44 */ float f44;
    /* 0x48 */ float period;
    /* 0x4C */ float limit;
    /* 0x50 */ unsigned char swing;
} ChainPendulum;

/* The head of a chain record, 0xE0 bytes, the node array following it.
 * Reconstructed from the offsets the chain code uses. */
typedef struct {
    /* 0x00 */ int root;
    /* 0x04 */ int rootNode;
    /* 0x10 */ sceVu0FVECTOR rootPos;
    /* 0x20 */ ChainPendulum pdl;
    /* 0x60 */ unsigned char hold;
    /* 0x64 */ char *owner;
    /* 0x68 */ int holdNode;
    /* 0x6C */ unsigned char f6C;
    /* 0x70 */ float f70;
    /* 0x74 */ int nodes;
    /* 0x78 */ int mode; /* derived name */
    /* 0x80 */ sceVu0FVECTOR f80;
    /* 0x90 */ sceVu0FVECTOR f90;
    /* 0xA0 */ unsigned char wallHit;
    /* 0xA4 */ float wallPos[2];
    /* 0xAC */ char *wall;
    /* 0xB0 */ sceVu0FVECTOR wallOrient;
    /* 0xC0 */ unsigned char fC0;
    /* 0xC4 */ int count;
    /* 0xC8 */ float angle;
    /* 0xCC */ unsigned char fCC;
    /* 0xCD */ unsigned char fCD;
    /* 0xD0 */ ChainNode *node;
} ChainRecord;

int UpdateRootPosition(char *gobj)
{
    float pos[4];
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(gobj)->f_830;
    ChainNode *nd;
    int moved = 0;

    if (*(int *)cw != 0) {
        SetDirectRootPosition(gobj, *(char **)(*(int *)(cw->root + 0x15C) + 0xC) +
                                        (cw->rootNode << 6) + 0x30);
    }
    GetRootPosition(pos, gobj);
    if (_DistSqGV(pos, cw->rootPos) < 1.0f) {
    } else {
        moved = 1;
    }
    cw->rootPos[0] = pos[0];
    cw->rootPos[1] = pos[1];
    cw->rootPos[2] = pos[2];
    nd = cw->node;
    nd[0].x = cw->rootPos[0];
    nd[0].y = cw->rootPos[1];
    nd[0].z = cw->rootPos[2];
    cw->f80[0] = nd[2].x;
    cw->f80[1] = nd[2].y;
    cw->f80[2] = nd[2].z;
    cw->f90[0] = nd[cw->nodes - 1].x;
    cw->f90[1] = nd[cw->nodes - 1].y;
    cw->f90[2] = nd[cw->nodes - 1].z;
    return moved;
}

/* kept local: void * (void *) here, void * (char *) in commonact.h */
extern void *test_CURRENTORIENT(void *a0);
extern void __assert(char *file, int line, char *expr);
void _GetCorrectOrientOfChain(float *out, char *gobj, float *dir);

/* INTERIM (same shape as GetChainDirCorrectVal below): the listing inlines
 * InitPendulum's lines 517-538 into StartPendulum, so InitPendulum is a public
 * `inline` whose out-of-line copy sits at its own ROM position further down;
 * until then the caller inlines this static stand-in, which collapses at
 * layout. */
static inline void initPendulum(char *gobj)
{
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(gobj)->f_830;
    float a = (float)debug_chain_cycle_speed * -0.2f + 2.0f;
    float y;

    a = a < 0.1f ? 0.1f : (a > 2.0f ? 2.0f : a);

    y = (float)(int)(a * 6.0f * FSqrt(cw->pdl.f3C / 2.5f) * 8.0f / 10.0f);

    cw->pdl.f40 = y;
    cw->pdl.f40 = cw->pdl.f40 < 1.0f ? 1.0f : (cw->pdl.f40 > 255.0f ? 255.0f : cw->pdl.f40);

    cw->pdl.f38 = cw->pdl.f40 * 0.5f;
    cw->pdl.period = 360.0f;
    cw->pdl.swing = 1;
}

/* K&R definition: HoldChain calls StartPendulum with the gobj alone. */
void StartPendulum(gobj, owner, pos) char *gobj;

char *owner;

float *pos;

{
    float d[4];
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(gobj)->f_830;
    int best = -1;
    float min = 3.40282347e+38f; /* FLT_MAX, a constant-pool word */
    int i;

    sceVu0SubVector(d, pos, cw->node);
    cw->owner = owner;

    for (i = 0; i < cw->nodes; i++) {
        int n = (int)(pos[1] - (cw->node)[i].y);
        float t = (float)(n < 0 ? -n : n);

        if (t < min) {
            min = t;
            best = i;
        }
    }
    if (best == -1) {
        debug_assert(__FILE__, 563);
        __assert(__FILE__, 563, "nearestNode!=-1");
    }
    cw->holdNode = best;
    cw->holdNode =
        cw->holdNode < 2 ? 2 : (cw->nodes - 1 < cw->holdNode ? cw->nodes - 1 : cw->holdNode);

    _GetCorrectOrientOfChain((float *)cw->pdl.orient, gobj, (float *)test_CURRENTORIENT(owner));

    ((ChainVal *)&cw->pdl.f3C)->f = (float)cw->holdNode * 50.0f;

    initPendulum(gobj);
}

/* the debug trace line: every chain trace steps it by 10 and ChainGeo resets
 * it; chain.o's one .sbss word, MAIN.MAP names nothing there, so the name is
 * ours */
static int chainDebugY;

/* kept local: void (float, void *, void *, int, int, int) here, void (void) in camera-editor.h */
extern void debug_Arrow(float len, void *from, void *to, int r, int g, int b);

/* The wall-clip request the chain hands to ClipWall: the segment endpoints, the
 * clip radius at 0x70 and the hit result at 0x88. */
typedef struct {
    /* 0x00 */ float from[4];
    /* 0x10 */ float to[4];
    /* 0x20 */ char _20[0x50];
    /* 0x70 */ float radius;
    /* 0x74 */ char _74[0xC];
    /* 0x80 */ float f80[2];
    /* 0x88 */ int hit;
    /* 0x8C */ char _8c[0x34];
} ChainClipWork;

int collisionCheck(char *gobj)
{
    ChainClipWork w;
    float v[4];
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(gobj)->f_830;

    if (cw->pdl.swing) {
        v[0] = cw->pdl.orient[0];
        v[1] = cw->pdl.orient[1];
        v[2] = cw->pdl.orient[2];
    } else {
        sceVu0ScaleVector(v, cw->pdl.orient, -1.0f);
    }
    v[1] = 0.0f;
    sceVu0Normalize(v, v);
    debug_Arrow(200.0f, &cw->node[cw->holdNode], v, 0xFF, 0, 0xFF);
    sceVu0ScaleVector(v, v, 140.0f);
    w.from[0] = cw->node[cw->holdNode].x;
    w.from[1] = cw->node[cw->holdNode].y;
    w.from[2] = cw->node[cw->holdNode].z;
    sceVu0AddVector(w.to, w.from, v);
    w.radius = 10.0f;
    ClipWall(&w);
    if (w.hit) {
        if (debug_font_flag & 1) {
            chainDebugY = chainDebugY + 10;
            debug_Printf(10, chainDebugY, 0x0FFFFFFF, "collision!!!\n");
        }
        return 1;
    }
    return 0;
}

/* kept local: chain.h does not compile in this TU (conflicting types for `ChainGeo') */
extern int collisionCheck(char *gobj);
/* kept local: chain.h does not compile in this TU (conflicting types for `ChainGeo') */
extern void pendulum_Process(void *a0, int a1);
/* kept local: chain.h does not compile in this TU (conflicting types for `ChainGeo') */
extern void chain_sub_pendulum(char *base, int n, void *a2);
/* The sixth integer parameter is passed by both ROM call sites (always 0) and
 * never read by the body; it keeps $9 in the argument sequence. */
extern void chain_sub_simulate(int a0, ChainNode *nd, int from, int to, unsigned char flag,
                               int flag2, float grav, float len, float damp);

static inline void ChainPendulumSwing(float *dst, ChainRecord *cw, float *orient)
{
    float ang = cw->pdl.f30;
    float len = cw->pdl.f3C;
    float m1[16];
    float m2[16];
    float v[4];

    v[0] = 0.0f;
    v[1] = len;
    v[2] = 0.0f;

    sceVu0UnitMatrix(m1);
    sceVu0RotMatrixX(m2, m1, ang * 3.1415927f / 180.0f);
    sceVu0RotMatrixY(
        m1, m2, (float)(int)(_GetDirection(orient) / 3.1415927f * 180.0f) * 3.1415927f / 180.0f);

    sceVu0ApplyMatrix(dst, m1, v);
}

void chain_simulate_term_simple(int a0)
{
    float pos[4];
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(a0)->f_830;

    pendulum_Process(cw->pdl.orient, collisionCheck((char *)a0));
    ChainPendulumSwing(pos, cw, (float *)cw->pdl.orient);
    sceVu0AddVector(pos, cw->node, pos);
    chain_sub_pendulum((char *)cw->node, cw->holdNode, pos);
    chain_sub_simulate(a0, cw->node, cw->holdNode, cw->nodes, 1, 0, 20.0f, 50.0f, 0.6f);
}

/* kept local: chain.h does not compile in this TU (conflicting types for `ChainGeo') */
extern void chain_simulate_term_simple(int a0);

void chain_simulate_term_ropeturn(int a0)
{
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(a0)->f_830;

    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_term_ropeturn\n");
    }
    cw->pdl.f44 = -0.4f;
    chain_simulate_term_simple(a0);
}

void chain_simulate_term_loop(int a0)
{
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(a0)->f_830;

    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_term_loop\n");
    }
    if (cw->pdl.f34 < 0.5) {
        cw->pdl.f44 = -0.01f;
    } else if (cw->pdl.f34 < 1.0) {
        cw->pdl.f44 = -0.05f;
    } else {
        cw->pdl.f44 = -0.15f;
    }
    chain_simulate_term_simple(a0);
}

void chain_simulate_term_swingready(int a0)
{
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(a0)->f_830;

    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_term_swingready\n");
    }
    if (cw->pdl.f34 < 0.5) {
        cw->pdl.f44 = -0.29999998f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
    } else if (cw->pdl.f34 < 1.0) {
        cw->pdl.f44 = -1.5f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
    } else {
        cw->pdl.f44 = -4.5f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
    }
    chain_simulate_term_simple(a0);
}

void chain_simulate_term_swingstart(int a0)
{
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(a0)->f_830;
    float h;

    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_term_swingstart\n");
    }

    h = GOBJ_SUB(boyGObj)->f_4AC;

    if (h < 20.0f) {
        if (cw->pdl.f34 < 0.3) {
            cw->pdl.f44 = -0.29999998f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
        } else if (cw->pdl.f34 < 1.0) {
            cw->pdl.f44 = -6.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
        } else {
            cw->pdl.f44 = -9.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
        }
    } else {
        if (h >= 20.0 && h < 21.5) {
            cw->pdl.f38 = 0.0f;
            cw->pdl.period = 360.0f;
        }
        cw->pdl.f44 = 0.0f;
        cw->pdl.f34 = 3.0f;

        cw->pdl.f38 = cw->pdl.f38 - 1.0f +
                      cw->pdl.f40 * 0.5f / 41.0f * 30.0f /
                          (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
    }
    chain_simulate_term_simple(a0);
}

void chain_simulate_term_moveup(int a0)
{
    float w[4];
    float v[4];
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(a0)->f_830;
    float h;

    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_term_moveup\n");
    }
    if (cw->pdl.f34 < 1.0f) {
        cw->pdl.f34 = 1.0f;
        cw->pdl.f44 = 0.0f;
    } else if (cw->pdl.f34 < 2.0) {
        cw->pdl.f44 = -0.05f;
    } else {
        cw->pdl.f44 = -0.15f;
    }
    chain_simulate_term_simple(a0);
    h = GOBJ_SUB(boyGObj)->f_4AC;
    v[0] = cw->pdl.orient[0];
    v[1] = cw->pdl.orient[1];
    v[2] = cw->pdl.orient[2];
    _ApplyRyGV(v, -1.5707964f);
    sceVu0ScaleVector(v, v,
                      GetTableSin(h * 6.283185307179586 / 40.0 * 32768.0 / 3.1415927f) * 5.0f);
    sceVu0AddVector(w, &cw->node[cw->holdNode], v);
    chain_sub_pendulum((char *)cw->node, cw->holdNode, w);
}

void chain_simulate_term_free(int a0)
{
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(a0)->f_830;

    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_term_free\n");
    }
    if (cw->pdl.f34 < 0.5) {
        cw->pdl.f44 = -0.01f;
    } else if (cw->pdl.f34 < 2.0) {
        cw->pdl.f44 = -0.05f;
    } else {
        cw->pdl.f44 = -0.15f;
    }
    chain_simulate_term_simple(a0);
}

void chain_simulate_term_down(int a0)
{
    float w[4];
    float v[4];
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(a0)->f_830;
    ChainNode *nd;
    ChainNode *next;
    float h;

    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        /* a 2001 copy and paste: this arm prints the sibling term's name */
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_term_free\n");
    }
    if (cw->pdl.f34 < 0.5) {
        cw->pdl.f44 = -0.01f;
    } else if (cw->pdl.f34 < 2.0) {
        cw->pdl.f44 = -0.05f;
    } else {
        cw->pdl.f44 = -0.15f;
    }
    chain_simulate_term_simple(a0);
    h = GOBJ_SUB(boyGObj)->f_4AC;
    v[0] = cw->pdl.orient[0];
    v[1] = cw->pdl.orient[1];
    v[2] = cw->pdl.orient[2];
    _ApplyRyGV(v, -1.5707964f);
    sceVu0ScaleVector(v, v,
                      GetTableSin(h * 6.283185307179586 / 23.0 * 32768.0 / 3.1415927f) * 2.0f);
    sceVu0AddVector(w, &cw->node[cw->holdNode], v);
    chain_sub_pendulum((char *)cw->node, cw->holdNode, w);
    if (cw->holdNode + 1 <= cw->nodes - 1) {
        nd = (ChainNode *)((cw->holdNode << 5) + (int)cw->node);
        next = nd + 1;
        next->x = nd->x;
        next->y = nd->y + 50.0f;
        next->z = nd->z;
    }
}

void chain_simulate_hangstart(int a0)
{
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(a0)->f_830;

    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_hangstart\n");
    }
    cw->pdl.f44 = -1.5f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
    chain_simulate_term_simple(a0);
}

void chain_simulate_term(int a0)
{
    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_term\n");
    }
    chain_simulate_term_simple(a0);
}

static inline void ResetChainNodes(ChainRecord *cw, float *pos)
{
    int i;

    for (i = 0; i < cw->nodes; i++) {
        ChainNode *e = cw->node + i;
        e->x = pos[0];
        e->y = pos[1];
        e->z = pos[2];
        e->y += (float)i * 50.0f;
        e->vx = 0.0f;
        e->vy = 0.0f;
        e->vz = 0.0f;
    }
}

void chain_simulate_stop(int a0)
{
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(a0)->f_830;

    ResetChainNodes(cw, (float *)cw->rootPos);
    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_stop\n");
    }
}

void chain_simulate_free(int a0)
{
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(a0)->f_830;
    int i;

    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_free\n");
    }
    chain_sub_simulate(a0, cw->node, 0, cw->nodes, 1, 0, 10.0f, 50.0f, 0.675f);
    cw->pdl.f34 = 0.0f;
    for (i = 1; i < cw->nodes; i++) {
        ChainNode *nd = cw->node;
        if (nd[i].y < nd[i - 1].y) {
            nd[i].x += 3.0f;
            nd[i].y += 3.0f;
        }
    }
}

void correct_vector(float *out, float *v)
{
    float a[4];
    float u[4];

    memset(a, 0, 16);

    MatrixDrive_PushMatrix();

    a[1] = -atan2f(v[0], v[2]);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_RotMatrixY((short)(a[1] * 32768.0f / 3.1415927f));

    v[3] = 0.0f;
    sceVu0ApplyMatrix(u, MatrixDrive_GetMatrix(), v);

    a[0] = atan2f(u[1], u[2]);

    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_RotMatrixX((short)(a[0] * 32768.0f / 3.1415927f));
    MatrixDrive_RotMatrixY((short)(a[1] * 32768.0f / 3.1415927f));

    out[3] = 0.0f;
    sceVu0ApplyMatrix(u, MatrixDrive_GetMatrix(), out);

    u[2] = 0.0f;
    MatrixDrive_SetTransposeMatrix(MatrixDrive_GetMatrix(), MatrixDrive_GetMatrix());

    u[3] = 0.0f;
    sceVu0ApplyMatrix(out, MatrixDrive_GetMatrix(), u);

    MatrixDrive_PopMatrix();
}

/* The pendulum block the chain work carries at cw+0x20; the caller hands the
 * block itself, so the leading 0x10 bytes are the swing orient vector. */
typedef struct {
    /* 0x00 */ char _0[0x10];
    /* 0x10 */ float f10;
    /* 0x14 */ float f14;
    /* 0x18 */ float f18;
    /* 0x1C */ float f1C;
    /* 0x20 */ float f20;
    /* 0x24 */ float f24;
    /* 0x28 */ float f28;
    /* 0x2C */ float f2C;
    /* 0x30 */ unsigned char f30;
} PdlWork;

/* K&R definition: ROM zero-extends the flag on entry, which a prototyped int
 * parameter cannot do, and the file-scope extern above (int) is compatible
 * with the promoted unsigned char. */
void pendulum_Process(p, flag) void *p;

unsigned char flag;

{
    PdlWork *w = (PdlWork *)p;
    int up;

    up = w->f24 > 0.0f ? 1 : 0;

    if (debug_font_flag & 1) {
        debug_Printf(10, chainDebugY += 10, 0x0FFFFFFF, "time = %f\n", w->f18);
        if (debug_font_flag & 1) {
            debug_Printf(10, chainDebugY += 10, 0x0FFFFFFF, "rad  = %f\n", w->f10);
            if (debug_font_flag & 1) {
                debug_Printf(10, chainDebugY += 10, 0x0FFFFFFF, "max  = %f\n", w->f14);
                if (debug_font_flag & 1) {
                    debug_Printf(10, chainDebugY += 10, 0x0FFFFFFF, "maxl = %f\n", w->f28);
                    if (debug_font_flag & 1) {
                        debug_Printf(10, chainDebugY += 10, 0x0FFFFFFF, "T    = %f\n", w->f20);
                        if (debug_font_flag & 1) {
                            debug_Printf(10, chainDebugY += 10, 0x0FFFFFFF, "d    = %f\n", w->f1C);
                            if (debug_font_flag & 1) {
                                debug_Printf(10, chainDebugY += 10, 0x0FFFFFFF, "inc  = %d\n", up);
                            }
                        }
                    }
                }
            }
        }
    }

    if (w->f1C > 0.0f) {
        w->f18 = w->f18 + 1.0f;
        if (w->f20 <= w->f18) {
            w->f18 = 0.0f;
        }

        w->f14 = w->f14 + w->f24;
        w->f14 = w->f14 < 0.0f ? 0.0f : (w->f2C < w->f14 ? w->f2C : w->f14);
        w->f24 = 0.0f;

        w->f10 = -GetTableSin(((int)w->f18 << 16) / (int)w->f20) * w->f14;

        if (flag) {
            if ((w->f10 < 0.0f ? -w->f10 : w->f10) < w->f28) {
                w->f28 = w->f10 < 0.0f ? -w->f10 : w->f10;
            }
        }

        if (w->f28 < w->f14) {
            w->f14 = w->f14 - 0.2f;
        }

        w->f10 = w->f10 < -w->f28 ? -w->f28 : (w->f28 < w->f10 ? w->f28 : w->f10);

        if (w->f20 * 0.25 < w->f18 && w->f18 < w->f20 * 0.75) {
            w->f30 = 1;
        } else {
            w->f30 = 0;
        }
    }
}

/* kept local: this TU does not include fieldCollision.h, whose third parameter
 * type is not the float pair the chain hands over */
/* kept local: this TU does not include memory.h, whose first parameter type is
 * not the plain partition word the chain code hands over */
/* kept local: void * (void *, int, char *, int) here, void * (IosMemPart *, int, char *, int) in memory.h */
extern void *iosMallocDebug(void *part, int size, char *file, int line);
/* kept local: agrees with memory.h, which this TU does not include (iosMallocDebug differs) */
extern void *iosFree(void *p);

/* the two templates a new chain geometry starts from, the pendulum block and
 * the record head; MAIN.MAP names nothing in chain.o's .data, so both names
 * are ours */
static ChainPendulum chainPendulumDefault = {
    {0.0f, 0.0f, 0.0f, 0.0f}, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 360.0f, 45.0f, 1};

static ChainRecord chainRecordDefault = {
    0,
    0,
    {0.0f, 0.0f, 0.0f, 0.0f},
    {{0.0f, 0.0f, 0.0f, 0.0f}, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0},
    0,
    0,
    -1,
    0,
    0.0f,
    0,
    0,
    {0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f},
    0,
    {0.0f, 0.0f},
    0,
    {0.0f, 0.0f, 0.0f, 0.0f},
    1,
    0,
    70.0f,
    0,
    1,
    0};

/* kept local: void * here, int in ios.h */
extern void *ios_partition_sugipon;
/* kept local: void * here, int in ios.h */
extern void *ios_partition_seki;

/* The geometry request the caller fills in: the anchor position, the probe
 * direction at 0x10 and 0x14, the hang height at 0x18, the start angle at 0x20,
 * the chain length at 0x24 and the swing limit at 0x28. */
typedef struct {
    /* 0x00 */ float pos[4];
    /* 0x10 */ float f10;
    /* 0x14 */ float f14;
    /* 0x18 */ float f18;
    /* 0x1C */ float f1C;
    /* 0x20 */ float f20;
    /* 0x24 */ float f24;
    /* 0x28 */ float f28;
} ChainGeoReq;

/* the copy shapes the record templates are moved through: doubleword-aligned
 * so the copies come out as ld/sd runs */
typedef struct {
    long long w[28];
} ChainRecTemplate;

typedef struct {
    long long w[8];
} ChainPendTemplate;

/* the wall hit point, written into a word-aligned slot of the record */
typedef struct {
    float w[2];
} ChainHitPos;

/* the gobj extension pointer, read as a union member: every store through the
 * extension has to force the reload the ROM does */
typedef union {
    char *p;
    int i;
} ChainExtPtr;

/* the DObj entry flag word, the same union DObj.c's allocObjectData uses */
typedef union {
    long long ll;
    int i[2];
} ChainDObjFlags;

char *InitChainGeo(char *gobj, ChainGeoReq *req)
{
    char *cw;
    int n;
    int i;

    n = (int)(req->f24 / 50.0f + 0.5f);

    if (n < 2) {
        /* "the chain is too short (set it with the Y-scale of the placement table)" */
        debug_StdPrintfDummy("鎖の長さが短かすぎます(配置表のY-scaleで指定します)");
        debug_assert(__FILE__, 1178);
        __assert(__FILE__, 1178, "0");
    }

    cw = (char *)iosMallocDebug((void *)ios_partition_sugipon, (n << 5) + 0xE0, __FILE__, 1181);

    *(ChainRecTemplate *)cw = *(ChainRecTemplate *)&chainRecordDefault;

    *(int *)(cw + 0x74) = n;
    *(char **)(cw + 0xD0) = cw + 0xE0;
    *(int *)(cw + 0x68) = -1;
    if (req->f20 != -1.0f) {
        *(float *)(cw + 0xC8) = req->f20;
    }

    *(ChainPendTemplate *)(cw + 0x20) = *(ChainPendTemplate *)&chainPendulumDefault;

    *(float *)(cw + 0x4C) = req->f28;
    *(float *)(cw + 0x4C) = *(float *)(cw + 0x4C) < 5.0f
                                ? 5.0f
                                : (90.0f < *(float *)(cw + 0x4C) ? 90.0f : *(float *)(cw + 0x4C));

    ResetChainNodes(cw, (float *)req);

    if (req->f10 != 0.0f) {
        sceVu0FVECTOR p0 = {0.0f, 0.0f, -25.0f, 1.0f};
        sceVu0FVECTOR p1 = {0.0f, 0.0f, 25.0f, 1.0f};
        ChainClipWork w;
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrix(req->pos[0], req->pos[1] + 10.0f, req->pos[2]);
        MatrixDrive_RotMatrixY((short)(req->f14 * 32768.0f / 3.1415927f));
        sceVu0ApplyMatrix(w.from, MatrixDrive_GetMatrix(), p0);
        sceVu0ApplyMatrix(w.to, MatrixDrive_GetMatrix(), p1);
        ClipWall(&w);
        if (w.hit == 0) {
            /* "cannot find the wall above the chain. / is the direction wrong, or is
             * it placed where there is no wall?" (in yellow) */
            debug_StdPrintfDummy(
                "\033[33m鎖の上の壁を見付けることができません。\n方向が間違っているか、壁が無いところに置いていませんか?\033[m\n");
        } else {
            *(ChainHitPos *)(cw + 0xA4) = *(ChainHitPos *)w.f80;
            *(char **)(cw + 0xAC) = (char *)w.hit;
            GetOrientOfWall(cw + 0xB0, w.hit, w.f80);
            cw[0xA0] = 1;
        }
    } else {
        *(int *)(cw + 0xA4) = 0;
        *(int *)(cw + 0xA8) = 0;
        *(char **)(cw + 0xAC) = 0;
        cw[0xA0] = 0;
    }

    if (req->f18 < 0.0f) {
        cw[0x6C] = 0;
    } else {
        cw[0x6C] = 1;
        *(float *)(cw + 0x70) = req->f18;
    }

    if (*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0xC) != 0) {
        iosFree((void *)((int)*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0xC) & 0x0FFFFFFF));
    }
    if (*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x10) != 0) {
        iosFree((void *)((int)*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x10) & 0x0FFFFFFF));
    }
    *(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0xC) = 0;
    *(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x10) = 0;
    *(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0xC) = (char *)iosMallocDebug(
        (void *)ios_partition_seki, (*(int *)(cw + 0x74) - 1) << 6, __FILE__, 1245);
    *(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x10) = (char *)iosMallocDebug(
        (void *)ios_partition_seki, (*(int *)(cw + 0x74) - 1) << 4, __FILE__, 1245);
    *(int *)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x8) = *(int *)(cw + 0x74) - 1;
    if (*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x870) != 0) {
        iosFree((void *)((int)*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x870) & 0x0FFFFFFF));
    }
    *(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x870) = (char *)iosMallocDebug(
        (void *)ios_partition_seki, (*(int *)(cw + 0x74) - 1) * 80, __FILE__, 1245);

    for (i = 0; i < *(int *)(cw + 0x74) - 1; i++) {
        {
            char *e =
                (char *)(i * 80 + (int)*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x870));
            ((ChainDObjFlags *)(e + 0x38))->ll &= ~1;
        }
        {
            char *e =
                (char *)(i * 80 + (int)*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x870));
            ((ChainDObjFlags *)(e + 0x38))->ll &= ~2;
        }
        {
            char *e =
                (char *)(i * 80 + (int)*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x870));
            *(float *)(e + 0x40) = 0.0f;
        }
        {
            char *e =
                (char *)(i * 80 + (int)*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x870));
            *(float *)(e + 0x44) = 0.0f;
        }
        {
            char *e =
                (char *)(i * 80 + (int)*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x870));
            *(float *)(e + 0x48) = 0.0f;
        }
        {
            char *e =
                (char *)(i * 80 + (int)*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x870));
            *(float *)(e + 0x4C) = 1.0f;
        }
        {
            char *e =
                (char *)(i * 80 + (int)*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x870));
            ((ChainDObjFlags *)(e + 0x38))->ll &= ~4;
        }
        {
            char *e =
                (char *)(i * 80 + (int)*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x870));
            *(int *)(e + 0x30) = 0;
        }
        {
            char *e =
                (char *)(i * 80 + (int)*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x870));
            *(float *)(e + 0x34) = 1.0f;
        }
        {
            char *e =
                (char *)(i * 80 + (int)*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x870));
            *(short *)(e + 0x3A) = 0;
        }
        {
            char *e =
                (char *)(i * 80 + (int)*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x870));
            *(float *)(e + 0x20) = 1.0f;
        }
        {
            char *e =
                (char *)(i * 80 + (int)*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x870));
            *(float *)(e + 0x24) = 1.0f;
        }
        {
            char *e =
                (char *)(i * 80 + (int)*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x870));
            *(float *)(e + 0x28) = 1.0f;
        }
    }
    *(short *)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x84C) = 2;

    return cw;
}

void chain_set_charachara(char *gobj, float amp)
{
    float v[4];
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(gobj)->f_830;
    int deg;
    int idx;
    float c;
    float s;
    char *p;

    memset(v, 0, 16);

    deg = (int)(_GetDirection(test_CURRENTORIENT(boyGObj)) / 3.1415927f * 180.0f);
    idx = cw->holdNode + 2;

    if (cw->nodes - 2 < idx) {
        return;
    }

    c = GetTableCos(cw->count * 2000) * amp;
    s = GetTableSin(cw->count * 1500) * amp;

    v[0] = c;
    v[1] = 0.0f;
    v[2] = s;
    _ApplyRyGV(v, (float)deg * 3.1415927f / 180.0f);

    p = (char *)((idx << 5) + (int)cw->node);
    *(float *)p = *(float *)(p - 0x20) + v[0];

    *(float *)(p + 0x8) = *(float *)(p - 0x18) + v[2];

    cw->count = cw->count + 1;
}

/* kept local: int (void *, int, void *) here, int (char *, int, int) in obj_manager.h */
extern int iosOmSendMail(void *to, int msg, void *from);

/* The enemy parameter table, one 404-byte row per motion id; ChainGeo reads
 * only the flag word at 0x18C.  Same record enemy_act.c reads as EnemyParaRow. */
typedef struct {
    char pad00[0x18C];
    unsigned int flags18C;
    char pad190[4];
} ChainParaRow;

extern ChainParaRow motionKind[];
void SetChainRootUpdateMode(char *gobj, int mode, float *pos);
void TestChainUpDown(char *gobj, char *boy);

/* chain.c lines 342-390: the motion-to-simulation-mode selector, inlined into
 * ChainGeo by its single call site. */
static inline int GetChainSimulateMode(char *gobj)
{
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(gobj)->f_830;
    int mode = 1;

    if (cw->hold != 0) {
        char *holder = cw->owner;
        int st = *(int *)(*(int *)(holder + 0x164) + 0x34);

        mode = 6;
        if (st != 58) {
            mode = st == 59 ? 9 : 3;
        }

        switch (*(int *)(*(int *)(holder + 0x15C) + 0x4A0)) {
        case 136:
        case 137:
            if (mode == 3) {
                mode = 11;
            }
            break;
        case 140:
            mode = 11;
            break;
        case 123:
        case 124:
            mode = 4;
            break;
        case 120:
            mode = 10;
            break;
        case 119:
            mode = 7;
            break;
        case 121:
        case 122:
            mode = 8;
            break;
        case 128:
            mode = 2;
            break;
        case 134:
            mode = 5;
            break;
        }
    }
    return mode;
}

/* chain.c lines 441-487: the hand-proximity probe down the chain, inlined into
 * ChainGeo by its single call site; the caller reads the result as one byte. */
static inline unsigned char isChainHitByHand(char *gobj, float *p, float *v, float *o, float lim)
{
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(gobj)->f_830;
    float d[4];
    int i;
    int ilim = (int)lim;

    /* clang-format off */
    v[0] = o[0]; v[1] = o[1]; v[2] = o[2];
    /* clang-format on */
    v[1] = 0.0f;

    for (i = 2; i <= cw->nodes - 1; i++) {
        ChainNode *nd = (ChainNode *)((i << 5) + (int)cw->node);

        if (nd->y < p[1] && p[1] < nd->y + 50.0f) {
            float t;
            float r;

            sceVu0SubVector(d, nd, p);
            d[1] = 0.0f;
            t = sceVu0InnerProduct(d, v);
            r = FSqrt(d[0] * d[0] + d[1] * d[1] + d[2] * d[2] - t * t);
            if (-50.0f < t && t < 50.0f && r < (float)ilim) {
                return 1;
            }
        }
    }
    return 0;
}

void ChainGeo(char *gobj)
{
    float p[4];
    float v[4];
    ChainRecord *cw = *(ChainRecord **)(*(int *)(gobj + 0x15C) + 0x830);
    char *sub;
    int mode;
    int moved;
    int i;

    chainDebugY = 250;

    if (cw->fCC != 0) {
        return;
    }

    moved = UpdateRootPosition(gobj);

    mode = GetChainSimulateMode(gobj);

    if (boyGObj != 0) {
        float lim;

        lim = cw->angle;
        if (*(int *)(*(int *)((char *)boyGObj + 0x164) + 0x34) == 5 ||
            (((motionKind + *(int *)(*(int *)((char *)boyGObj + 0x15C) + 0x4A0))->flags18C >> 11) &
             1)) {
            lim = 70.0f;
        }

        GetRootPositionHandExtra(boyGObj, p);
        if (isChainHitByHand(gobj, p, v, (float *)test_CURRENTORIENT(boyGObj), lim)) {
            iosOmSendMail(boyGObj, 21, gobj);
        }
        if (_DistSqGV(p, cw->rootPos) < 900.0f) {
            iosOmSendMail(boyGObj, 166, gobj);
        }
    }

    if (mode != cw->mode) {
        switch (mode) {
        case 2:
            initPendulum(gobj);
            cw->pdl.f34 = 10.0f;
            break;
        case 6:
            initPendulum(gobj);
            cw->pdl.f34 = 5.0f;
            break;
        }
        cw->mode = mode;
    }

    if (debug_font_flag & 1) {
        debug_Printf(10, chainDebugY += 10, 0x0FFFFFFF, "%d\n", mode);
    }
    /* the plumb index is read as the record's member: ROM loads it ahead of
     * the counter store, which alias.c allows only for a struct member
     * against a fixed scalar */
    if (debug_font_flag & 1) {
        debug_Printf(10, chainDebugY += 10, 0x0FFFFFFF, "plumb = %d\n",
                     ((ChainRecord *)cw)->holdNode);
    }

    switch (mode) {
    case 1:
        if (cw->hold == 0 && cw->fC0 != 0) {
            chain_simulate_stop((int)gobj);
        } else {
            chain_simulate_free((int)gobj);
        }
        break;
    case 2:
        chain_simulate_hangstart(gobj);
        break;
    case 3:
    case 11:
        chain_simulate_term_loop(gobj);
        break;
    case 9:
        chain_simulate_term_ropeturn(gobj);
        break;
    case 4:
        chain_set_charachara(gobj, 20.0f);
        chain_simulate_term_swingready(gobj);
        break;
    case 5:
        chain_simulate_term_swingstart(gobj);
        break;
    case 6:
        chain_simulate_term(gobj);
        break;
    case 8:
        chain_set_charachara(gobj, 10.0f);
        chain_simulate_term_down(gobj);
        break;
    case 7:
        chain_set_charachara(gobj, 20.0f);
        chain_simulate_term_moveup(gobj);
        break;
    default:
        chain_simulate_term_free(gobj);
        break;
    }

    if (cw->hold != 0) {
        sub = *(char **)((char *)boyGObj + 0x164);
        *(int *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->i + 0x420) = 0;
        TestChainUpDown(gobj, cw->owner);

        /* 0x130..0x138 of the extension is a float vector (cleared here and in
         * case 2 beside the float stores at 0x410..0x418) */
        switch (mode) {
        case 8:
            *(float *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->i + 0x130) = 0.0f;
            *(float *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->i + 0x134) = 0.0f;
            *(float *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->i + 0x138) = 0.0f;
            SetChainRootUpdateMode((char *)boyGObj, 2, &cw->node[cw->holdNode].x);
            break;
        case 7:
        case 10:
            SetChainRootUpdateMode((char *)boyGObj, 2, &cw->node[cw->holdNode].x);
            break;
        case 3:
        case 9:
            SetChainRootUpdateMode((char *)boyGObj, 3, &cw->node[cw->holdNode].x);
            break;
        case 2:
            if (sub != 0) {
                float *nd = (float *)((cw->holdNode << 5) + (int)cw->node);
                float h;

                *(float *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->i + 0x130) = 0.0f;
                *(float *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->i + 0x134) = 0.0f;
                *(float *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->i + 0x138) = 0.0f;
                *(float *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->i + 0x410) = nd[0];
                *(float *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->i + 0x414) = nd[1];
                *(float *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->i + 0x418) = nd[2];
                h = *(float *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->i + 0x4AC);
                if (h < 3.0f) {
                    *(int *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->i + 0x420) = -1;
                    ropeInterRate = 0.5f;
                } else if (h < 10.0f) {
                    *(int *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->i + 0x420) = -1;
                    ropeInterRate = 1.0f;
                } else {
                    *(int *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->i + 0x420) = 1;
                }
            }
            break;
        default:
            if (sub != 0) {
                CopyVector((char *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->i + 0x410),
                           &cw->node[cw->holdNode]);
                *(int *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->i + 0x420) = 1;
            }
            break;
        }
    }

    /* no node-pointer local: ROM re-reads cw->0xD0 after the first fptodp */
    if (cw->hold != 0) {
        if (debug_font_flag & 1) {
            debug_Printf(10, chainDebugY += 10, 0x0FFFFFFF, "%f/%f, %d\n", cw->pdl.f3C,
                         (cw->node)[0].y - ((ChainNode *)((cw->holdNode << 5) + (int)cw->node))->y,
                         cw->holdNode);
        }
    }

    cw->fC0 = 0;

    if (moved == 0 && cw->pdl.f34 < 5.0f) {
        cw->fC0 = 1;
        for (i = 0; i < cw->nodes; i++) {
            /* clang-format off */
            v[0] = cw->rootPos[0]; v[1] = cw->rootPos[1]; v[2] = cw->rootPos[2];
            /* clang-format on */
            v[1] = v[1] + (float)i * 50.0f;
            if (!(_DistSqGV(v, &(cw->node)[i]) < 9.0f)) {
                cw->fC0 = 0;
                break;
            }

            if (1.0f < (cw->node)[i].vx * (cw->node)[i].vx + (cw->node)[i].vy * (cw->node)[i].vy +
                           (cw->node)[i].vz * (cw->node)[i].vz) {
                cw->fC0 = 0;
                break;
            }
        }
    }
}

void ChainDL(char *gobj)
{
    char q[0x10];
    char up[0x10];
    char d[0x10];
    char n[0x10];
    char dq[0x10];
    char *ext = (char *)GOBJ_SUB(gobj);
    ChainRecord *cw = *(ChainRecord **)(ext + 0x830);
    int i;

    memset(q, 0, 16);
    ((ChainVal *)(q + 0xC))->f = 1.0f;
    memset(up, 0, 16);
    ((ChainVal *)(up + 0x4))->f = 1.0f;

    for (i = 0; i < cw->nodes - 1; i++) {
        ChainNode *p = &(cw->node)[i];
        ChainNode *np = &(cw->node)[i + 1];

        _SubVector(d, np, p);
        _NormalizeVector(n, d);
        GetDifferencialQuaternionWithNoRegularize(dq, n, up);
        MultiQuaternion(q, dq, q);
        CopyVector(up, n);
        GetMatrixFromQuaternionPos((char *)GOBJ_SUB(gobj)->f_C + (i << 6), q, p);
    }
    p2o_DispVU1DObjMulti(ext);
}

static inline void ChainNodeSpan(ChainRecord *cw, float *pos, int *i0, int *i1)
{
    ChainNode *nd = cw->node;

    *i0 = (int)((pos[1] - nd[0].y) / 50.0f);
    *i1 = *i0 + 1;
    *i0 = *i0 < 2 ? 2 : (cw->nodes - 1 < *i0 ? cw->nodes - 1 : *i0);
    *i1 = *i1 < 2 ? 2 : (cw->nodes - 1 < *i1 ? cw->nodes - 1 : *i1);
}

void GetPositionOnTheChain(float *out, char *gobj, float *pos)
{
    float a[4];
    float b[4];
    int i0;
    int i1;
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(gobj)->f_830;
    ChainNode *nd;

    ChainNodeSpan(cw, pos, &i0, &i1);
    nd = cw->node;
    a[0] = nd[i0].x;
    a[1] = nd[i0].y;
    a[2] = nd[i0].z;
    b[0] = nd[i1].x;
    b[1] = nd[i1].y;
    b[2] = nd[i1].z;
    if (i0 != i1) {
        float r = (a[1] - pos[1]) / (a[1] - b[1]);

        if (r < 0.0f) {
            r = -r;
        }
        _InterGV(out, a, b, r, 1.0f - r);
    } else {
        out[0] = a[0];
        out[1] = a[1];
        out[2] = a[2];
    }
}

void PlumbPointUpdateChain(char *gobj, float *pos)
{
    float d[4];
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(gobj)->f_830;
    char *owner;
    int best = -1;
    float min = 3.40282347e+38f; /* FLT_MAX, a constant-pool word */
    int i;

    owner = cw->owner;
    sceVu0SubVector(d, pos, cw->node);
    cw->owner = owner;

    for (i = 0; i < cw->nodes; i++) {
        int n = (int)(pos[1] - (cw->node)[i].y);
        float t = (float)(n < 0 ? -n : n);

        if (t < min) {
            min = t;
            best = i;
        }
    }
    if (best == -1) {
        debug_assert(__FILE__, 1675);
        __assert(__FILE__, 1675, "nearestNode!=-1");
    }
    cw->holdNode = best;
    cw->holdNode =
        cw->holdNode < 2 ? 2 : (cw->nodes - 1 < cw->holdNode ? cw->nodes - 1 : cw->holdNode);

    _GetCorrectOrientOfChain((float *)cw->pdl.orient, gobj, (float *)test_CURRENTORIENT(owner));

    ((ChainVal *)&cw->pdl.f3C)->f = (float)cw->holdNode * 50.0f;
}

/* the climb work the chain-climb modes share: the focus node point, the target
 * point the root is interpolated towards, the interpolation phase, the
 * motion's frame count and the mode the previous call left behind.
 * Reconstructed from the offsets TestChainUpDown uses. */
typedef struct {
    /* 0x00 */ sceVu0FVECTOR node;
    /* 0x10 */ sceVu0FVECTOR target;
    /* 0x20 */ float phase;
    /* 0x24 */ int frames;
    /* 0x28 */ int prev;
} ChainClimbWork;

/* the climb work's storage, twelve words reached through ChainClimbWork
 * casts (the phase updates and the mode store in TestChainUpDown rebuild the
 * pointer from the symbol each time, which a cast of storage of another type
 * gives and a ChainClimbWork object would fold away); the mode word at 0x28
 * starts at -1.  MAIN.MAP names nothing in chain.o's .data, so the name is
 * ours */
static int chainClimb[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0};

/* kept local: float * (void *) here, void * (void *) in commonact.h */
extern float *test_CURRENTROOT(void *a0);
/* the per-motion frame-count records, indexed by the motion id at ext + 0x4A0 */
/* kept local: this TU's uses of these do not fit the prototypes their own
 * headers carry */
/* kept local: void (float, void *, int, int, int) here, void (int *, int, int, int, float) in camera-editor.h */
extern void debug_NMarker(float size, void *pos, int r, int g, int b);

/* chain.c:1777-1987 in the listing: the two climb helpers and TestChainUpDown, laid out on its lines */
/* clang-format off */
static inline void SetChainClimbNodePoint(char *obj, ChainClimbWork *rec)
{
    int n = GetSkeltonFocusNode(obj, 0x23);
    rec->node[0] = *(float *)(n * 64 + ((ChainExtPtr *)(((ChainExtPtr *)(obj + 0x15C))->p + 0xC))->i + 0x30); rec->node[1] = *(float *)(n * 64 + ((ChainExtPtr *)(((ChainExtPtr *)(obj + 0x15C))->p + 0xC))->i + 0x34); rec->node[2] = *(float *)(n * 64 + ((ChainExtPtr *)(((ChainExtPtr *)(obj + 0x15C))->p + 0xC))->i + 0x38);
}

static inline float *PushChainClimbRoot(char *obj, float *pos, float *out, float *ofs, float fwd, float side)
{
    /* pushes the root out from the chain point (fwd along the orientation, side
     * across it) and returns the pushed point.  Both work vectors are the
     * caller's: ROM's frame has sp+0x30/0x40 and sp+0x50/0x60 and no other slot.
     * RECONSTRUCTION: the bytes pin only that the last call is not a sibling call
     * (a void helper ending in one is never inlined); they cannot tell this
     * returned point, unused by every caller, from a once-run loop around it */
    sceVu0ScaleVector(out, test_CURRENTORIENT(obj), fwd);
    sceVu0AddVector(out, pos, out);



    sceVu0ScaleVector(ofs, test_CURRENTORIENT(obj), side);
    _ApplyRyGV(ofs, 1.5707964f);
    sceVu0AddVector(out, out, ofs);








    debug_NMarker(100.0f, out, 0, 0, 0xFF);

    SetDirectRootPositionNoFittingWithNodePoint(obj, 0x23, out, 1.0f);
    return out;
}

/* Climbing the chain: moves the boy's root between the chain's node points.
 * TestChainUpDown's own brace is on the listing's line 1826 (the gobj
 * parameter copy's row), so the climb-mode selector (1827-1849) is a nested
 * function at its head, after the brace and before the parent's first
 * declarations: it reads the action record's 0x34 state through the captured
 * boy, and that capture is what gives boy its home at sp+0, below the six
 * vectors (a file-scope helper cannot: nothing else allocates a parameter's
 * slot before the locals).  Its parameter is the motion id, whose load lands
 * on the helper's brace line (1828) while the extension load stays on the
 * call line (1869).  The node-point and push helpers (1777-1811) precede the
 * function at file scope.  The region is laid on the listing's lines, one
 * offset from 1777 to 1987, and fenced from clang-format. */
void TestChainUpDown(char *gobj, char *boy)
{
    inline int GetChainClimbMode(int motion)
    {
        int mode = -1;
        switch (motion) {
        case 119:
            mode = 4; if (*(int *)((char *)GOBJ_ACT(boy) + 0x34) != 0x3F) {
                mode = 0;
            }

            break;
        case 120:
            mode = 1;
            break;

        case 121:
            mode = 2;
            break;
        case 122:
            mode = 3;
            break;
        }
        return mode;
    }

    float v[4], org[4], w[4], d[4], hw[4], hd[4];
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(gobj)->f_830;
    char *sub = (char *)GOBJ_ACT(boy);

    /* Each arm has its own pointer to the climb work, set on the arm's first
     * test (ROM rebuilds it there in every arm and lets it die before the
     * phase update: one set per pointer gives it the symbol as its known
     * value), and every read of an extension's 0x15C slot goes through the
     * ChainExtPtr union as in the node-point helper.  The listing's lines
     * without rows (1854-1868, 1874-1875, 1886-1888, 1894-1897, 1901-1905,
     * 1930-1933, 1938-1940) held nothing the object records. */







    int mode = GetChainClimbMode(*(int *)((char *)GOBJ_SUB(boy) + 0x4A0));

    switch (mode) {
    case 4: {
        ChainClimbWork *rec;


        org[0] = test_CURRENTROOT(boyGObj)[0]; org[1] = test_CURRENTROOT(boyGObj)[1]; org[2] = test_CURRENTROOT(boyGObj)[2];

        rec = (ChainClimbWork *)chainClimb; if (rec->prev != mode) {
            rec->phase = 0.0f;
            rec->frames = (int)(float)*motionTable[*(int *)(((ChainExtPtr *)(boy + 0x15C))->i + 0x4A0)];
            SetChainClimbNodePoint(boy, rec);
            rec->target[0] = rec->node[0]; rec->target[2] = rec->node[2];
            rec->target[1] = rec->node[1] - 100.0f;
        }
        _InterGV(v, rec->node, rec->target, rec->phase, (float)rec->frames - rec->phase);



        v[1] = v[1] < cw->rootPos[1] ? cw->rootPos[1] : (cw->f90[1] < v[1] ? cw->f90[1] : v[1]);

        PushChainClimbRoot(boy, v, w, d, -10.0f, 3.0f);

        ((ChainClimbWork *)chainClimb)->phase = ((ChainClimbWork *)chainClimb)->phase + 1.0f;




        w[0] = test_CURRENTROOT(boyGObj)[0]; w[1] = test_CURRENTROOT(boyGObj)[1]; w[2] = test_CURRENTROOT(boyGObj)[2];
        w[1] = org[1] + *(float *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->i + 0x144);
        SetDirectRootPositionNoFitting(boyGObj, w);





    } break;

    case 0:
    case 1: {
        ChainClimbWork *rec;

        org[0] = test_CURRENTROOT(boyGObj)[0]; org[1] = test_CURRENTROOT(boyGObj)[1]; org[2] = test_CURRENTROOT(boyGObj)[2];

        rec = (ChainClimbWork *)chainClimb; if (rec->prev != mode) {
            rec->phase = 0.0f;
            rec->frames = (int)(float)*motionTable[*(int *)(((ChainExtPtr *)(boy + 0x15C))->i + 0x4A0)];
            SetChainClimbNodePoint(boy, rec);
            rec->target[0] = rec->node[0]; rec->target[2] = rec->node[2];
            rec->target[1] = rec->node[1] - 100.0f;
        }
        _InterGV(v, rec->node, rec->target, rec->phase, (float)rec->frames - rec->phase);

        GetPositionOnTheChain(v, gobj, v);

        v[1] = v[1] < cw->f80[1] ? cw->f80[1] : (cw->f90[1] < v[1] ? cw->f90[1] : v[1]);

        PushChainClimbRoot(boy, v, w, d, mode == 0 ? -15.0f : -10.0f, mode == 0 ? -3.0f : -10.0f);

        ((ChainClimbWork *)chainClimb)->phase = ((ChainClimbWork *)chainClimb)->phase + 30.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);




        w[0] = test_CURRENTROOT(boyGObj)[0]; w[1] = test_CURRENTROOT(boyGObj)[1]; w[2] = test_CURRENTROOT(boyGObj)[2];
        w[1] = org[1] + *(float *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->i + 0x144);
        w[1] = w[1] < cw->rootPos[1] + 150.0f ? cw->rootPos[1] + 150.0f : (cw->f90[1] < w[1] ? cw->f90[1] : w[1]);
        SetDirectRootPosition(boyGObj, w);



        PlumbPointUpdateChain(gobj, v);

    } break;
    case 2: case 3: {
        ChainClimbWork *rec;
        rec = (ChainClimbWork *)chainClimb; if (rec->prev != mode) {
            rec->phase = 0.0f;
            rec->frames = (int)(float)*motionTable[*(int *)(((ChainExtPtr *)(boy + 0x15C))->i + 0x4A0)];
            SetChainClimbNodePoint(boy, rec);
            rec->target[0] = rec->node[0]; rec->target[2] = rec->node[2];
            rec->target[1] = rec->node[1] + 200.0f;
        }


        _InterGV(v, rec->node, rec->target, rec->phase, (float)rec->frames - rec->phase);

        GetPositionOnTheChain(v, gobj, v);

        v[1] = v[1] < cw->f80[1] ? cw->f80[1] : (cw->f90[1] < v[1] ? cw->f90[1] : v[1]);

        PushChainClimbRoot(boy, v, hw, hd, -20.0f, -5.0f);
        ((ChainClimbWork *)chainClimb)->phase = ((ChainClimbWork *)chainClimb)->phase + 1.0f;
        PlumbPointUpdateChain(gobj, v);
    } break;
    default: { ChainClimbWork *rec;
        rec = (ChainClimbWork *)chainClimb; if ((unsigned int)rec->prev < 2) {

            int n = GetSkeltonFocusNode(boyGObj, 0x16);
            v[0] = *(float *)(n * 64 + ((ChainExtPtr *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->p + 0xC))->i + 0x30); v[1] = *(float *)(n * 64 + ((ChainExtPtr *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->p + 0xC))->i + 0x34); v[2] = *(float *)(n * 64 + ((ChainExtPtr *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->p + 0xC))->i + 0x38);
            PlumbPointUpdateChain(*(char **)(sub + 0x190), v);
        }
        if ((unsigned int)(rec->prev - 2) < 2) {

            int n = GetSkeltonFocusNode(boyGObj, 0x16);
            v[0] = *(float *)(n * 64 + ((ChainExtPtr *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->p + 0xC))->i + 0x30); v[1] = *(float *)(n * 64 + ((ChainExtPtr *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->p + 0xC))->i + 0x34); v[2] = *(float *)(n * 64 + ((ChainExtPtr *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->p + 0xC))->i + 0x38);
            PlumbPointUpdateChain(*(char **)(sub + 0x190), v);
        }

        if (*(int *)(sub + 0x34) != 59) {

            _GetCorrectOrientOfChain((float *)cw->pdl.orient, gobj, (float *)test_CURRENTORIENT(boy));
        }
    } break;
    }

    ((ChainClimbWork *)chainClimb)->prev = mode;
}

/* clang-format on */

void SetChainRootUpdateMode(char *gobj, int mode, float *pos)
{
    GOBJ_SUB(gobj)->f_420 = mode;
    ((ChainVal *)((int)GOBJ_SUB(gobj) + 0x410))->f = pos[0];
    ((ChainVal *)((int)GOBJ_SUB(gobj) + 0x414))->f = pos[1];
    ((ChainVal *)((int)GOBJ_SUB(gobj) + 0x418))->f = pos[2];
    if (mode == 3) {
        SetDirectRootPositionNoFittingWithNodePoint(gobj, 0x16, pos, 1.0f);
    }
}

void HoldChain(char *a0)
{
    char *p = (char *)GOBJ_SUB(a0)->f_830;
    StartPendulum(a0);
    *(char *)(p + 0x60) = 1;
}

void ReleaseChain(char *a0)
{
    *(char *)((char *)GOBJ_SUB(a0)->f_830 + 0x60) = 0;
}

void GetChainPendulum(char *a0, float *a, float *b, float *c)
{
    char *p = (char *)GOBJ_SUB(a0)->f_830;
    *a = *(float *)(p + 0x30);
    *b = *(float *)(p + 0x34);
    if (*(float *)(p + 0x48) < *(float *)(p + 0x34)) {
        *b = *(float *)(p + 0x48);
    }
    *c = *(float *)(p + 0x40);
}

void IncreasePdlChain(char *a0)
{
    *(float *)((char *)GOBJ_SUB(a0)->f_830 + 0x44) = 0.1f;
}

void DecreasePdlChain(char *a0)
{
    *(float *)((char *)GOBJ_SUB(a0)->f_830 + 0x44) = (float)debug_chain_slow_speed * 0.5f * -0.1f;
}

void PlumbOrientUpdateChain(char *a0, float *src)
{
    char *p = (char *)GOBJ_SUB(a0)->f_830;
    *(float *)(p + 0x20) = src[0];
    *(float *)(p + 0x24) = src[1];
    *(float *)(p + 0x28) = src[2];
}

int isBottomOfChain(char *a0)
{
    char *p = (char *)GOBJ_SUB(a0)->f_830;
    return *(int *)(p + 0x68) == *(int *)(p + 0x74) - 1;
}

int isStopChain(char *a0)
{
    return *(unsigned char *)((char *)GOBJ_SUB(a0)->f_830 + 0xC0);
}

void GetChainClimbOrient(float *dst, char *a0)
{
    char *p = (char *)GOBJ_SUB(a0)->f_830;
    dst[0] = *(float *)(p + 0xB0);
    dst[1] = *(float *)(p + 0xB4);
    dst[2] = *(float *)(p + 0xB8);
}

int CheckChainClimbablePos(char *a0)
{
    char *p = (char *)GOBJ_SUB(a0)->f_830;

    if (*(unsigned char *)(p + 0xA0) != 0 && *(int *)(p + 0x68) < 3)
        return 1;
    return 0;
}

typedef struct {
    int a, b, c;
} ClimbCol;

void GetChainClimbCollision(ClimbCol *dst, char *a0)
{
    *dst = *(ClimbCol *)((char *)GOBJ_SUB(a0)->f_830 + 0xA4);
}

void SetChainParentGObj(char *a0, void *a1)
{
    *(void **)((char *)GOBJ_SUB(a0)->f_830) = a1;
}

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * GetChainDirCorrectVal's lines into _GetCorrectOrientOfChain, so it is a
 * public `inline` of the deferred tail; until the tail's asm members are C the
 * copy is emitted here as a plain function at its ROM position and the caller
 * inlines the static stand-in getChainDirCorrectVal, which collapses at layout. */
int GetChainDirCorrectVal(char *a0, int *a1)
{
    char *p = (char *)GOBJ_SUB(a0)->f_830;
    *a1 = (int)(*(float *)(p + 0x70) * 180.0f / 3.1415927f);
    return *(unsigned char *)(p + 0x6C);
}

static inline int getChainDirCorrectVal(char *a0, int *a1)
{
    char *p = (char *)GOBJ_SUB(a0)->f_830;
    *a1 = (int)(*(float *)(p + 0x70) * 180.0f / 3.1415927f);
    return *(unsigned char *)(p + 0x6C);
}

/* kept local: float * (void *) here, void * (void *) in commonact.h */
extern float *test_CURRENTROOT(void *a0);

void GetRootPositionHandExtra(void *a0, float *a1)
{
    a1[0] = test_CURRENTROOT(a0)[0];
    a1[1] = test_CURRENTROOT(a0)[1];
    a1[2] = test_CURRENTROOT(a0)[2];
    a1[1] -= 50.0f;
}

void InitPendulum(char *a0)
{
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(a0)->f_830;
    float a = (float)debug_chain_cycle_speed * -0.2f + 2.0f;
    float y;

    a = a < 0.1f ? 0.1f : (a > 2.0f ? 2.0f : a);

    y = (float)(int)(a * 6.0f * FSqrt(cw->pdl.f3C / 2.5f) * 8.0f / 10.0f);

    cw->pdl.f40 = y;
    cw->pdl.f40 = cw->pdl.f40 < 1.0f ? 1.0f : (cw->pdl.f40 > 255.0f ? 255.0f : cw->pdl.f40);

    cw->pdl.f38 = cw->pdl.f40 * 0.5f;
    cw->pdl.period = 360.0f;
    cw->pdl.swing = 1;
}

void LockChainGeo(char *a0)
{
    *(char *)((char *)GOBJ_SUB(a0)->f_830 + 0xCC) = 1;
}

void UnLockChainGeo(char *a0)
{
    *(char *)((char *)GOBJ_SUB(a0)->f_830 + 0xCC) = 0;
}

float GetChainHangRange(char *a0)
{
    return *(float *)((char *)GOBJ_SUB(a0)->f_830 + 0xC8);
}

float GetChainLength(char *a0)
{
    return (float)(*(int *)((char *)GOBJ_SUB(a0)->f_830 + 0x74) - 1) * 50.0f;
}

void EnableChainHang(char *a0)
{
    *(char *)((char *)GOBJ_SUB(a0)->f_830 + 0xCD) = 1;
}

void UnableChainHang(char *a0)
{
    *(char *)((char *)GOBJ_SUB(a0)->f_830 + 0xCD) = 0;
}

int IsAbleChainHang(char *a0)
{
    return *(unsigned char *)((char *)GOBJ_SUB(a0)->f_830 + 0xCD);
}

void ChainPositionReset(char *a0)
{
    float pos[4];
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(a0)->f_830;

    UpdateRootMatrix(a0);
    GetRootPosition(pos, a0);
    ResetChainNodes(cw, pos);
}

void _GetCorrectOrientOfChain(float *out, char *gobj, float *dir)
{
    float v[4];
    int deg;

    if (getChainDirCorrectVal(gobj, &deg) != 0) {
        float pi = 3.1415927f;
        int d;

        memset(v, 0, 16);
        v[2] = 1.0f;
        d = (int)(_GetDirection(dir) / pi * 180.0f);
        d = RoundDegGV(d - deg);
        d = AlignDegGV(d);
        d = RoundDegGV(deg + d);
        _ApplyRyGV(v, (float)d * pi / 180.0f);
        out[0] = v[0];
        out[1] = v[1];
        out[2] = v[2];
    } else {
        out[0] = dir[0];
        out[1] = dir[1];
        out[2] = dir[2];
    }
}

void chain_sub_simulate(int a0, ChainNode *nd, int from, int to, unsigned char flag, int flag2,
                        float grav, float len, float damp)
{
    float d[4];
    float t[4];
    ChainNode *p;
    ChainNode *q;
    ChainNode *e;
    int step;
    float l;

    step = from < to ? 1 : -1;
    e = nd + to;
    q = nd + from;

    for (p = q + step; p != e; p += step, q += step) {
        if (flag) {
            p->vy += grav;
            sceVu0SubVector(d, p, q);
            correct_vector(&p->vx, d);
        } else {
            p->vy += grav;
        }
        sceVu0ScaleVector(&p->vx, &p->vx, damp);
        sceVu0AddVector(t, p, &p->vx);
        sceVu0SubVector(d, t, q);
        l = FSqrt(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
        if (l == 0.0f)
            continue;
        if (l < len && d[1] < 0.0f)
            continue;
        sceVu0ScaleVector(d, d, len / l);
        sceVu0AddVector(t, q, d);
        sceVu0SubVector(&p->vx, t, p);
        p->x = t[0];
        p->y = t[1];
        p->z = t[2];
    }
}

void chain_sub_pendulum(char *base, int n, void *a2)
{
    char *p;
    int i = 0;
    if (n < 0) {
        return;
    }
    p = base;
    do {
        _InterGV(p, base, a2, (float)i, (float)(n - i));
        i++;
        p += 0x20;
    } while (i <= n);
}

int GetChainNearestNodePosition(float *out, char *gobj, float *p)
{
    ChainRecord *cw = (ChainRecord *)GOBJ_SUB(gobj)->f_830;

    float best = 3.40282347e+38f; /* FLT_MAX, a constant-pool word */
    int ret = 0;
    int i;

    for (i = 2; i <= cw->nodes - 1; i++) {
        float d = _DistSqGV(p, (char *)cw->node + i * 32);

        if (d < best) {
            float *e = (float *)(i * 32 + (int)cw->node);
            out[0] = e[0];
            out[1] = e[1];
            out[2] = e[2];
            best = d;
            ret = 1;
        }
    }
    return ret;
}
