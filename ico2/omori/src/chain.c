#include "common.h"

extern void SetDirectRootPosition(char *self, void *v);
extern void GetRootPosition(void *a0, void *a1);
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
    char *cw = *(char **)(*(int *)(gobj + 0x15C) + 0x830);
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

extern void sceVu0SubVector(void *a0, void *a1, void *a2);
extern void *test_CURRENTORIENT(void *a0);
extern char D_005551C0[];
extern char D_005551D0[];
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
void _GetCorrectOrientOfChain(float *out, char *gobj, float *dir);
extern int D_0063B214;
extern float D_0063ABC0[];
extern float FSqrt(float a0);

/* INTERIM (same shape as GetChainDirCorrectVal below): the listing inlines
 * InitPendulum's lines 517-538 into StartPendulum, so InitPendulum is a public
 * `inline` whose out-of-line copy sits at its own ROM position further down;
 * until then the caller inlines this static stand-in, which collapses at
 * layout. */
static inline void initPendulum(char *gobj)
{
    char *cw = *(char **)(*(char **)(gobj + 0x15C) + 0x830);
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
    char *cw = *(char **)(*(int *)(gobj + 0x15C) + 0x830);
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
extern void debug_Printf(int a, int b, int c, const char *d);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);
extern void sceVu0Normalize(void *a0, void *a1);
extern void sceVu0AddVector(void *a0, void *a1, void *a2);
extern void debug_Arrow(float len, void *from, void *to, int r, int g, int b);
extern void ClipWall(void *w);
extern char D_005551E0[];

/* The wall-clip request the chain hands to ClipWall: the segment endpoints, the
 * clip radius at 0x70 and the hit result at 0x88. */
typedef struct {
    /* 0x00 */ float from[4];
    /* 0x10 */ float to[4];
    /* 0x20 */ char _20[0x50];
    /* 0x70 */ float radius;
    /* 0x74 */ char _74[0x14];
    /* 0x88 */ int hit;
    /* 0x8C */ char _8c[0x34];
} ChainClipWork;

int collisionCheck(char *gobj)
{
    ChainClipWork w;
    float v[4];
    char *cw = *(char **)(*(int *)(gobj + 0x15C) + 0x830);

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
            D_0063C2C0 = D_0063C2C0 + 0xA;
            debug_Printf(0xA, D_0063C2C0, 0x0FFFFFFF, D_005551E0);
        }
        return 1;
    }
    return 0;
}

extern void sceVu0UnitMatrix(void *m);
extern void sceVu0RotMatrixX(void *d, void *s, float a);
extern void sceVu0RotMatrixY(void *d, void *s, float a);
extern void sceVu0ApplyMatrix(void *d, void *m, void *v);
extern float _GetDirection(float *a0);
extern int collisionCheck(char *gobj);
extern void pendulum_Process(void *a0, int a1);
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
    char *cw = *(char **)(*(int *)(a0 + 0x15C) + 0x830);

    pendulum_Process(cw + 0x20, collisionCheck((char *)a0));
    ChainPendulumSwing(pos, cw, (float *)(cw + 0x20));
    sceVu0AddVector(pos, *(void **)(cw + 0xD0), pos);
    chain_sub_pendulum(*(char **)(cw + 0xD0), *(int *)(cw + 0x68), pos);
    chain_sub_simulate(a0, *(ChainNode **)(cw + 0xD0), *(int *)(cw + 0x68), *(int *)(cw + 0x74), 1,
                       0, 20.0f, 50.0f, 0.6f);
}

extern char D_005551F0[];
extern void chain_simulate_term_simple(int a0);

void chain_simulate_term_ropeturn(int a0)
{
    char *cw = *(char **)(*(int *)(a0 + 0x15C) + 0x830);

    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 0xA;
        debug_Printf(0xA, D_0063C2C0, 0x0FFFFFFF, D_005551F0);
    }
    *(float *)(cw + 0x44) = -0.4f;
    chain_simulate_term_simple(a0);
}

extern char D_00555210[];

void chain_simulate_term_loop(int a0)
{
    char *cw = *(char **)(*(int *)(a0 + 0x15C) + 0x830);

    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 0xA;
        debug_Printf(0xA, D_0063C2C0, 0x0FFFFFFF, D_00555210);
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
    char *cw = *(char **)(*(int *)(a0 + 0x15C) + 0x830);

    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 0xA;
        debug_Printf(0xA, D_0063C2C0, 0x0FFFFFFF, D_00555230);
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
    char *cw = *(char **)(*(int *)(a0 + 0x15C) + 0x830);
    float h;

    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 0xA;
        debug_Printf(0xA, D_0063C2C0, 0x0FFFFFFF, D_00555250);
    }

    h = *(float *)(*(int *)((char *)D_00639EA4 + 0x15C) + 0x4AC);

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

ASM_LIT4_SLOT(D_00639168, -0.05f);
ASM_LIT4_SLOT(D_0063916C, -0.15f);
ASM_LIT4_SLOT(D_00639170, -1.5707964f);
INCLUDE_ASM("asm/nonmatchings/ico2/omori/src/chain", chain_simulate_term_moveup);

extern char D_005552B0[];

void chain_simulate_term_free(int a0)
{
    char *cw = *(char **)(*(int *)(a0 + 0x15C) + 0x830);

    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 0xA;
        debug_Printf(0xA, D_0063C2C0, 0x0FFFFFFF, D_005552B0);
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

ASM_LIT4_SLOT(D_00639180, -0.01f);
ASM_LIT4_SLOT(D_00639184, -0.05f);
ASM_LIT4_SLOT(D_00639188, -0.15f);
ASM_LIT4_SLOT(D_0063918C, -1.5707964f);
INCLUDE_ASM("asm/nonmatchings/ico2/omori/src/chain", chain_simulate_term_down);

extern char D_005552E0[];

void chain_simulate_hangstart(int a0)
{
    char *cw = *(char **)(*(int *)(a0 + 0x15C) + 0x830);

    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 0xA;
        debug_Printf(0xA, D_0063C2C0, 0x0FFFFFFF, D_005552E0);
    }
    *(float *)(cw + 0x44) = -1.5f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    chain_simulate_term_simple(a0);
}

extern char D_00555300[];

void chain_simulate_term(int a0)
{
    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 0xA;
        debug_Printf(0xA, D_0063C2C0, 0x0FFFFFFF, D_00555300);
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
    char *cw = *(char **)(*(int *)(a0 + 0x15C) + 0x830);

    ResetChainNodes(cw, (float *)(cw + 0x10));
    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 0xA;
        debug_Printf(0xA, D_0063C2C0, 0x0FFFFFFF, D_00555318);
    }
}

extern char D_00555330[];

void chain_simulate_free(int a0)
{
    char *cw = *(char **)(*(int *)(a0 + 0x15C) + 0x830);
    int i;

    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 0xA;
        debug_Printf(0xA, D_0063C2C0, 0x0FFFFFFF, D_00555330);
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

extern void memset(void *a0, int a1, int a2);
extern float atan2f(float y, float x);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_RotMatrixX(short a0);
extern void MatrixDrive_RotMatrixY(short a0);
extern void MatrixDrive_SetTransposeMatrix(void *d, void *s);

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

ASM_LIT4_SLOT(D_00639198, 0.2f);
INCLUDE_ASM("asm/nonmatchings/ico2/omori/src/chain", pendulum_Process);
ASM_LIT4_SLOT(D_0063919C, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/ico2/omori/src/chain", InitChainGeo);

extern float GetTableCos(short a0);
extern float GetTableSin(short a0);
extern void _ApplyRyGV(void *a0, float a1);

void chain_set_charachara(char *gobj, float amp)
{
    float v[4];
    char *cw = *(char **)(*(int *)(gobj + 0x15C) + 0x830);
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

ASM_LIT4_SLOT(D_006391A4, -0.2f);
ASM_LIT4_SLOT(D_006391A8, 0.1f);
ASM_LIT4_SLOT(D_006391AC, -0.2f);
ASM_LIT4_SLOT(D_006391B0, 0.1f);
INCLUDE_ASM("asm/nonmatchings/ico2/omori/src/chain", ChainGeo);

extern void _SubVector(void *d, void *a, void *b);
extern void _NormalizeVector(void *d, void *s);
extern void GetDifferencialQuaternionWithNoRegularize(void *d, void *a, void *b);
extern void MultiQuaternion(void *d, void *a, void *b);
extern void CopyVector(void *d, void *s);
extern void GetMatrixFromQuaternionPos(void *m, void *q, void *pos);
extern void p2o_DispVU1DObjMulti(void *ext);

void ChainDL(char *gobj)
{
    char q[0x10];
    char up[0x10];
    char d[0x10];
    char n[0x10];
    char dq[0x10];
    char *ext = *(char **)(gobj + 0x15C);
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
        GetMatrixFromQuaternionPos(*(char **)(*(int *)(gobj + 0x15C) + 0xC) + (i << 6), q, p);
    }
    p2o_DispVU1DObjMulti(ext);
}

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
    char *cw = *(char **)(*(int *)(gobj + 0x15C) + 0x830);
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
    char *cw = *(char **)(*(int *)(gobj + 0x15C) + 0x830);
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

ASM_LIT4_SLOT(D_006391B4, 1.5707964f);
ASM_LIT4_SLOT(D_006391B8, 1.5707964f);
ASM_LIT4_SLOT(D_006391BC, 1.5707964f);
INCLUDE_ASM("asm/nonmatchings/ico2/omori/src/chain", TestChainUpDown);

extern void SetDirectRootPositionNoFittingWithNodePoint(char *gobj, int node, float *pos, float t);

void SetChainRootUpdateMode(char *gobj, int mode, float *pos)
{
    *(int *)(*(int *)(gobj + 0x15C) + 0x420) = mode;
    ((ChainVal *)(*(int *)(gobj + 0x15C) + 0x410))->f = pos[0];
    ((ChainVal *)(*(int *)(gobj + 0x15C) + 0x414))->f = pos[1];
    ((ChainVal *)(*(int *)(gobj + 0x15C) + 0x418))->f = pos[2];
    if (mode == 3) {
        SetDirectRootPositionNoFittingWithNodePoint(gobj, 0x16, pos, 1.0f);
    }
}

void HoldChain(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    StartPendulum(a0);
    *(char *)(p + 0x60) = 1;
}

void ReleaseChain(char *a0)
{
    *(char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x60) = 0;
}

void GetChainPendulum(char *a0, float *a, float *b, float *c)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    *a = *(float *)(p + 0x30);
    *b = *(float *)(p + 0x34);
    if (*(float *)(p + 0x48) < *(float *)(p + 0x34)) {
        *b = *(float *)(p + 0x48);
    }
    *c = *(float *)(p + 0x40);
}

void IncreasePdlChain(char *a0)
{
    *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x44) = 0.1f;
}

extern int D_0063B218;

void DecreasePdlChain(char *a0)
{
    *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x44) =
        (float)D_0063B218 * 0.5f * -0.1f;
}

void PlumbOrientUpdateChain(char *a0, float *src)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    *(float *)(p + 0x20) = src[0];
    *(float *)(p + 0x24) = src[1];
    *(float *)(p + 0x28) = src[2];
}

int isBottomOfChain(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    return *(int *)(p + 0x68) == *(int *)(p + 0x74) - 1;
}

int isStopChain(char *a0)
{
    return *(unsigned char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xC0);
}

void GetChainClimbOrient(float *dst, char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    dst[0] = *(float *)(p + 0xB0);
    dst[1] = *(float *)(p + 0xB4);
    dst[2] = *(float *)(p + 0xB8);
}

int CheckChainClimbablePos(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);

    if (*(unsigned char *)(p + 0xA0) != 0 && *(int *)(p + 0x68) < 3)
        return 1;
    return 0;
}

typedef struct {
    int a, b, c;
} ClimbCol;

void GetChainClimbCollision(ClimbCol *dst, char *a0)
{
    *dst = *(ClimbCol *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xA4);
}

void SetChainParentGObj(char *a0, void *a1)
{
    *(void **)(*(char **)(*(char **)(a0 + 0x15C) + 0x830)) = a1;
}

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * GetChainDirCorrectVal's lines into _GetCorrectOrientOfChain, so it is a
 * public `inline` of the deferred tail; until the tail's asm members are C the
 * copy is emitted here as a plain function at its ROM position and the caller
 * inlines the static stand-in getChainDirCorrectVal, which collapses at layout. */
int GetChainDirCorrectVal(char *a0, int *a1)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    *a1 = (int)(*(float *)(p + 0x70) * 180.0f / 3.1415927f);
    return *(unsigned char *)(p + 0x6C);
}

static inline int getChainDirCorrectVal(char *a0, int *a1)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    *a1 = (int)(*(float *)(p + 0x70) * 180.0f / 3.1415927f);
    return *(unsigned char *)(p + 0x6C);
}

extern float *test_CURRENTROOT(void *a0);

void GetRootPositionHandExtra(void *a0, float *a1)
{
    a1[0] = test_CURRENTROOT(a0)[0];
    a1[1] = test_CURRENTROOT(a0)[1];
    a1[2] = test_CURRENTROOT(a0)[2];
    a1[1] -= 50.0f;
}

extern int D_0063B214;
extern float FSqrt(float a0);

void InitPendulum(char *a0)
{
    char *cw = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
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
    *(char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xCC) = 1;
}

void UnLockChainGeo(char *a0)
{
    *(char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xCC) = 0;
}

float GetChainHangRange(char *a0)
{
    return *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xC8);
}

float GetChainLength(char *a0)
{
    return (float)(*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x74) - 1) * 50.0f;
}

void EnableChainHang(char *a0)
{
    *(char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xCD) = 1;
}

void UnableChainHang(char *a0)
{
    *(char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xCD) = 0;
}

int IsAbleChainHang(char *a0)
{
    return *(unsigned char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xCD);
}

extern void UpdateRootMatrix(void *a0);
extern void GetRootPosition(void *a0, void *a1);

void ChainPositionReset(char *a0)
{
    float pos[4];
    char *cw = *(char **)(*(char **)(a0 + 0x15C) + 0x830);

    UpdateRootMatrix(a0);
    GetRootPosition(pos, a0);
    ResetChainNodes(cw, pos);
}

extern float _GetDirection(float *a0);
extern int RoundDegGV(int a0);
extern int AlignDegGV(int a0);
extern void _ApplyRyGV(void *a0, float a1);

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

extern float FSqrt(float a0);

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

extern float _DistSqGV(void *a, void *b);
extern float D_0063ABD8[];

int GetChainNearestNodePosition(float *out, char *gobj, float *p)
{
    char *cw = *(char **)(*(char **)(gobj + 0x15C) + 0x830);

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
