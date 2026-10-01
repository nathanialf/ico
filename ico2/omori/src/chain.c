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
#include "chain.h"
#include "memory.h"
#include "ios.h"
#include "commonact.h"
#include "obj_manager.h"
#include "camera-editor.h"

typedef struct {
    float x, y, z, w;
    float vx, vy, vz, vw;
} ChainNode;

/* One word of a chain record or of a chain vector: the chain code writes these
 * slots as float and reads them as int (and the other way round), so the word
 * itself is a union. */
typedef union ChainVal {
    int i;
    float f;
} ChainVal;

/* The pendulum block at 0x20 of a chain record: the swing orientation, the
 * swing state, the swing period at 0x48 (360 at every restart), the swing
 * limit at 0x4C and the swinging flag at 0x50.  Reconstructed from the offsets
 * the chain code uses; the vector makes it 16-aligned and 0x40 long. */
typedef struct { /* field names derived */
    /* 0x20 */ sceVu0FVECTOR orient;
    /* 0x30 */ float angle;
    /* 0x34 */ float amp;
    /* 0x38 */ float phase;
    /* 0x3C */ float length;
    /* 0x40 */ float cycle;
    /* 0x44 */ float ampSpeed;
    /* 0x48 */ float period;
    /* 0x4C */ float limit;
    /* 0x50 */ unsigned char swing;
} ChainPendulum;

/* The head of a chain record, 0xE0 bytes, the node array following it. */
typedef struct { /* field names derived */
    /* 0x00 */ int root;
    /* 0x04 */ int rootNode;
    /* 0x10 */ sceVu0FVECTOR rootPos;
    /* 0x20 */ ChainPendulum pdl;
    /* 0x60 */ unsigned char hold;
    /* 0x64 */ char *owner;
    /* 0x68 */ int holdNode;
    /* 0x6C */ unsigned char hasDirCorrect;
    /* 0x70 */ float dirCorrect;
    /* 0x74 */ int nodes;
    /* 0x78 */ int mode; /* derived name */
    /* 0x80 */ sceVu0FVECTOR node2Pos;
    /* 0x90 */ sceVu0FVECTOR endPos;
    /* 0xA0 */ unsigned char wallHit;
    /* 0xA4 */ float wallPos[2];
    /* 0xAC */ char *wall;
    /* 0xB0 */ sceVu0FVECTOR wallOrient;
    /* 0xC0 */ unsigned char stopped;
    /* 0xC4 */ int count;
    /* 0xC8 */ float angle;
    /* 0xCC */ unsigned char locked;
    /* 0xCD */ unsigned char hangable;
    /* 0xD0 */ ChainNode *node;
} ChainRecord;

int UpdateRootPosition(char *gobj)
{
    float pos[4];
    ChainRecord *cw = GOBJ_SUB(gobj)->work;
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
    cw->node2Pos[0] = nd[2].x;
    cw->node2Pos[1] = nd[2].y;
    cw->node2Pos[2] = nd[2].z;
    cw->endPos[0] = nd[cw->nodes - 1].x;
    cw->endPos[1] = nd[cw->nodes - 1].y;
    cw->endPos[2] = nd[cw->nodes - 1].z;
    return moved;
}

extern void __assert(char *file, int line, char *expr);
void _GetCorrectOrientOfChain(float *out, char *gobj, float *dir);

/* InitPendulum's body, for StartPendulum above its definition */
static inline void initPendulum(char *gobj) /* derived name */
{
    ChainRecord *cw = GOBJ_SUB(gobj)->work;
    float a = (float)debug_chain_cycle_speed * -0.2f + 2.0f;
    float y;

    a = a < 0.1f ? 0.1f : (a > 2.0f ? 2.0f : a);

    y = (float)(int)(a * 6.0f * FSqrt(cw->pdl.length / 2.5f) * 8.0f / 10.0f);

    cw->pdl.cycle = y;
    cw->pdl.cycle = cw->pdl.cycle < 1.0f ? 1.0f : (cw->pdl.cycle > 255.0f ? 255.0f : cw->pdl.cycle);

    cw->pdl.phase = cw->pdl.cycle * 0.5f;
    cw->pdl.period = 360.0f;
    cw->pdl.swing = 1;
}

/* K&R definition: HoldChain calls StartPendulum with the gobj alone. */
void StartPendulum(gobj, owner, pos) char *gobj;

char *owner;

float *pos;

{
    float d[4];
    ChainRecord *cw = GOBJ_SUB(gobj)->work;
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

    ((ChainVal *)&cw->pdl.length)->f = (float)cw->holdNode * 50.0f;

    initPendulum(gobj);
}

/* the debug trace line: every chain trace steps it by 10 and ChainGeo resets
 * it */
static int chainDebugY; /* derived name */

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
    ChainRecord *cw = GOBJ_SUB(gobj)->work;

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

/* The sixth integer parameter is passed by both call sites (always 0) and
 * never read by the body. */
extern void chain_sub_simulate(int a0, ChainNode *nd, int from, int to, unsigned char flag,
                               int flag2, float grav, float len, float damp);

static inline void ChainPendulumSwing(float *dst, ChainRecord *cw, float *orient)
{
    float ang = cw->pdl.angle;
    float len = cw->pdl.length;
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
    ChainRecord *cw = GOBJ_SUB(a0)->work;

    pendulum_Process(cw->pdl.orient, collisionCheck((char *)a0));
    ChainPendulumSwing(pos, cw, (float *)cw->pdl.orient);
    sceVu0AddVector(pos, cw->node, pos);
    chain_sub_pendulum((char *)cw->node, cw->holdNode, pos);
    chain_sub_simulate(a0, cw->node, cw->holdNode, cw->nodes, 1, 0, 20.0f, 50.0f, 0.6f);
}

void chain_simulate_term_ropeturn(int a0)
{
    ChainRecord *cw = GOBJ_SUB(a0)->work;

    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_term_ropeturn\n");
    }
    cw->pdl.ampSpeed = -0.4f;
    chain_simulate_term_simple(a0);
}

void chain_simulate_term_loop(int a0)
{
    ChainRecord *cw = GOBJ_SUB(a0)->work;

    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_term_loop\n");
    }
    if (cw->pdl.amp < 0.5) {
        cw->pdl.ampSpeed = -0.01f;
    } else if (cw->pdl.amp < 1.0) {
        cw->pdl.ampSpeed = -0.05f;
    } else {
        cw->pdl.ampSpeed = -0.15f;
    }
    chain_simulate_term_simple(a0);
}

void chain_simulate_term_swingready(int a0)
{
    ChainRecord *cw = GOBJ_SUB(a0)->work;

    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_term_swingready\n");
    }
    if (cw->pdl.amp < 0.5) {
        cw->pdl.ampSpeed = -0.29999998f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
    } else if (cw->pdl.amp < 1.0) {
        cw->pdl.ampSpeed = -1.5f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
    } else {
        cw->pdl.ampSpeed = -4.5f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
    }
    chain_simulate_term_simple(a0);
}

void chain_simulate_term_swingstart(int a0)
{
    ChainRecord *cw = GOBJ_SUB(a0)->work;
    float h;

    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_term_swingstart\n");
    }

    h = GOBJ_SUB(boyGObj)->animFrame;

    if (h < 20.0f) {
        if (cw->pdl.amp < 0.3) {
            cw->pdl.ampSpeed =
                -0.29999998f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
        } else if (cw->pdl.amp < 1.0) {
            cw->pdl.ampSpeed = -6.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
        } else {
            cw->pdl.ampSpeed = -9.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
        }
    } else {
        if (h >= 20.0 && h < 21.5) {
            cw->pdl.phase = 0.0f;
            cw->pdl.period = 360.0f;
        }
        cw->pdl.ampSpeed = 0.0f;
        cw->pdl.amp = 3.0f;

        cw->pdl.phase = cw->pdl.phase - 1.0f +
                        cw->pdl.cycle * 0.5f / 41.0f * 30.0f /
                            (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
    }
    chain_simulate_term_simple(a0);
}

void chain_simulate_term_moveup(int a0)
{
    float w[4];
    float v[4];
    ChainRecord *cw = GOBJ_SUB(a0)->work;
    float h;

    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_term_moveup\n");
    }
    if (cw->pdl.amp < 1.0f) {
        cw->pdl.amp = 1.0f;
        cw->pdl.ampSpeed = 0.0f;
    } else if (cw->pdl.amp < 2.0) {
        cw->pdl.ampSpeed = -0.05f;
    } else {
        cw->pdl.ampSpeed = -0.15f;
    }
    chain_simulate_term_simple(a0);
    h = GOBJ_SUB(boyGObj)->animFrame;
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
    ChainRecord *cw = GOBJ_SUB(a0)->work;

    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_term_free\n");
    }
    if (cw->pdl.amp < 0.5) {
        cw->pdl.ampSpeed = -0.01f;
    } else if (cw->pdl.amp < 2.0) {
        cw->pdl.ampSpeed = -0.05f;
    } else {
        cw->pdl.ampSpeed = -0.15f;
    }
    chain_simulate_term_simple(a0);
}

void chain_simulate_term_down(int a0)
{
    float w[4];
    float v[4];
    ChainRecord *cw = GOBJ_SUB(a0)->work;
    ChainNode *nd;
    ChainNode *next;
    float h;

    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        /* a 2001 copy and paste: this arm prints the sibling term's name */
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_term_free\n");
    }
    if (cw->pdl.amp < 0.5) {
        cw->pdl.ampSpeed = -0.01f;
    } else if (cw->pdl.amp < 2.0) {
        cw->pdl.ampSpeed = -0.05f;
    } else {
        cw->pdl.ampSpeed = -0.15f;
    }
    chain_simulate_term_simple(a0);
    h = GOBJ_SUB(boyGObj)->animFrame;
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
    ChainRecord *cw = GOBJ_SUB(a0)->work;

    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_hangstart\n");
    }
    cw->pdl.ampSpeed = -1.5f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
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
    ChainRecord *cw = GOBJ_SUB(a0)->work;

    ResetChainNodes(cw, (float *)cw->rootPos);
    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_stop\n");
    }
}

void chain_simulate_free(int a0)
{
    ChainRecord *cw = GOBJ_SUB(a0)->work;
    int i;

    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_free\n");
    }
    chain_sub_simulate(a0, cw->node, 0, cw->nodes, 1, 0, 10.0f, 50.0f, 0.675f);
    cw->pdl.amp = 0.0f;
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

/* K&R definition: the flag is an unsigned char promoted to int. */
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

/* the two templates a new chain geometry starts from, the pendulum block and
 * the record head */
static ChainPendulum chainPendulumDefault = {
    /* derived name */
    {0.0f, 0.0f, 0.0f, 0.0f}, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 360.0f, 45.0f, 1};

static ChainRecord chainRecordDefault = {
    /* derived name */
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

/* the gobj extension pointer, read as a pointer or as a word */
typedef union {
    char *p;
    int i;
    Sub15C *sub;
} ChainExtPtr;

/* the DObj entry flag word, the same union DObj.c's allocObjectData uses */
typedef union {
    long long ll;
    int i[2];
} ChainDObjFlags;

ChainRecord *InitChainGeo(char *gobj, ChainGeoReq *req)
{
    ChainRecord *cw;
    int n;
    int i;

    n = (int)(req->f24 / 50.0f + 0.5f);

    if (n < 2) {
        /* "the chain is too short (set it with the Y-scale of the placement table)" */
        debug_StdPrintfDummy("鎖の長さが短かすぎます(配置表のY-scaleで指定します)");
        debug_assert(__FILE__, 1178);
        __assert(__FILE__, 1178, "0");
    }

    cw = iosMallocDebug((void *)ios_partition_sugipon, (n << 5) + 0xE0, __FILE__, 1181);

    *(ChainRecTemplate *)cw = *(ChainRecTemplate *)&chainRecordDefault;

    cw->nodes = n;
    cw->node = (ChainNode *)(cw + 1);
    cw->holdNode = -1;
    if (req->f20 != -1.0f) {
        cw->angle = req->f20;
    }

    *(ChainPendTemplate *)&cw->pdl = *(ChainPendTemplate *)&chainPendulumDefault;

    cw->pdl.limit = req->f28;
    cw->pdl.limit = cw->pdl.limit < 5.0f ? 5.0f : (90.0f < cw->pdl.limit ? 90.0f : cw->pdl.limit);

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
            *(ChainHitPos *)cw->wallPos = *(ChainHitPos *)w.f80;
            cw->wall = (char *)w.hit;
            GetOrientOfWall(cw->wallOrient, w.hit, w.f80);
            cw->wallHit = 1;
        }
    } else {
        /* no wall: the hit position is cleared as two words */
        *(int *)&cw->wallPos[0] = 0;
        *(int *)&cw->wallPos[1] = 0;
        cw->wall = 0;
        cw->wallHit = 0;
    }

    if (req->f18 < 0.0f) {
        cw->hasDirCorrect = 0;
    } else {
        cw->hasDirCorrect = 1;
        cw->dirCorrect = req->f18;
    }

    if ((char *)((ChainExtPtr *)(gobj + 0x15C))->sub->nodeMtx != 0) {
        iosFree((void *)((int)(char *)((ChainExtPtr *)(gobj + 0x15C))->sub->nodeMtx & 0x0FFFFFFF));
    }
    if ((char *)((ChainExtPtr *)(gobj + 0x15C))->sub->nodeQuat != 0) {
        iosFree((void *)((int)(char *)((ChainExtPtr *)(gobj + 0x15C))->sub->nodeQuat & 0x0FFFFFFF));
    }
    *(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0xC) = 0;
    *(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x10) = 0;
    *(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0xC) =
        (char *)iosMallocDebug((void *)ios_partition_seki, (cw->nodes - 1) << 6, __FILE__, 1245);
    *(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x10) =
        (char *)iosMallocDebug((void *)ios_partition_seki, (cw->nodes - 1) << 4, __FILE__, 1245);
    ((ChainExtPtr *)(gobj + 0x15C))->sub->nodeNum = cw->nodes - 1;
    if ((char *)((ChainExtPtr *)(gobj + 0x15C))->sub->nodes != 0) {
        iosFree((void *)((int)(char *)((ChainExtPtr *)(gobj + 0x15C))->sub->nodes & 0x0FFFFFFF));
    }
    *(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x870) =
        (char *)iosMallocDebug((void *)ios_partition_seki, (cw->nodes - 1) * 80, __FILE__, 1245);

    for (i = 0; i < cw->nodes - 1; i++) {
        {
            char *e = (char *)(i * 80 + (int)(char *)((ChainExtPtr *)(gobj + 0x15C))->sub->nodes);
            ((ChainDObjFlags *)(e + 0x38))->ll &= ~1;
        }
        {
            char *e = (char *)(i * 80 + (int)(char *)((ChainExtPtr *)(gobj + 0x15C))->sub->nodes);
            ((ChainDObjFlags *)(e + 0x38))->ll &= ~2;
        }
        {
            char *e = (char *)(i * 80 + (int)(char *)((ChainExtPtr *)(gobj + 0x15C))->sub->nodes);
            *(float *)(e + 0x40) = 0.0f;
        }
        {
            char *e = (char *)(i * 80 + (int)(char *)((ChainExtPtr *)(gobj + 0x15C))->sub->nodes);
            *(float *)(e + 0x44) = 0.0f;
        }
        {
            char *e = (char *)(i * 80 + (int)(char *)((ChainExtPtr *)(gobj + 0x15C))->sub->nodes);
            *(float *)(e + 0x48) = 0.0f;
        }
        {
            char *e = (char *)(i * 80 + (int)(char *)((ChainExtPtr *)(gobj + 0x15C))->sub->nodes);
            *(float *)(e + 0x4C) = 1.0f;
        }
        {
            char *e = (char *)(i * 80 + (int)(char *)((ChainExtPtr *)(gobj + 0x15C))->sub->nodes);
            ((ChainDObjFlags *)(e + 0x38))->ll &= ~4;
        }
        {
            char *e = (char *)(i * 80 + (int)(char *)((ChainExtPtr *)(gobj + 0x15C))->sub->nodes);
            *(int *)(e + 0x30) = 0;
        }
        {
            char *e = (char *)(i * 80 + (int)(char *)((ChainExtPtr *)(gobj + 0x15C))->sub->nodes);
            *(float *)(e + 0x34) = 1.0f;
        }
        {
            char *e = (char *)(i * 80 + (int)(char *)((ChainExtPtr *)(gobj + 0x15C))->sub->nodes);
            *(short *)(e + 0x3A) = 0;
        }
        {
            char *e = (char *)(i * 80 + (int)(char *)((ChainExtPtr *)(gobj + 0x15C))->sub->nodes);
            *(float *)(e + 0x20) = 1.0f;
        }
        {
            char *e = (char *)(i * 80 + (int)(char *)((ChainExtPtr *)(gobj + 0x15C))->sub->nodes);
            *(float *)(e + 0x24) = 1.0f;
        }
        {
            char *e = (char *)(i * 80 + (int)(char *)((ChainExtPtr *)(gobj + 0x15C))->sub->nodes);
            *(float *)(e + 0x28) = 1.0f;
        }
    }
    *(short *)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x84C) = 2;

    return cw;
}

void chain_set_charachara(char *gobj, float amp)
{
    float v[4];
    ChainRecord *cw = GOBJ_SUB(gobj)->work;
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
    ChainRecord *cw = GOBJ_SUB(gobj)->work;
    int mode = 1;

    if (cw->hold != 0) {
        char *holder = cw->owner;
        int st = GOBJ_ACT(holder)->actMode;

        mode = 6;
        if (st != 58) {
            mode = st == 59 ? 9 : 3;
        }

        switch (GOBJ_SUB(holder)->motion) {
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

/* the hand-proximity probe down the chain, for ChainGeo; the caller reads the
 * result as one byte */
static inline unsigned char isChainHitByHand(char *gobj, float *p, float *v, float *o,
                                             float lim) /* derived name */
{
    ChainRecord *cw = GOBJ_SUB(gobj)->work;
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
    ChainRecord *cw = GOBJ_SUB(gobj)->work;
    char *sub;
    int mode;
    int moved;
    int i;

    chainDebugY = 250;

    if (cw->locked != 0) {
        return;
    }

    moved = UpdateRootPosition(gobj);

    mode = GetChainSimulateMode(gobj);

    if (boyGObj != 0) {
        float lim;

        lim = cw->angle;
        if (GOBJ_ACT(boyGObj)->actMode == 5 ||
            (((motionKind + GOBJ_SUB(boyGObj)->motion)->flags18C >> 11) & 1)) {
            lim = 70.0f;
        }

        GetRootPositionHandExtra(boyGObj, p);
        if (isChainHitByHand(gobj, p, v, (float *)test_CURRENTORIENT(boyGObj), lim)) {
            iosOmSendMail((char *)boyGObj, 21, (int)gobj);
        }
        if (_DistSqGV(p, cw->rootPos) < 900.0f) {
            iosOmSendMail((char *)boyGObj, 166, (int)gobj);
        }
    }

    if (mode != cw->mode) {
        switch (mode) {
        case 2:
            initPendulum(gobj);
            cw->pdl.amp = 10.0f;
            break;
        case 6:
            initPendulum(gobj);
            cw->pdl.amp = 5.0f;
            break;
        }
        cw->mode = mode;
    }

    if (debug_font_flag & 1) {
        debug_Printf(10, chainDebugY += 10, 0x0FFFFFFF, "%d\n", mode);
    }
    if (debug_font_flag & 1) {
        debug_Printf(10, chainDebugY += 10, 0x0FFFFFFF, "plumb = %d\n",
                     ((ChainRecord *)cw)->holdNode);
    }

    switch (mode) {
    case 1:
        if (cw->hold == 0 && cw->stopped != 0) {
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
        sub = (char *)GOBJ_ACT(boyGObj);
        ((ChainExtPtr *)((char *)boyGObj + 0x15C))->sub->ropeState = 0;
        TestChainUpDown(gobj, cw->owner);

        /* 0x130..0x138 of the extension is a float vector (cleared here and in
         * case 2 beside the float stores at 0x410..0x418) */
        switch (mode) {
        case 8:
            ((ChainExtPtr *)((char *)boyGObj + 0x15C))->sub->moveX = 0.0f;
            ((ChainExtPtr *)((char *)boyGObj + 0x15C))->sub->moveY = 0.0f;
            ((ChainExtPtr *)((char *)boyGObj + 0x15C))->sub->moveZ = 0.0f;
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

                ((ChainExtPtr *)((char *)boyGObj + 0x15C))->sub->moveX = 0.0f;
                ((ChainExtPtr *)((char *)boyGObj + 0x15C))->sub->moveY = 0.0f;
                ((ChainExtPtr *)((char *)boyGObj + 0x15C))->sub->moveZ = 0.0f;
                ((ChainExtPtr *)((char *)boyGObj + 0x15C))->sub->ropeBaseX = nd[0];
                ((ChainExtPtr *)((char *)boyGObj + 0x15C))->sub->ropeBaseY = nd[1];
                ((ChainExtPtr *)((char *)boyGObj + 0x15C))->sub->ropeBaseZ = nd[2];
                h = ((ChainExtPtr *)((char *)boyGObj + 0x15C))->sub->animFrame;
                if (h < 3.0f) {
                    ((ChainExtPtr *)((char *)boyGObj + 0x15C))->sub->ropeState = -1;
                    ropeInterRate = 0.5f;
                } else if (h < 10.0f) {
                    ((ChainExtPtr *)((char *)boyGObj + 0x15C))->sub->ropeState = -1;
                    ropeInterRate = 1.0f;
                } else {
                    ((ChainExtPtr *)((char *)boyGObj + 0x15C))->sub->ropeState = 1;
                }
            }
            break;
        default:
            if (sub != 0) {
                CopyVector((char *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->i + 0x410),
                           &cw->node[cw->holdNode]);
                ((ChainExtPtr *)((char *)boyGObj + 0x15C))->sub->ropeState = 1;
            }
            break;
        }
    }

    if (cw->hold != 0) {
        if (debug_font_flag & 1) {
            debug_Printf(10, chainDebugY += 10, 0x0FFFFFFF, "%f/%f, %d\n", cw->pdl.length,
                         (cw->node)[0].y - ((ChainNode *)((cw->holdNode << 5) + (int)cw->node))->y,
                         cw->holdNode);
        }
    }

    cw->stopped = 0;

    if (moved == 0 && cw->pdl.amp < 5.0f) {
        cw->stopped = 1;
        for (i = 0; i < cw->nodes; i++) {
            /* clang-format off */
            v[0] = cw->rootPos[0]; v[1] = cw->rootPos[1]; v[2] = cw->rootPos[2];
            /* clang-format on */
            v[1] = v[1] + (float)i * 50.0f;
            if (!(_DistSqGV(v, &(cw->node)[i]) < 9.0f)) {
                cw->stopped = 0;
                break;
            }

            if (1.0f < (cw->node)[i].vx * (cw->node)[i].vx + (cw->node)[i].vy * (cw->node)[i].vy +
                           (cw->node)[i].vz * (cw->node)[i].vz) {
                cw->stopped = 0;
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
    Sub15C *ext = GOBJ_SUB(gobj);
    ChainRecord *cw = ext->work;
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
        GetMatrixFromQuaternionPos((char *)GOBJ_SUB(gobj)->nodeMtx + (i << 6), q, p);
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
    ChainRecord *cw = GOBJ_SUB(gobj)->work;
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
    ChainRecord *cw = GOBJ_SUB(gobj)->work;
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

    ((ChainVal *)&cw->pdl.length)->f = (float)cw->holdNode * 50.0f;
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
 * casts; the mode word at 0x28 starts at -1 */
static int chainClimb[12] = {/* derived name */ 0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             0,
                             -1,
                             0};

/* the two climb helpers and TestChainUpDown */
/* clang-format off */
static inline void SetChainClimbNodePoint(char *obj, ChainClimbWork *rec) /* derived name */
{
    int n = GetSkeltonFocusNode(obj, 0x23);
    rec->node[0] = *(float *)(n * 64 + ((ChainExtPtr *)(((ChainExtPtr *)(obj + 0x15C))->p + 0xC))->i + 0x30); rec->node[1] = *(float *)(n * 64 + ((ChainExtPtr *)(((ChainExtPtr *)(obj + 0x15C))->p + 0xC))->i + 0x34); rec->node[2] = *(float *)(n * 64 + ((ChainExtPtr *)(((ChainExtPtr *)(obj + 0x15C))->p + 0xC))->i + 0x38);
}

static inline float *PushChainClimbRoot(char *obj, float *pos, float *out, float *ofs, float fwd, float side) /* derived name */
{
    /* pushes the root out from the chain point (fwd along the orientation, side
     * across it) and returns the pushed point, which no caller reads.  Both
     * work vectors are the caller's.
     *
     *
     */
    sceVu0ScaleVector(out, test_CURRENTORIENT(obj), fwd);
    sceVu0AddVector(out, pos, out);



    sceVu0ScaleVector(ofs, test_CURRENTORIENT(obj), side);
    _ApplyRyGV(ofs, 1.5707964f);
    sceVu0AddVector(out, out, ofs);








    debug_NMarker(out, 0, 0, 255, 100.0f);

    SetDirectRootPositionNoFittingWithNodePoint(obj, 0x23, out, 1.0f);
    return out;
}

/* Climbing the chain: moves the boy's root between the chain's node points.
 * The climb-mode selector is a nested function at its head: it reads the
 * action record's 0x34 state through the captured boy, and its parameter is
 * the motion id.  The node-point and push helpers precede the function at
 * file scope.  This region keeps its line layout and is fenced from
 * clang-format.
 *
 *
 *
 *
 *
 */
void TestChainUpDown(char *gobj, char *boy)
{
    inline int GetChainClimbMode(int motion) /* derived name */
    {
        int mode = -1;
        switch (motion) {
        case 119:
            mode = 4; if (GOBJ_ACT(boy)->actMode != 0x3F) {
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
    ChainRecord *cw = GOBJ_SUB(gobj)->work;
    /* Act's 0x190 holds the chain object the boy hangs on, an int in typedef.h's Act */
    Act *sub = GOBJ_ACT(boy);

    /* Each arm has its own pointer to the climb work, set on the arm's first
     * test, and every read of an extension's 0x15C slot goes through the
     * ChainExtPtr union as in the node-point helper.
     *
     *
     *
     */







    int mode = GetChainClimbMode(GOBJ_SUB(boy)->motion);

    switch (mode) {
    case 4: {
        ChainClimbWork *rec;


        org[0] = test_CURRENTROOT(boyGObj)[0]; org[1] = test_CURRENTROOT(boyGObj)[1]; org[2] = test_CURRENTROOT(boyGObj)[2];

        rec = (ChainClimbWork *)chainClimb; if (rec->prev != mode) {
            rec->phase = 0.0f;
            rec->frames = (int)(float)*motionTable[((ChainExtPtr *)(boy + 0x15C))->sub->motion];
            SetChainClimbNodePoint(boy, rec);
            rec->target[0] = rec->node[0]; rec->target[2] = rec->node[2];
            rec->target[1] = rec->node[1] - 100.0f;
        }
        _InterGV(v, rec->node, rec->target, rec->phase, (float)rec->frames - rec->phase);



        v[1] = v[1] < cw->rootPos[1] ? cw->rootPos[1] : (cw->endPos[1] < v[1] ? cw->endPos[1] : v[1]);

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
            rec->frames = (int)(float)*motionTable[((ChainExtPtr *)(boy + 0x15C))->sub->motion];
            SetChainClimbNodePoint(boy, rec);
            rec->target[0] = rec->node[0]; rec->target[2] = rec->node[2];
            rec->target[1] = rec->node[1] - 100.0f;
        }
        _InterGV(v, rec->node, rec->target, rec->phase, (float)rec->frames - rec->phase);

        GetPositionOnTheChain(v, gobj, v);

        v[1] = v[1] < cw->node2Pos[1] ? cw->node2Pos[1] : (cw->endPos[1] < v[1] ? cw->endPos[1] : v[1]);

        PushChainClimbRoot(boy, v, w, d, mode == 0 ? -15.0f : -10.0f, mode == 0 ? -3.0f : -10.0f);

        ((ChainClimbWork *)chainClimb)->phase = ((ChainClimbWork *)chainClimb)->phase + 30.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);




        w[0] = test_CURRENTROOT(boyGObj)[0]; w[1] = test_CURRENTROOT(boyGObj)[1]; w[2] = test_CURRENTROOT(boyGObj)[2];
        w[1] = org[1] + *(float *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->i + 0x144);
        w[1] = w[1] < cw->rootPos[1] + 150.0f ? cw->rootPos[1] + 150.0f : (cw->endPos[1] < w[1] ? cw->endPos[1] : w[1]);
        SetDirectRootPosition(boyGObj, w);



        PlumbPointUpdateChain(gobj, v);

    } break;
    case 2: case 3: {
        ChainClimbWork *rec;
        rec = (ChainClimbWork *)chainClimb; if (rec->prev != mode) {
            rec->phase = 0.0f;
            rec->frames = (int)(float)*motionTable[((ChainExtPtr *)(boy + 0x15C))->sub->motion];
            SetChainClimbNodePoint(boy, rec);
            rec->target[0] = rec->node[0]; rec->target[2] = rec->node[2];
            rec->target[1] = rec->node[1] + 200.0f;
        }


        _InterGV(v, rec->node, rec->target, rec->phase, (float)rec->frames - rec->phase);

        GetPositionOnTheChain(v, gobj, v);

        v[1] = v[1] < cw->node2Pos[1] ? cw->node2Pos[1] : (cw->endPos[1] < v[1] ? cw->endPos[1] : v[1]);

        PushChainClimbRoot(boy, v, hw, hd, -20.0f, -5.0f);
        ((ChainClimbWork *)chainClimb)->phase = ((ChainClimbWork *)chainClimb)->phase + 1.0f;
        PlumbPointUpdateChain(gobj, v);
    } break;
    default: { ChainClimbWork *rec;
        rec = (ChainClimbWork *)chainClimb; if ((unsigned int)rec->prev < 2) {

            int n = GetSkeltonFocusNode(boyGObj, 0x16);
            v[0] = *(float *)(n * 64 + ((ChainExtPtr *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->p + 0xC))->i + 0x30); v[1] = *(float *)(n * 64 + ((ChainExtPtr *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->p + 0xC))->i + 0x34); v[2] = *(float *)(n * 64 + ((ChainExtPtr *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->p + 0xC))->i + 0x38);
            PlumbPointUpdateChain((char *)sub->chain, v);
        }
        if ((unsigned int)(rec->prev - 2) < 2) {

            int n = GetSkeltonFocusNode(boyGObj, 0x16);
            v[0] = *(float *)(n * 64 + ((ChainExtPtr *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->p + 0xC))->i + 0x30); v[1] = *(float *)(n * 64 + ((ChainExtPtr *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->p + 0xC))->i + 0x34); v[2] = *(float *)(n * 64 + ((ChainExtPtr *)(((ChainExtPtr *)((char *)boyGObj + 0x15C))->p + 0xC))->i + 0x38);
            PlumbPointUpdateChain((char *)sub->chain, v);
        }

        if (sub->actMode != 59) {

            _GetCorrectOrientOfChain((float *)cw->pdl.orient, gobj, (float *)test_CURRENTORIENT(boy));
        }
    } break;
    }

    ((ChainClimbWork *)chainClimb)->prev = mode;
}

/* clang-format on */

void SetChainRootUpdateMode(char *gobj, int mode, float *pos)
{
    GOBJ_SUB(gobj)->ropeState = mode;
    ((ChainVal *)((int)GOBJ_SUB(gobj) + 0x410))->f = pos[0];
    ((ChainVal *)((int)GOBJ_SUB(gobj) + 0x414))->f = pos[1];
    ((ChainVal *)((int)GOBJ_SUB(gobj) + 0x418))->f = pos[2];
    if (mode == 3) {
        SetDirectRootPositionNoFittingWithNodePoint(gobj, 0x16, pos, 1.0f);
    }
}

void HoldChain(char *a0)
{
    ChainRecord *p = GOBJ_SUB(a0)->work;
    StartPendulum(a0);
    p->hold = 1;
}

void ReleaseChain(char *a0)
{
    ChainRecord *cw = GOBJ_SUB(a0)->work;

    cw->hold = 0;
}

void GetChainPendulum(char *a0, float *a, float *b, float *c)
{
    ChainRecord *p = GOBJ_SUB(a0)->work;
    *a = p->pdl.angle;
    *b = p->pdl.amp;
    if (p->pdl.period < p->pdl.amp) {
        *b = p->pdl.period;
    }
    *c = p->pdl.cycle;
}

void IncreasePdlChain(char *a0)
{
    ChainRecord *cw = GOBJ_SUB(a0)->work;

    cw->pdl.ampSpeed = 0.1f;
}

void DecreasePdlChain(char *a0)
{
    ChainRecord *cw = GOBJ_SUB(a0)->work;

    cw->pdl.ampSpeed = (float)debug_chain_slow_speed * 0.5f * -0.1f;
}

void PlumbOrientUpdateChain(char *a0, float *src)
{
    ChainRecord *p = GOBJ_SUB(a0)->work;
    p->pdl.orient[0] = src[0];
    p->pdl.orient[1] = src[1];
    p->pdl.orient[2] = src[2];
}

int isBottomOfChain(char *a0)
{
    ChainRecord *p = GOBJ_SUB(a0)->work;
    return p->holdNode == p->nodes - 1;
}

int isStopChain(char *a0)
{
    ChainRecord *cw = GOBJ_SUB(a0)->work;

    return cw->stopped;
}

void GetChainClimbOrient(float *dst, char *a0)
{
    ChainRecord *p = GOBJ_SUB(a0)->work;
    dst[0] = p->wallOrient[0];
    dst[1] = p->wallOrient[1];
    dst[2] = p->wallOrient[2];
}

int CheckChainClimbablePos(char *a0)
{
    ChainRecord *p = GOBJ_SUB(a0)->work;

    if (p->wallHit != 0 && p->holdNode < 3)
        return 1;
    return 0;
}

typedef struct ClimbCol { /* field names derived */
    int hitPos[2];        /* the wall hit point */
    int wall;             /* the wall hit */
} ClimbCol;

void GetChainClimbCollision(ClimbCol *dst, char *a0)
{
    *dst = *(ClimbCol *)((ChainRecord *)GOBJ_SUB(a0)->work)->wallPos;
}

void SetChainParentGObj(char *a0, void *a1)
{
    *(void **)((char *)GOBJ_SUB(a0)->work) = a1;
}

/* the chain's direction correction in degrees, and whether it has one;
 * getChainDirCorrectVal below is the same body, for _GetCorrectOrientOfChain */
int GetChainDirCorrectVal(char *a0, int *a1)
{
    ChainRecord *p = GOBJ_SUB(a0)->work;
    *a1 = (int)(p->dirCorrect * 180.0f / 3.1415927f);
    return p->hasDirCorrect;
}

static inline int getChainDirCorrectVal(char *a0, int *a1) /* derived name */
{
    ChainRecord *p = GOBJ_SUB(a0)->work;
    *a1 = (int)(p->dirCorrect * 180.0f / 3.1415927f);
    return p->hasDirCorrect;
}

void GetRootPositionHandExtra(void *a0, float *a1)
{
    a1[0] = test_CURRENTROOT(a0)[0];
    a1[1] = test_CURRENTROOT(a0)[1];
    a1[2] = test_CURRENTROOT(a0)[2];
    a1[1] -= 50.0f;
}

void InitPendulum(char *a0)
{
    ChainRecord *cw = GOBJ_SUB(a0)->work;
    float a = (float)debug_chain_cycle_speed * -0.2f + 2.0f;
    float y;

    a = a < 0.1f ? 0.1f : (a > 2.0f ? 2.0f : a);

    y = (float)(int)(a * 6.0f * FSqrt(cw->pdl.length / 2.5f) * 8.0f / 10.0f);

    cw->pdl.cycle = y;
    cw->pdl.cycle = cw->pdl.cycle < 1.0f ? 1.0f : (cw->pdl.cycle > 255.0f ? 255.0f : cw->pdl.cycle);

    cw->pdl.phase = cw->pdl.cycle * 0.5f;
    cw->pdl.period = 360.0f;
    cw->pdl.swing = 1;
}

void LockChainGeo(char *a0)
{
    ChainRecord *cw = GOBJ_SUB(a0)->work;

    cw->locked = 1;
}

void UnLockChainGeo(char *a0)
{
    ChainRecord *cw = GOBJ_SUB(a0)->work;

    cw->locked = 0;
}

float GetChainHangRange(char *a0)
{
    ChainRecord *cw = GOBJ_SUB(a0)->work;

    return cw->angle;
}

float GetChainLength(char *a0)
{
    ChainRecord *cw = GOBJ_SUB(a0)->work;

    return (float)(cw->nodes - 1) * 50.0f;
}

void EnableChainHang(char *a0)
{
    ChainRecord *cw = GOBJ_SUB(a0)->work;

    cw->hangable = 1;
}

void UnableChainHang(char *a0)
{
    ChainRecord *cw = GOBJ_SUB(a0)->work;

    cw->hangable = 0;
}

int IsAbleChainHang(char *a0)
{
    ChainRecord *cw = GOBJ_SUB(a0)->work;

    return cw->hangable;
}

void ChainPositionReset(char *a0)
{
    float pos[4];
    ChainRecord *cw = GOBJ_SUB(a0)->work;

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
    ChainRecord *cw = GOBJ_SUB(gobj)->work;

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
