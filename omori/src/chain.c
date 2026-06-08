#include "common.h"

/* chain 0x7F0 view (local) */
typedef struct {
    int f_0; char _pad4[0x1C];
    float f_20, f_24, f_28; char _pad2C[0x18];
    float f_44; char _pad48[0x18];
    char f_60; char _pad61[7];
    int f_68; unsigned char f_6C; char _pad6D[3];
    float f_70; int f_74; char _pad78[0x28];
    unsigned char f_A0; char _padA1[0xF];
    float f_B0, f_B4, f_B8; char _padBC[4];
    unsigned char f_C0;
} ChainGeo;

extern int D_0062AA10;
extern int D_006C9F60[];

void *UpdateRootPosition(void) {
    if (D_0062AA10 == 0) {
        return 0;
    }
    return D_006C9F60;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", StartPendulum);

extern unsigned char D_0062C07D;
extern int D_0062A9E4;

void collisionCheck(void) {
    D_0062C07D = 1;
}

void chain_simulate_term_simple(void) {
    D_0062A9E4 = 1;
}

extern int D_0062AA20;

void chain_simulate_term_loop(void) {
    D_0062AA20 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", chain_simulate_term_swingready);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", chain_simulate_term_swingstart);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", chain_simulate_term_moveup);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", chain_simulate_term_free);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", chain_simulate_term_down);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", chain_simulate_hangstart);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", chain_simulate_term);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", chain_simulate_stop);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", chain_simulate_free);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", correct_vector);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", pendulum_Process);

extern int D_0062AF84;
extern int D_0062C090;
extern void traceLine(int a, int b, int c, const char *d);
extern void chain_simulate_term_free(int a0);

extern char D_00554D68[];

void InitChainGeo(int a0)
{
    if (D_0062AF84 & 1) {
        D_0062C090 = D_0062C090 + 0xA;
        traceLine(0xA, D_0062C090, 0x0FFFFFFF, D_00554D68);
    }
    chain_simulate_term_free(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", chain_simulate_climb);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", chain_set_charachara);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", ChainGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", ChainDL);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", GetPositionOnTheChain);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", PlumbPointUpdateChain);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", TestChainUpDown);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", HoldChain);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", ReleaseChain);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", GetChainPendulum);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", IncreasePdlChain);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", DecreasePdlChain);

extern void chain_simulate_term_swingstart(void *a0);

void PlumbOrientUpdateChain(void *a0) {
    ChainGeo *p = *(ChainGeo **)(*(char **)((char *)a0 + 0x15C) + 0x7F0);
    chain_simulate_term_swingstart(a0);
    p->f_60 = 1;
}

void isBottomOfChain(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    ChainGeo *q = *(ChainGeo **)((char *)p + 0x7F0);
    q->f_60 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", isStopChain);

extern float D_0062927C;

void GetChainClimbOrient(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    ChainGeo *q = *(ChainGeo **)((char *)p + 0x7F0);
    q->f_44 = D_0062927C;
}

extern int D_0062B060;
extern float D_00629280;

void CheckChainClimbablePos(void *a0) {
    ChainGeo *p = *(ChainGeo **)(*(char **)((char *)a0 + 0x15C) + 0x7F0);
    p->f_44 = (float)D_0062B060 * 0.5f * D_00629280;
}

void GetChainClimbCollision(void *a0, float *a1) {
    void *p = *(void **)((char *)a0 + 0x15C);
    ChainGeo *q = *(ChainGeo **)((char *)p + 0x7F0);
    q->f_20 = a1[0];
    q->f_24 = a1[1];
    q->f_28 = a1[2];
}

int SetChainParentGObj(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    ChainGeo *q = *(ChainGeo **)((char *)p + 0x7F0);
    return q->f_68 == q->f_74 - 1;
}

int GetChainDirCorrectVal(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    ChainGeo *q = *(ChainGeo **)((char *)p + 0x7F0);
    return q->f_C0;
}

void GetRootPositionHandExtra(float *a0, void *a1) {
    void *p = *(void **)((char *)a1 + 0x15C);
    ChainGeo *q = *(ChainGeo **)((char *)p + 0x7F0);
    a0[0] = q->f_B0;
    a0[1] = q->f_B4;
    a0[2] = q->f_B8;
}

int InitPendulum(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    ChainGeo *q = *(ChainGeo **)((char *)p + 0x7F0);
    if (q->f_A0) {
        if (q->f_68 < 3) {
            return 1;
        }
    }
    return 0;
}

typedef struct { unsigned int lo; unsigned char m[3]; unsigned char hi; } Blk8;
typedef struct { Blk8 a; int b; } Geo12;

void LockChainGeo(char *a0, void *a1) {
    int *p = *(int **)((char *)a1 + 0x15C);
    ChainGeo *q = *(ChainGeo **)((char *)p + 0x7F0);
    *(Geo12 *)a0 = *(Geo12 *)((char *)q + 0xA4);
}

void UnLockChainGeo(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    ChainGeo *q = *(ChainGeo **)((char *)p + 0x7F0);
    q->f_0 = a1;
}

extern float D_00629284;

int GetChainHangRange(char *a0, int *a1) {
    char *p = *(char **)(a0 + 0x15C);
    ChainGeo *v = *(ChainGeo **)(p + 0x7F0);
    *a1 = (int)(v->f_70 * 180.0f / D_00629284);
    return v->f_6C;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_28;  /* 0x28 */
} S_002872D0;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00554F10;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00554F50;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00554F80;  /* stride 0x4 */

/* end struct shapes */
