#include "common.h"
#include "debug.h"
#include "DisplayP2O.h"
#include "matrixDrive.h"
#include "quaternion.h"
#include "tableSin.h"
#include <libvu0.h>
#include <string.h>
#include <math.h>
#include "geometryManager.h"

/* kept local: this TU's uses of _DistSqGV do not fit the prototype in gv.h */
extern float _DistSqGV(void *a, void *b);

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

int UpdateRootPosition(char *gobj)
{
    float pos[4];
    char *cw = (char *)GOBJ_SUB(gobj)->f_830;
    ChainNode *nd;
    int moved = 0;

    if (*(int *)cw != 0) {
        SetDirectRootPosition(gobj, *(char **)(*(int *)(*(int *)cw + 0x15C) + 0xC) +
                                        (*(int *)(cw + 0x4) << 6) + 0x30);
    }
    GetRootPosition(pos, gobj);
    if (_DistSqGV(pos, cw + 0x10) < 1.0f) {
    } else {
        moved = 1;
    }
    *(float *)(cw + 0x10) = pos[0];
    *(float *)(cw + 0x14) = pos[1];
    *(float *)(cw + 0x18) = pos[2];
    nd = *(ChainNode **)(cw + 0xD0);
    nd[0].x = *(float *)(cw + 0x10);
    nd[0].y = *(float *)(cw + 0x14);
    nd[0].z = *(float *)(cw + 0x18);
    *(float *)(cw + 0x80) = nd[2].x;
    *(float *)(cw + 0x84) = nd[2].y;
    *(float *)(cw + 0x88) = nd[2].z;
    *(float *)(cw + 0x90) = nd[*(int *)(cw + 0x74) - 1].x;
    *(float *)(cw + 0x94) = nd[*(int *)(cw + 0x74) - 1].y;
    *(float *)(cw + 0x98) = nd[*(int *)(cw + 0x74) - 1].z;
    return moved;
}

/* kept local: this TU's uses of test_CURRENTORIENT do not fit the prototype in commonact.h */
extern void *test_CURRENTORIENT(void *a0);
extern char D_005551C0[];
extern char D_005551D0[];
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
void _GetCorrectOrientOfChain(float *out, char *gobj, float *dir);
extern int D_0063B214;
extern float D_0063ABC0[];

/* INTERIM (same shape as GetChainDirCorrectVal below): the listing inlines
 * InitPendulum's lines 517-538 into StartPendulum, so InitPendulum is a public
 * `inline` whose out-of-line copy sits at its own ROM position further down;
 * until then the caller inlines this static stand-in, which collapses at
 * layout. */
static inline void initPendulum(char *gobj)
{
    char *cw = (char *)GOBJ_SUB(gobj)->f_830;
    float a = (float)D_0063B214 * -0.2f + 2.0f;
    float y;

    a = a < 0.1f ? 0.1f : (a > 2.0f ? 2.0f : a);

    y = (float)(int)(a * 6.0f * FSqrt(*(float *)(cw + 0x3C) / 2.5f) * 8.0f / 10.0f);

    *(float *)(cw + 0x40) = y;
    *(float *)(cw + 0x40) = *(float *)(cw + 0x40) < 1.0f
                                ? 1.0f
                                : (*(float *)(cw + 0x40) > 255.0f ? 255.0f : *(float *)(cw + 0x40));

    *(float *)(cw + 0x38) = *(float *)(cw + 0x40) * 0.5f;
    *(float *)(cw + 0x48) = 360.0f;
    *(char *)(cw + 0x50) = 1;
}

/* K&R definition: HoldChain calls StartPendulum with the gobj alone. */
void StartPendulum(gobj, owner, pos) char *gobj;

char *owner;

float *pos;

{
    float d[4];
    char *cw = (char *)GOBJ_SUB(gobj)->f_830;
    int best = -1;
    float min = D_0063ABC0[0];
    int i;

    sceVu0SubVector(d, pos, *(void **)(cw + 0xD0));
    *(char **)(cw + 0x64) = owner;

    for (i = 0; i < *(int *)(cw + 0x74); i++) {
        int n = (int)(pos[1] - (*(ChainNode **)(cw + 0xD0))[i].y);
        float t = (float)(n < 0 ? -n : n);

        if (t < min) {
            min = t;
            best = i;
        }
    }
    if (best == -1) {
        debug_assert(D_005551C0, 563);
        __assert(D_005551C0, 563, D_005551D0);
    }
    *(int *)(cw + 0x68) = best;
    *(int *)(cw + 0x68) = *(int *)(cw + 0x68) < 2 ? 2
                                                  : (*(int *)(cw + 0x74) - 1 < *(int *)(cw + 0x68)
                                                         ? *(int *)(cw + 0x74) - 1
                                                         : *(int *)(cw + 0x68));

    _GetCorrectOrientOfChain((float *)(cw + 0x20), gobj, (float *)test_CURRENTORIENT(owner));

    ((ChainVal *)(cw + 0x3C))->f = (float)*(int *)(cw + 0x68) * 50.0f;

    initPendulum(gobj);
}

extern int D_0063B13C;
extern int D_0063C2C0;
/* kept local: this TU's uses of debug_Arrow do not fit the prototype in camera-editor.h */
extern void debug_Arrow(float len, void *from, void *to, int r, int g, int b);
/* kept local: the declaration in fieldCollision.h changes this TU codegen */
extern void ClipWall(void *w);
extern char D_005551E0[];

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
    char *cw = (char *)GOBJ_SUB(gobj)->f_830;

    if (*(unsigned char *)(cw + 0x50)) {
        v[0] = *(float *)(cw + 0x20);
        v[1] = *(float *)(cw + 0x24);
        v[2] = *(float *)(cw + 0x28);
    } else {
        sceVu0ScaleVector(v, cw + 0x20, -1.0f);
    }
    v[1] = 0.0f;
    sceVu0Normalize(v, v);
    debug_Arrow(200.0f, *(char **)(cw + 0xD0) + (*(int *)(cw + 0x68) << 5), v, 0xFF, 0, 0xFF);
    sceVu0ScaleVector(v, v, 140.0f);
    w.from[0] = ((float *)((*(int *)(cw + 0x68) << 5) + *(int *)(cw + 0xD0)))[0];
    w.from[1] = ((float *)((*(int *)(cw + 0x68) << 5) + *(int *)(cw + 0xD0)))[1];
    w.from[2] = ((float *)((*(int *)(cw + 0x68) << 5) + *(int *)(cw + 0xD0)))[2];
    sceVu0AddVector(w.to, w.from, v);
    w.radius = 10.0f;
    ClipWall(&w);
    if (w.hit) {
        if (D_0063B13C & 1) {
            D_0063C2C0 = D_0063C2C0 + 10;
            debug_Printf(10, D_0063C2C0, 0x0FFFFFFF, D_005551E0);
        }
        return 1;
    }
    return 0;
}

/* kept local: this TU's uses of _GetDirection do not fit the prototype in gv.h */
extern float _GetDirection(float *a0);
/* kept local: this TU's uses of collisionCheck do not fit the prototype in chain.h */
extern int collisionCheck(char *gobj);
/* kept local: this TU's uses of pendulum_Process do not fit the prototype in chain.h */
extern void pendulum_Process(void *a0, int a1);
/* kept local: this TU's uses of chain_sub_pendulum do not fit the prototype in chain.h */
extern void chain_sub_pendulum(char *base, int n, void *a2);
/* The sixth integer parameter is passed by both ROM call sites (always 0) and
 * never read by the body; it keeps $9 in the argument sequence. */
extern void chain_sub_simulate(int a0, ChainNode *nd, int from, int to, unsigned char flag,
                               int flag2, float grav, float len, float damp);

static inline void ChainPendulumSwing(float *dst, char *cw, float *orient)
{
    float ang = *(float *)(cw + 0x30);
    float len = *(float *)(cw + 0x3C);
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
    char *cw = (char *)GOBJ_SUB(a0)->f_830;

    pendulum_Process(cw + 0x20, collisionCheck((char *)a0));
    ChainPendulumSwing(pos, cw, (float *)(cw + 0x20));
    sceVu0AddVector(pos, *(void **)(cw + 0xD0), pos);
    chain_sub_pendulum(*(char **)(cw + 0xD0), *(int *)(cw + 0x68), pos);
    chain_sub_simulate(a0, *(ChainNode **)(cw + 0xD0), *(int *)(cw + 0x68), *(int *)(cw + 0x74), 1,
                       0, 20.0f, 50.0f, 0.6f);
}

extern char D_005551F0[];
/* kept local: this TU's uses of chain_simulate_term_simple do not fit the prototype in chain.h */
extern void chain_simulate_term_simple(int a0);

void chain_simulate_term_ropeturn(int a0)
{
    char *cw = (char *)GOBJ_SUB(a0)->f_830;

    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 10;
        debug_Printf(10, D_0063C2C0, 0x0FFFFFFF, D_005551F0);
    }
    *(float *)(cw + 0x44) = -0.4f;
    chain_simulate_term_simple(a0);
}

extern char D_00555210[];

void chain_simulate_term_loop(int a0)
{
    char *cw = (char *)GOBJ_SUB(a0)->f_830;

    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 10;
        debug_Printf(10, D_0063C2C0, 0x0FFFFFFF, D_00555210);
    }
    if (*(float *)(cw + 0x34) < 0.5) {
        *(float *)(cw + 0x44) = -0.01f;
    } else if (*(float *)(cw + 0x34) < 1.0) {
        *(float *)(cw + 0x44) = -0.05f;
    } else {
        *(float *)(cw + 0x44) = -0.15f;
    }
    chain_simulate_term_simple(a0);
}

extern int D_0028F4C0[];
extern char D_00555230[];

void chain_simulate_term_swingready(int a0)
{
    char *cw = (char *)GOBJ_SUB(a0)->f_830;

    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 10;
        debug_Printf(10, D_0063C2C0, 0x0FFFFFFF, D_00555230);
    }
    if (*(float *)(cw + 0x34) < 0.5) {
        *(float *)(cw + 0x44) = -0.29999998f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    } else if (*(float *)(cw + 0x34) < 1.0) {
        *(float *)(cw + 0x44) = -1.5f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    } else {
        *(float *)(cw + 0x44) = -4.5f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    }
    chain_simulate_term_simple(a0);
}

extern void *D_00639EA4;
extern char D_00555250[];

void chain_simulate_term_swingstart(int a0)
{
    char *cw = (char *)GOBJ_SUB(a0)->f_830;
    float h;

    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 10;
        debug_Printf(10, D_0063C2C0, 0x0FFFFFFF, D_00555250);
    }

    h = GOBJ_SUB(D_00639EA4)->f_4AC;

    if (h < 20.0f) {
        if (*(float *)(cw + 0x34) < 0.3) {
            *(float *)(cw + 0x44) =
                -0.29999998f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
        } else if (*(float *)(cw + 0x34) < 1.0) {
            *(float *)(cw + 0x44) = -6.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
        } else {
            *(float *)(cw + 0x44) = -9.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
        }
    } else {
        if (h >= 20.0 && h < 21.5) {
            *(float *)(cw + 0x38) = 0.0f;
            *(float *)(cw + 0x48) = 360.0f;
        }
        *(float *)(cw + 0x44) = 0.0f;
        *(float *)(cw + 0x34) = 3.0f;

        *(float *)(cw + 0x38) = *(float *)(cw + 0x38) - 1.0f +
                                *(float *)(cw + 0x40) * 0.5f / 41.0f * 30.0f /
                                    (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    }
    chain_simulate_term_simple(a0);
}

/* kept local: this TU's uses of _ApplyRyGV do not fit the prototype in gv.h */
extern void _ApplyRyGV(void *a0, float a1);

void chain_simulate_term_moveup(int a0)
{
    float w[4];
    float v[4];
    char *cw = (char *)GOBJ_SUB(a0)->f_830;
    float h;

    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 10;
        debug_Printf(10, D_0063C2C0, 0x0FFFFFFF, "chain_simulate_term_moveup\n");
    }
    if (*(float *)(cw + 0x34) < 1.0f) {
        *(float *)(cw + 0x34) = 1.0f;
        *(float *)(cw + 0x44) = 0.0f;
    } else if (*(float *)(cw + 0x34) < 2.0) {
        *(float *)(cw + 0x44) = -0.05f;
    } else {
        *(float *)(cw + 0x44) = -0.15f;
    }
    chain_simulate_term_simple(a0);
    h = GOBJ_SUB(D_00639EA4)->f_4AC;
    v[0] = *(float *)(cw + 0x20);
    v[1] = *(float *)(cw + 0x24);
    v[2] = *(float *)(cw + 0x28);
    _ApplyRyGV(v, -1.5707964f);
    sceVu0ScaleVector(v, v,
                      GetTableSin(h * 6.283185307179586 / 40.0 * 32768.0 / 3.1415927f) * 5.0f);
    sceVu0AddVector(w, *(char **)(cw + 0xD0) + (*(int *)(cw + 0x68) << 5), v);
    chain_sub_pendulum(*(char **)(cw + 0xD0), *(int *)(cw + 0x68), w);
}

void chain_simulate_term_free(int a0)
{
    char *cw = (char *)GOBJ_SUB(a0)->f_830;

    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 10;
        debug_Printf(10, D_0063C2C0, 0x0FFFFFFF, "chain_simulate_term_free\n");
    }
    if (*(float *)(cw + 0x34) < 0.5) {
        *(float *)(cw + 0x44) = -0.01f;
    } else if (*(float *)(cw + 0x34) < 2.0) {
        *(float *)(cw + 0x44) = -0.05f;
    } else {
        *(float *)(cw + 0x44) = -0.15f;
    }
    chain_simulate_term_simple(a0);
}

void chain_simulate_term_down(int a0)
{
    float w[4];
    float v[4];
    char *cw = (char *)GOBJ_SUB(a0)->f_830;
    ChainNode *nd;
    ChainNode *next;
    float h;

    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 10;
        /* a 2001 copy and paste: this arm prints the sibling term's name */
        debug_Printf(10, D_0063C2C0, 0x0FFFFFFF, "chain_simulate_term_free\n");
    }
    if (*(float *)(cw + 0x34) < 0.5) {
        *(float *)(cw + 0x44) = -0.01f;
    } else if (*(float *)(cw + 0x34) < 2.0) {
        *(float *)(cw + 0x44) = -0.05f;
    } else {
        *(float *)(cw + 0x44) = -0.15f;
    }
    chain_simulate_term_simple(a0);
    h = GOBJ_SUB(D_00639EA4)->f_4AC;
    v[0] = *(float *)(cw + 0x20);
    v[1] = *(float *)(cw + 0x24);
    v[2] = *(float *)(cw + 0x28);
    _ApplyRyGV(v, -1.5707964f);
    sceVu0ScaleVector(v, v,
                      GetTableSin(h * 6.283185307179586 / 23.0 * 32768.0 / 3.1415927f) * 2.0f);
    sceVu0AddVector(w, *(char **)(cw + 0xD0) + (*(int *)(cw + 0x68) << 5), v);
    chain_sub_pendulum(*(char **)(cw + 0xD0), *(int *)(cw + 0x68), w);
    if (*(int *)(cw + 0x68) + 1 <= *(int *)(cw + 0x74) - 1) {
        nd = (ChainNode *)((*(int *)(cw + 0x68) << 5) + *(int *)(cw + 0xD0));
        next = nd + 1;
        next->x = nd->x;
        next->y = nd->y + 50.0f;
        next->z = nd->z;
    }
}

extern char D_005552E0[];

void chain_simulate_hangstart(int a0)
{
    char *cw = (char *)GOBJ_SUB(a0)->f_830;

    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 10;
        debug_Printf(10, D_0063C2C0, 0x0FFFFFFF, D_005552E0);
    }
    *(float *)(cw + 0x44) = -1.5f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    chain_simulate_term_simple(a0);
}

extern char D_00555300[];

void chain_simulate_term(int a0)
{
    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 10;
        debug_Printf(10, D_0063C2C0, 0x0FFFFFFF, D_00555300);
    }
    chain_simulate_term_simple(a0);
}

static inline void ResetChainNodes(char *cw, float *pos)
{
    int i;

    for (i = 0; i < *(int *)(cw + 0x74); i++) {
        ChainNode *e = *(ChainNode **)(cw + 0xD0) + i;
        e->x = pos[0];
        e->y = pos[1];
        e->z = pos[2];
        e->y += (float)i * 50.0f;
        e->vx = 0.0f;
        e->vy = 0.0f;
        e->vz = 0.0f;
    }
}

extern char D_00555318[];

void chain_simulate_stop(int a0)
{
    char *cw = (char *)GOBJ_SUB(a0)->f_830;

    ResetChainNodes(cw, (float *)(cw + 0x10));
    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 10;
        debug_Printf(10, D_0063C2C0, 0x0FFFFFFF, D_00555318);
    }
}

extern char D_00555330[];

void chain_simulate_free(int a0)
{
    char *cw = (char *)GOBJ_SUB(a0)->f_830;
    int i;

    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 10;
        debug_Printf(10, D_0063C2C0, 0x0FFFFFFF, D_00555330);
    }
    chain_sub_simulate(a0, *(ChainNode **)(cw + 0xD0), 0, *(int *)(cw + 0x74), 1, 0, 10.0f, 50.0f,
                       0.675f);
    *(float *)(cw + 0x34) = 0.0f;
    for (i = 1; i < *(int *)(cw + 0x74); i++) {
        ChainNode *nd = *(ChainNode **)(cw + 0xD0);
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

extern char D_00555348[];
extern char D_00555358[];
extern char D_00555368[];
extern char D_00555378[];
extern char D_00555388[];
extern char D_00555398[];
extern char D_005553A8[];

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

    if (D_0063B13C & 1) {
        debug_Printf(10, D_0063C2C0 += 10, 0x0FFFFFFF, D_00555348, w->f18);
        if (D_0063B13C & 1) {
            debug_Printf(10, D_0063C2C0 += 10, 0x0FFFFFFF, D_00555358, w->f10);
            if (D_0063B13C & 1) {
                debug_Printf(10, D_0063C2C0 += 10, 0x0FFFFFFF, D_00555368, w->f14);
                if (D_0063B13C & 1) {
                    debug_Printf(10, D_0063C2C0 += 10, 0x0FFFFFFF, D_00555378, w->f28);
                    if (D_0063B13C & 1) {
                        debug_Printf(10, D_0063C2C0 += 10, 0x0FFFFFFF, D_00555388, w->f20);
                        if (D_0063B13C & 1) {
                            debug_Printf(10, D_0063C2C0 += 10, 0x0FFFFFFF, D_00555398, w->f1C);
                            if (D_0063B13C & 1) {
                                debug_Printf(10, D_0063C2C0 += 10, 0x0FFFFFFF, D_005553A8, up);
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
extern void GetOrientOfWall(void *out, int wall, float *pos);
/* kept local: this TU does not include memory.h, whose first parameter type is
 * not the plain partition word the chain code hands over */
extern void *iosMallocDebug(void *part, int size, char *file, int line);
extern void *iosFree(void *p);
/* the two carved chain records the new geometry starts from: 224 bytes over the
 * head of the record and 64 bytes over the pendulum block at 0x20 */
extern char D_002A5ED0[];
extern char D_002A5F10[];
extern char D_005553B8[];
extern char D_00555410[];
extern char D_0063ABC8[];
extern void *D_0063A438;
extern void *D_0063A44C;

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

/* the copy shapes the record templates and the probe endpoints are moved
 * through: doubleword-aligned so the copies come out as ld/sd runs */
typedef struct {
    long long w[28];
} ChainRecTemplate;

typedef struct {
    long long w[8];
} ChainPendTemplate;

typedef struct {
    long long w[2];
} ChainProbeVec;

/* The two wall-probe endpoints, (0, 0, -100, 1) and (0, 0, 25, 1): read-only
 * data, and const is also what gives ROM's load order in the second copy, since
 * an unchanging read carries no anti-dependence on the frame stores of the
 * first one. */
extern const ChainProbeVec D_005553F0;
extern const ChainProbeVec D_00555400;

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
    ChainProbeVec p0;
    ChainProbeVec p1;
    ChainClipWork w;
    char *cw;
    int n;
    int i;

    n = (int)(req->f24 / 50.0f + 0.5f);

    if (n < 2) {
        debug_StdPrintfDummy(D_005553B8);
        debug_assert(D_005551C0, 1178);
        __assert(D_005551C0, 1178, D_0063ABC8);
    }

    cw = (char *)iosMallocDebug((void *)D_0063A438, (n << 5) + 0xE0, D_005551C0, 1181);

    *(ChainRecTemplate *)cw = *(ChainRecTemplate *)D_002A5F10;

    *(int *)(cw + 0x74) = n;
    *(char **)(cw + 0xD0) = cw + 0xE0;
    *(int *)(cw + 0x68) = -1;
    if (req->f20 != -1.0f) {
        *(float *)(cw + 0xC8) = req->f20;
    }

    *(ChainPendTemplate *)(cw + 0x20) = *(ChainPendTemplate *)D_002A5ED0;

    *(float *)(cw + 0x4C) = req->f28;
    *(float *)(cw + 0x4C) = *(float *)(cw + 0x4C) < 5.0f
                                ? 5.0f
                                : (90.0f < *(float *)(cw + 0x4C) ? 90.0f : *(float *)(cw + 0x4C));

    ResetChainNodes(cw, (float *)req);

    if (req->f10 != 0.0f) {
        p0 = D_005553F0;
        p1 = D_00555400;

        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrix(req->pos[0], req->pos[1] + 10.0f, req->pos[2]);
        MatrixDrive_RotMatrixY((short)(req->f14 * 32768.0f / 3.1415927f));
        sceVu0ApplyMatrix(w.from, MatrixDrive_GetMatrix(), &p0);
        sceVu0ApplyMatrix(w.to, MatrixDrive_GetMatrix(), &p1);
        ClipWall(&w);
        if (w.hit == 0) {
            debug_StdPrintfDummy(D_00555410);
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
        (void *)D_0063A44C, (*(int *)(cw + 0x74) - 1) << 6, D_005551C0, 1245);
    *(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x10) = (char *)iosMallocDebug(
        (void *)D_0063A44C, (*(int *)(cw + 0x74) - 1) << 4, D_005551C0, 1245);
    *(int *)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x8) = *(int *)(cw + 0x74) - 1;
    if (*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x870) != 0) {
        iosFree((void *)((int)*(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x870) & 0x0FFFFFFF));
    }
    *(char **)(((ChainExtPtr *)(gobj + 0x15C))->p + 0x870) = (char *)iosMallocDebug(
        (void *)D_0063A44C, (*(int *)(cw + 0x74) - 1) * 80, D_005551C0, 1245);

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
    char *cw = (char *)GOBJ_SUB(gobj)->f_830;
    int deg;
    int idx;
    float c;
    float s;
    char *p;

    memset(v, 0, 16);

    deg = (int)(_GetDirection(test_CURRENTORIENT(D_00639EA4)) / 3.1415927f * 180.0f);
    idx = *(int *)(cw + 0x68) + 2;

    if (*(int *)(cw + 0x74) - 2 < idx) {
        return;
    }

    c = GetTableCos(*(int *)(cw + 0xC4) * 2000) * amp;
    s = GetTableSin(*(int *)(cw + 0xC4) * 1500) * amp;

    v[0] = c;
    v[1] = 0.0f;
    v[2] = s;
    _ApplyRyGV(v, (float)deg * 3.1415927f / 180.0f);

    p = (char *)((idx << 5) + *(int *)(cw + 0xD0));
    *(float *)p = *(float *)(p - 0x20) + v[0];

    *(float *)(p + 0x8) = *(float *)(p - 0x18) + v[2];

    *(int *)(cw + 0xC4) = *(int *)(cw + 0xC4) + 1;
}

INCLUDE_ASM("asm/nonmatchings/ico2/omori/src/chain", ChainGeo);

/* kept local: this TU's uses of _SubVector do not fit the prototype in Matrix.h */
extern void _SubVector(void *d, void *a, void *b);
/* kept local: this TU's uses of _NormalizeVector do not fit the prototype in Matrix.h */
extern void _NormalizeVector(void *d, void *s);

void ChainDL(char *gobj)
{
    char q[0x10];
    char up[0x10];
    char d[0x10];
    char n[0x10];
    char dq[0x10];
    char *ext = (char *)GOBJ_SUB(gobj);
    char *cw = *(char **)(ext + 0x830);
    int i;

    memset(q, 0, 16);
    ((ChainVal *)(q + 0xC))->f = 1.0f;
    memset(up, 0, 16);
    ((ChainVal *)(up + 0x4))->f = 1.0f;

    for (i = 0; i < *(int *)(cw + 0x74) - 1; i++) {
        ChainNode *p = &(*(ChainNode **)(cw + 0xD0))[i];
        ChainNode *np = &(*(ChainNode **)(cw + 0xD0))[i + 1];

        _SubVector(d, np, p);
        _NormalizeVector(n, d);
        GetDifferencialQuaternionWithNoRegularize(dq, n, up);
        MultiQuaternion(q, dq, q);
        CopyVector(up, n);
        GetMatrixFromQuaternionPos((char *)GOBJ_SUB(gobj)->f_C + (i << 6), q, p);
    }
    p2o_DispVU1DObjMulti(ext);
}

/* kept local: this TU's uses of _InterGV do not fit the prototype in gv.h */
extern void _InterGV(void *elem, void *base, void *v, float a, float b);

static inline void ChainNodeSpan(char *cw, float *pos, int *i0, int *i1)
{
    ChainNode *nd = *(ChainNode **)(cw + 0xD0);

    *i0 = (int)((pos[1] - nd[0].y) / 50.0f);
    *i1 = *i0 + 1;
    *i0 = *i0 < 2 ? 2 : (*(int *)(cw + 0x74) - 1 < *i0 ? *(int *)(cw + 0x74) - 1 : *i0);
    *i1 = *i1 < 2 ? 2 : (*(int *)(cw + 0x74) - 1 < *i1 ? *(int *)(cw + 0x74) - 1 : *i1);
}

void GetPositionOnTheChain(float *out, char *gobj, float *pos)
{
    float a[4];
    float b[4];
    int i0;
    int i1;
    char *cw = (char *)GOBJ_SUB(gobj)->f_830;
    ChainNode *nd;

    ChainNodeSpan(cw, pos, &i0, &i1);
    nd = *(ChainNode **)(cw + 0xD0);
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

extern float D_0063ABD4[];

void PlumbPointUpdateChain(char *gobj, float *pos)
{
    float d[4];
    char *cw = (char *)GOBJ_SUB(gobj)->f_830;
    char *owner;
    int best = -1;
    float min = D_0063ABD4[0];
    int i;

    owner = *(char **)(cw + 0x64);
    sceVu0SubVector(d, pos, *(void **)(cw + 0xD0));
    *(char **)(cw + 0x64) = owner;

    for (i = 0; i < *(int *)(cw + 0x74); i++) {
        int n = (int)(pos[1] - (*(ChainNode **)(cw + 0xD0))[i].y);
        float t = (float)(n < 0 ? -n : n);

        if (t < min) {
            min = t;
            best = i;
        }
    }
    if (best == -1) {
        debug_assert(D_005551C0, 1675);
        __assert(D_005551C0, 1675, D_005551D0);
    }
    *(int *)(cw + 0x68) = best;
    *(int *)(cw + 0x68) = *(int *)(cw + 0x68) < 2 ? 2
                                                  : (*(int *)(cw + 0x74) - 1 < *(int *)(cw + 0x68)
                                                         ? *(int *)(cw + 0x74) - 1
                                                         : *(int *)(cw + 0x68));

    _GetCorrectOrientOfChain((float *)(cw + 0x20), gobj, (float *)test_CURRENTORIENT(owner));

    ((ChainVal *)(cw + 0x3C))->f = (float)*(int *)(cw + 0x68) * 50.0f;
}

INCLUDE_ASM("asm/nonmatchings/ico2/omori/src/chain", TestChainUpDown);

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

extern int D_0063B218;

void DecreasePdlChain(char *a0)
{
    *(float *)((char *)GOBJ_SUB(a0)->f_830 + 0x44) = (float)D_0063B218 * 0.5f * -0.1f;
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

/* kept local: this TU's uses of test_CURRENTROOT do not fit the prototype in commonact.h */
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
    char *cw = (char *)GOBJ_SUB(a0)->f_830;
    float a = (float)D_0063B214 * -0.2f + 2.0f;
    float y;

    a = a < 0.1f ? 0.1f : (a > 2.0f ? 2.0f : a);

    y = (float)(int)(a * 6.0f * FSqrt(*(float *)(cw + 0x3C) / 2.5f) * 8.0f / 10.0f);

    *(float *)(cw + 0x40) = y;
    *(float *)(cw + 0x40) = *(float *)(cw + 0x40) < 1.0f
                                ? 1.0f
                                : (*(float *)(cw + 0x40) > 255.0f ? 255.0f : *(float *)(cw + 0x40));

    *(float *)(cw + 0x38) = *(float *)(cw + 0x40) * 0.5f;
    *(float *)(cw + 0x48) = 360.0f;
    *(char *)(cw + 0x50) = 1;
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
    char *cw = (char *)GOBJ_SUB(a0)->f_830;

    UpdateRootMatrix(a0);
    GetRootPosition(pos, a0);
    ResetChainNodes(cw, pos);
}

/* kept local: this TU's uses of RoundDegGV do not fit the prototype in gv.h */
extern int RoundDegGV(int a0);
/* kept local: this TU's uses of AlignDegGV do not fit the prototype in gv.h */
extern int AlignDegGV(int a0);

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

extern float D_0063ABD8[];

int GetChainNearestNodePosition(float *out, char *gobj, float *p)
{
    char *cw = (char *)GOBJ_SUB(gobj)->f_830;

    float best = D_0063ABD8[0];
    int ret = 0;
    int i;

    for (i = 2; i <= *(int *)(cw + 0x74) - 1; i++) {
        float d = _DistSqGV(p, *(char **)(cw + 0xD0) + i * 32);

        if (d < best) {
            float *e = (float *)(i * 32 + *(int *)(cw + 0xD0));
            out[0] = e[0];
            out[1] = e[1];
            out[2] = e[2];
            best = d;
            ret = 1;
        }
    }
    return ret;
}
