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
#include <assert.h>
#include "include_asm.h"

static void chain_sub_pendulum(struct ChainNode *base, int n, float *pos);

/* gobj and the sixth parameter (always 0) are passed by both callers and never read */
static void chain_sub_simulate(GObj *gobj, struct ChainNode *nd, int from, int to,
                               unsigned char flag, int flag2, float grav, float len, float damp);

static void pendulum_Process(struct ChainPendulum *pdl, int flag);

typedef struct ChainNode { /* field names derived */
    float x, y, z, w;
    float vx, vy, vz, vw;
} ChainNode; /* derived name */

/* One word of a chain record or of a chain vector: the chain code writes these
 * slots as float and reads them as int (and the other way round), so the word
 * itself is a union. */
typedef union ChainVal { /* field names derived */
    int i;
    float f;
} ChainVal; /* derived name */

/* The pendulum block at 0x20 of a chain record: the swing orientation, the
 * swing angle, its amplitude, the phase within one cycle and the cycle length
 * in frames, the rope length, the amplitude change per frame, the amplitude
 * ceiling at 0x48 (360 at every restart, lowered to the swing a wall hit
 * leaves), the swing limit at 0x4C and the swinging flag at 0x50.
 * pendulum_Process's trace prints them as time, rad, max, maxl, T and d. */
typedef struct ChainPendulum { /* field names derived */
    /* 0x20 */ sceVu0FVECTOR orient;
    /* 0x30 */ float angle;
    /* 0x34 */ float amp;
    /* 0x38 */ float phase;
    /* 0x3C */ float length;
    /* 0x40 */ float cycle;
    /* 0x44 */ float ampSpeed;
    /* 0x48 */ float ampLimit;
    /* 0x4C */ float limit;
    /* 0x50 */ unsigned char swing;
} ChainPendulum; /* derived name */

/* The head of a chain record, 0xE0 bytes, the node array following it. */
typedef struct {             /* field names derived */
    /* 0x00 */ GObj *root;   /* the object the chain hangs from, or 0 */
    /* 0x04 */ int rootNode; /* the node of that object it hangs from */

    /* 0x10 */ sceVu0FVECTOR rootPos;
    /* 0x20 */ ChainPendulum pdl;
    /* 0x60 */ unsigned char hold;
    /* 0x64 */ GObj *owner;
    /* 0x68 */ int holdNode;
    /* 0x6C */ unsigned char hasDirCorrect;
    /* 0x70 */ float dirCorrect;
    /* 0x74 */ int nodes;
    /* 0x78 */ int mode; /* the simulation mode the last ChainGeo ran */
    /* 0x80 */ sceVu0FVECTOR node2Pos;
    /* 0x90 */ sceVu0FVECTOR endPos;
    /* 0xA0 */ unsigned char wallHit;
    /* 0xA4 */ ClimbCol climb; /* the wall the chain hangs against */
    /* 0xB0 */ sceVu0FVECTOR wallOrient;
    /* 0xC0 */ unsigned char stopped;
    /* 0xC4 */ int count;
    /* 0xC8 */ float hangRange;
    /* 0xCC */ unsigned char locked;
    /* 0xCD */ unsigned char hangable;
    /* 0xD0 */ ChainNode *node;
} ChainRecord; /* derived name */

INCLUDE_ASM(UpdateRootPosition);

/* InitPendulum's body, for StartPendulum above its definition */
static inline void initPendulum(GObj *gobj) /* derived name */
{
    ChainRecord *cw = GOBJ_SUB(gobj)->work;
    float a = (float)debug_chain_cycle_speed * -0.2f + 2.0f;
    float y;

    a = a < 0.1f ? 0.1f : (a > 2.0f ? 2.0f : a);

    y = (float)(int)(a * 6.0f * FSqrt(cw->pdl.length / 2.5f) * 8.0f / 10.0f);

    cw->pdl.cycle = y;
    cw->pdl.cycle = cw->pdl.cycle < 1.0f ? 1.0f : (cw->pdl.cycle > 255.0f ? 255.0f : cw->pdl.cycle);

    cw->pdl.phase = cw->pdl.cycle * 0.5f;
    cw->pdl.ampLimit = 360.0f;
    cw->pdl.swing = 1;
}

/* the hold starts the swing: the holder and its hand position fix the hold
   node and the swing plane */
INCLUDE_ASM(StartPendulum);

/* the debug trace line: every chain trace steps it by 10 and ChainGeo resets
 * it */
static int chainDebugY; /* derived name */

INCLUDE_ASM(collisionCheck);

static inline void ChainPendulumSwing(float *dst, ChainRecord *cw, float *orient) /* derived name */
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

static void chain_simulate_term_simple(GObj *gobj);

INCLUDE_ASM(chain_simulate_term_simple);

static void chain_simulate_term_ropeturn(GObj *gobj);

INCLUDE_ASM(chain_simulate_term_loop);

INCLUDE_ASM(chain_simulate_term_swingready);

INCLUDE_ASM(chain_simulate_term_swingstart);

INCLUDE_ASM(chain_simulate_term_moveup);

INCLUDE_ASM(chain_simulate_term_free);

INCLUDE_ASM(chain_simulate_term_down);

INCLUDE_ASM(chain_simulate_hangstart);

static void chain_simulate_term(GObj *gobj)
{
    if (debug_font_flag & 1) {
        chainDebugY = chainDebugY + 10;
        debug_Printf(10, chainDebugY, 0x0FFFFFFF, "chain_simulate_term\n");
    }
    chain_simulate_term_simple(gobj);
}

static inline void ResetChainNodes(ChainRecord *cw, float *pos) /* derived name */
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

INCLUDE_ASM(chain_simulate_stop);

INCLUDE_ASM(chain_simulate_free);

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

/* K&R definition: the flag is an unsigned char promoted to int. */
static void pendulum_Process(w, flag) ChainPendulum *w;

unsigned char flag;

{
    int up;

    up = w->ampSpeed > 0.0f ? 1 : 0;

    if (debug_font_flag & 1) {
        debug_Printf(10, chainDebugY += 10, 0x0FFFFFFF, "time = %f\n", w->phase);
        if (debug_font_flag & 1) {
            debug_Printf(10, chainDebugY += 10, 0x0FFFFFFF, "rad  = %f\n", w->angle);
            if (debug_font_flag & 1) {
                debug_Printf(10, chainDebugY += 10, 0x0FFFFFFF, "max  = %f\n", w->amp);
                if (debug_font_flag & 1) {
                    debug_Printf(10, chainDebugY += 10, 0x0FFFFFFF, "maxl = %f\n", w->ampLimit);
                    if (debug_font_flag & 1) {
                        debug_Printf(10, chainDebugY += 10, 0x0FFFFFFF, "T    = %f\n", w->cycle);
                        if (debug_font_flag & 1) {
                            debug_Printf(10, chainDebugY += 10, 0x0FFFFFFF, "d    = %f\n",
                                         w->length);
                            if (debug_font_flag & 1) {
                                debug_Printf(10, chainDebugY += 10, 0x0FFFFFFF, "inc  = %d\n", up);
                            }
                        }
                    }
                }
            }
        }
    }

    if (w->length > 0.0f) {
        w->phase = w->phase + 1.0f;
        if (w->cycle <= w->phase) {
            w->phase = 0.0f;
        }

        w->amp = w->amp + w->ampSpeed;
        w->amp = w->amp < 0.0f ? 0.0f : (w->limit < w->amp ? w->limit : w->amp);
        w->ampSpeed = 0.0f;

        w->angle = -GetTableSin(((int)w->phase << 16) / (int)w->cycle) * w->amp;

        if (flag) {
            if ((w->angle < 0.0f ? -w->angle : w->angle) < w->ampLimit) {
                w->ampLimit = w->angle < 0.0f ? -w->angle : w->angle;
            }
        }

        if (w->ampLimit < w->amp) {
            w->amp = w->amp - 0.2f;
        }

        w->angle = w->angle < -w->ampLimit ? -w->ampLimit
                                           : (w->ampLimit < w->angle ? w->ampLimit : w->angle);

        if (w->cycle * 0.25 < w->phase && w->phase < w->cycle * 0.75) {
            w->swing = 1;
        } else {
            w->swing = 0;
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
    {{0, 0}, 0},
    {0.0f, 0.0f, 0.0f, 0.0f},
    1,
    0,
    70.0f,
    0,
    1,
    0};

/* The geometry request the caller fills in: the anchor position, whether to
 * look for the wall the chain hangs against and the direction to look in, the
 * direction correction (negative for none), the hand's reach for a hang
 * (-1 keeps the default), the chain length and the swing limit. */
typedef struct { /* field names derived */
    /* 0x00 */ float pos[4];
    /* 0x10 */ float wallCheck;
    /* 0x14 */ float wallDir;
    /* 0x18 */ float dirCorrect;
    /* 0x1C */ char pad1C[4];
    /* 0x20 */ float hangRange;
    /* 0x24 */ float length;
    /* 0x28 */ float limit;
} ChainGeoReq; /* derived name */

/* the record templates, copied whole as doubleword runs */
typedef struct { /* field names derived */
    long long words[28];
} ChainRecTemplate; /* derived name */

typedef struct { /* field names derived */
    long long words[8];
} ChainPendTemplate; /* derived name */

/* the gobj extension pointer */
typedef union { /* field names derived */
    Sub15C *sub;
} ChainExtPtr; /* derived name */

/* the DObj entry flag word, the same union DObj.c's allocObjectData uses */
typedef union { /* field names derived */
    long long ll;
    int i[2];
} ChainDObjFlags; /* derived name */

INCLUDE_ASM(InitChainGeo);

INCLUDE_ASM(chain_simulate_climb);

INCLUDE_ASM(chain_set_charachara);

/* The enemy parameter table, one 404-byte row per motion id; ChainGeo reads
 * only the flag word at 0x18C.  Same record enemy_act.c reads as EnemyParaRow. */
typedef struct { /* field names derived */
    char pad00[396];
    unsigned int flags; /* bit 11: a motion the hand hangs on the chain from */
    char pad190[4];
} ChainParaRow; /* derived name */

/* the data-only member motion-def.o, read through this file's view of its
   rows; no header declares it */
extern ChainParaRow motionKind[];
static void TestChainUpDown(GObj *gobj, GObj *boy);

/* the simulation mode the boy's motion selects, for ChainGeo */
static inline int GetChainSimulateMode(GObj *gobj) /* derived name */
{
    ChainRecord *cw = GOBJ_SUB(gobj)->work;
    int mode = 1;

    if (cw->hold != 0) {
        GObj *holder = cw->owner;
        int st = GOBJ_ACT(holder)->actMode;

        mode = 6;
        if (st != 58) {
            mode = st == 59 ? 9 : 3;
        }

        switch (GOBJ_SUB(holder)->ctrl.motion) {
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
static inline unsigned char isChainHitByHand(GObj *gobj, float *p, float *v, float *o,
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

INCLUDE_ASM(ChainGeo);

INCLUDE_ASM(ChainDL);

static inline void ChainNodeSpan(ChainRecord *cw, float *pos, int *i0, int *i1) /* derived name */
{
    ChainNode *nd = cw->node;

    *i0 = (int)((pos[1] - nd[0].y) / 50.0f);
    *i1 = *i0 + 1;
    *i0 = *i0 < 2 ? 2 : (cw->nodes - 1 < *i0 ? cw->nodes - 1 : *i0);
    *i1 = *i1 < 2 ? 2 : (cw->nodes - 1 < *i1 ? cw->nodes - 1 : *i1);
}

INCLUDE_ASM(GetPositionOnTheChain);

INCLUDE_ASM(PlumbPointUpdateChain);

/* the climb work the chain-climb modes share: the focus node point, the target
 * point the root is interpolated towards, the interpolation phase, the
 * motion's frame count and the mode the previous call left behind. */
typedef struct { /* field names derived */
    /* 0x00 */ sceVu0FVECTOR node;
    /* 0x10 */ sceVu0FVECTOR target;
    /* 0x20 */ float phase;
    /* 0x24 */ int frames;
    /* 0x28 */ int prev;
} ChainClimbWork; /* derived name */

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
static inline void SetChainClimbNodePoint(GObj *obj, ChainClimbWork *rec) /* derived name */
{
    int n = GetSkeltonFocusNode(obj, 35);
    rec->node[0] = *(float *)(n * 64 + ((ChainExtPtr *)&obj->dobj)->sub->nodeMtx + 48); rec->node[1] = *(float *)(n * 64 + ((ChainExtPtr *)&obj->dobj)->sub->nodeMtx + 52); rec->node[2] = *(float *)(n * 64 + ((ChainExtPtr *)&obj->dobj)->sub->nodeMtx + 56);
}

static inline float *PushChainClimbRoot(GObj *obj, float *pos, float *out, float *ofs, float fwd, float side) /* derived name */
{
    /* pushes the root out from the chain point (fwd along the orientation, side
     * across it) and returns the pushed point, which no caller reads.  Both
     * work vectors are the caller's.
     */
    sceVu0ScaleVector(out, test_CURRENTORIENT(obj), fwd);
    sceVu0AddVector(out, pos, out);

    sceVu0ScaleVector(ofs, test_CURRENTORIENT(obj), side);
    _ApplyRyGV(ofs, 1.5707964f);
    sceVu0AddVector(out, out, ofs);

    debug_NMarker(out, 0, 0, 255, 100.0f);

    SetDirectRootPositionNoFittingWithNodePoint(obj, 35, out, 1.0f);
    return out;
}

/* Climbing the chain: moves the boy's root between the chain's node points.
 * The climb-mode selector is a nested function at its head: it reads the
 * action record's 0x34 state through the captured boy, and its parameter is
 * the motion id.  The node-point and push helpers precede the function at
 * file scope.  This region keeps its line layout and is fenced from
 * clang-format.
 */
INCLUDE_ASM(TestChainUpDown);

/* clang-format on */

INCLUDE_ASM(HoldChain);

INCLUDE_ASM(ReleaseChain);

INCLUDE_ASM(GetChainPendulum);

INCLUDE_ASM(IncreasePdlChain);

INCLUDE_ASM(DecreasePdlChain);

INCLUDE_ASM(PlumbOrientUpdateChain);

INCLUDE_ASM(isBottomOfChain);

INCLUDE_ASM(isStopChain);

INCLUDE_ASM(GetChainClimbOrient);

INCLUDE_ASM(CheckChainClimbablePos);

INCLUDE_ASM(GetChainClimbCollision);

INCLUDE_ASM(SetChainParentGObj);

/* the chain's direction correction in degrees, and whether it has one;
 * getChainDirCorrectVal below is the same body, for _GetCorrectOrientOfChain */
INCLUDE_ASM(GetChainDirCorrectVal);

static inline int getChainDirCorrectVal(GObj *chain, int *deg) /* derived name */
{
    ChainRecord *p = GOBJ_SUB(chain)->work;
    *deg = (int)(p->dirCorrect * 180.0f / 3.1415927f);
    return p->hasDirCorrect;
}

void GetRootPositionHandExtra(void *gobj, float *out)
{
    out[0] = test_CURRENTROOT(gobj)[0];
    out[1] = test_CURRENTROOT(gobj)[1];
    out[2] = test_CURRENTROOT(gobj)[2];
    out[1] -= 50.0f;
}

INCLUDE_ASM(InitPendulum);

INCLUDE_ASM(LockChainGeo);

INCLUDE_ASM(UnLockChainGeo);

INCLUDE_ASM(GetChainHangRange);

INCLUDE_ASM(GetChainLength);

INCLUDE_ASM(EnableChainHang);

INCLUDE_ASM(UnableChainHang);

INCLUDE_ASM(IsAbleChainHang);

INCLUDE_ASM(_GetCorrectOrientOfChain);

static void chain_sub_simulate(GObj *gobj, ChainNode *nd, int from, int to, unsigned char flag,
                               int flag2, float grav, float len, float damp)
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

static void chain_sub_pendulum(ChainNode *base, int n, float *pos)
{
    ChainNode *p;
    int i = 0;
    if (n < 0) {
        return;
    }
    p = base;
    do {
        _InterGV(&p->x, &base->x, pos, (float)i, (float)(n - i));
        i++;
        p++;
    } while (i <= n);
}

INCLUDE_ASM(GetChainNearestNodePosition);
