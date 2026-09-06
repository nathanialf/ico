#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/chain", UpdateRootPosition);
INCLUDE_ASM("asm/nonmatchings/src/chain", StartPendulum);
INCLUDE_ASM("asm/nonmatchings/src/chain", collisionCheck);
INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term_simple);
INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term_ropeturn);
INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term_loop);
INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term_swingready);
INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term_swingstart);
INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term_moveup);
INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term_free);
INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term_down);
INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_hangstart);
extern char D_00555300[];
extern int D_0063B13C;
extern int D_0063C2C0;
extern void chain_simulate_term_simple(int a0);
extern void debug_Printf(int a, int b, int c, const char *d);

void chain_simulate_term(int a0)
{
    if (D_0063B13C & 1) {
        D_0063C2C0 = D_0063C2C0 + 0xA;
        debug_Printf(0xA, D_0063C2C0, 0x0FFFFFFF, D_00555300);
    }
    chain_simulate_term_simple(a0);
}
INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_stop);
ASM_LIT4_SLOT(D_00639190, 0.675f);
INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_free);
ASM_LIT4_SLOT(D_00639194, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/chain", correct_vector);
ASM_LIT4_SLOT(D_00639198, 0.2f);
INCLUDE_ASM("asm/nonmatchings/src/chain", pendulum_Process);
ASM_LIT4_SLOT(D_0063919C, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/chain", InitChainGeo);
ASM_LIT4_SLOT(D_006391A0, 3.1415927f);
INCLUDE_ASM("asm/nonmatchings/src/chain", chain_set_charachara);
ASM_LIT4_SLOT(D_006391A4, -0.2f);
ASM_LIT4_SLOT(D_006391A8, 0.1f);
ASM_LIT4_SLOT(D_006391AC, -0.2f);
ASM_LIT4_SLOT(D_006391B0, 0.1f);
INCLUDE_ASM("asm/nonmatchings/src/chain", ChainGeo);
INCLUDE_ASM("asm/nonmatchings/src/chain", ChainDL);
INCLUDE_ASM("asm/nonmatchings/src/chain", GetPositionOnTheChain);
INCLUDE_ASM("asm/nonmatchings/src/chain", PlumbPointUpdateChain);
ASM_LIT4_SLOT(D_006391B4, 1.5707964f);
ASM_LIT4_SLOT(D_006391B8, 1.5707964f);
ASM_LIT4_SLOT(D_006391BC, 1.5707964f);
INCLUDE_ASM("asm/nonmatchings/src/chain", TestChainUpDown);
INCLUDE_ASM("asm/nonmatchings/src/chain", SetChainRootUpdateMode);
extern void StartPendulum(void *a0);
void HoldChain(char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    StartPendulum(a0);
    *(char *)(p + 0x60) = 1;
}
void ReleaseChain(char *a0) {
    *(char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x60) = 0;
}
void GetChainPendulum(char *a0, float *a, float *b, float *c) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    *a = *(float *)(p + 0x30);
    *b = *(float *)(p + 0x34);
    if (*(float *)(p + 0x48) < *(float *)(p + 0x34)) {
        *b = *(float *)(p + 0x48);
    }
    *c = *(float *)(p + 0x40);
}
void IncreasePdlChain(char *a0) {
    *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x44) = 0.1f;
}
extern int D_0063B218;
void DecreasePdlChain(char *a0) {
    *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x44) = (float)D_0063B218 * 0.5f * -0.1f;
}
void PlumbOrientUpdateChain(char *a0, float *src) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    *(float *)(p + 0x20) = src[0];
    *(float *)(p + 0x24) = src[1];
    *(float *)(p + 0x28) = src[2];
}
int isBottomOfChain(char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    return *(int *)(p + 0x68) == *(int *)(p + 0x74) - 1;
}
int isStopChain(char *a0) {
    return *(unsigned char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xC0);
}
void GetChainClimbOrient(float *dst, char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    dst[0] = *(float *)(p + 0xB0);
    dst[1] = *(float *)(p + 0xB4);
    dst[2] = *(float *)(p + 0xB8);
}
int CheckChainClimbablePos(char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);

    if (*(unsigned char *)(p + 0xA0) != 0 &&
        *(int *)(p + 0x68) < 3) return 1;
    return 0;
}
typedef struct { int a, b, c; } ClimbCol;
void GetChainClimbCollision(ClimbCol *dst, char *a0) {
    *dst = *(ClimbCol *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xA4);
}
void SetChainParentGObj(char *a0, void *a1) {
    *(void **)(*(char **)(*(char **)(a0 + 0x15C) + 0x830)) = a1;
}
/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * GetChainDirCorrectVal's lines into _GetCorrectOrientOfChain, so it is a
 * public `inline` of the deferred tail; until the tail's asm members are C the
 * copy is emitted here as a plain function at its ROM position and the caller
 * inlines the static stand-in getChainDirCorrectVal, which collapses at layout. */
int GetChainDirCorrectVal(char *a0, int *a1) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    *a1 = (int)(*(float *)(p + 0x70) * 180.0f / 3.1415927f);
    return *(unsigned char *)(p + 0x6C);
}
static inline int getChainDirCorrectVal(char *a0, int *a1) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    *a1 = (int)(*(float *)(p + 0x70) * 180.0f / 3.1415927f);
    return *(unsigned char *)(p + 0x6C);
}
extern float *test_CURRENTROOT(void *a0);

void GetRootPositionHandExtra(void *a0, float *a1) {
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
    *(float *)(cw + 0x40) = *(float *)(cw + 0x40) < 1.0f ? 1.0f
        : (*(float *)(cw + 0x40) > 255.0f ? 255.0f : *(float *)(cw + 0x40));

    *(float *)(cw + 0x38) = *(float *)(cw + 0x40) * 0.5f;
    *(float *)(cw + 0x48) = 360.0f;
    *(char *)(cw + 0x50) = 1;
}
void LockChainGeo(char *a0) {
    *(char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xCC) = 1;
}
void UnLockChainGeo(char *a0) {
    *(char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xCC) = 0;
}
float GetChainHangRange(char *a0) {
    return *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xC8);
}
float GetChainLength(char *a0) {
    return (float)(*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x74) - 1) * 50.0f;
}
void EnableChainHang(char *a0) {
    *(char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xCD) = 1;
}
void UnableChainHang(char *a0) {
    *(char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xCD) = 0;
}
int IsAbleChainHang(char *a0) {
    return *(unsigned char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xCD);
}
extern void UpdateRootMatrix(void *a0);
extern void GetRootPosition(void *a0, void *a1);

typedef struct {
    float x, y, z, w;
    float vx, vy, vz, vw;
} ChainNode;

static inline void ResetChainNodes(char *cw, float *pos)
{
    int i;

    for (i = 0; i < *(int *)(cw + 0x74); i++) {
        ChainNode *e = *(ChainNode **)(cw + 0xD0) + i;
        e->x = pos[0]; e->y = pos[1]; e->z = pos[2];
        e->y += (float)i * 50.0f;
        e->vx = 0.0f; e->vy = 0.0f; e->vz = 0.0f;
    }
}

void ChainPositionReset(char *a0)
{
    float pos[4];
    char *cw = *(char **)(*(char **)(a0 + 0x15C) + 0x830);

    UpdateRootMatrix(a0);
    GetRootPosition(pos, a0);
    ResetChainNodes(cw, pos);
}
extern void memset(void *a0, int a1, int a2);
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
extern void sceVu0SubVector(void *a0, void *a1, void *a2);
extern void sceVu0AddVector(void *a0, void *a1, void *a2);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);
extern void correct_vector(void *a0, void *a1);
extern float FSqrt(float a0);

void chain_sub_simulate(int a0, ChainNode *nd, int from, int to, unsigned char flag,
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
        if (l == 0.0f) continue;
        if (l < len && d[1] < 0.0f) continue;
        sceVu0ScaleVector(d, d, len / l);
        sceVu0AddVector(t, q, d);
        sceVu0SubVector(&p->vx, t, p);
        p->x = t[0];
        p->y = t[1];
        p->z = t[2];
    }
}
extern void _InterGV(char *elem, char *base, int a2, float a, float b);

void chain_sub_pendulum(char *base, int n, int a2)
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
            out[0] = e[0]; out[1] = e[1]; out[2] = e[2];
            best = d;
            ret = 1;
        }
    }
    return ret;
}
