#include "common.h"

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

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", InitChainGeo);

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

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", PlumbOrientUpdateChain);

void isBottomOfChain(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    void *q = *(void **)((char *)p + 0x7F0);
    *(char *)((char *)q + 0x60) = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", isStopChain);

extern float D_0062927C;

void GetChainClimbOrient(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    void *q = *(void **)((char *)p + 0x7F0);
    *(float *)((char *)q + 0x44) = D_0062927C;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", CheckChainClimbablePos);

void GetChainClimbCollision(void *a0, float *a1) {
    void *p = *(void **)((char *)a0 + 0x15C);
    void *q = *(void **)((char *)p + 0x7F0);
    *(float *)((char *)q + 0x20) = a1[0];
    *(float *)((char *)q + 0x24) = a1[1];
    *(float *)((char *)q + 0x28) = a1[2];
}

int SetChainParentGObj(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return *(int *)((char *)q + 0x68) == *(int *)((char *)q + 0x74) - 1;
}

int GetChainDirCorrectVal(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return *(unsigned char *)((char *)q + 0xC0);
}

void GetRootPositionHandExtra(float *a0, void *a1) {
    void *p = *(void **)((char *)a1 + 0x15C);
    void *q = *(void **)((char *)p + 0x7F0);
    a0[0] = *(float *)((char *)q + 0xB0);
    a0[1] = *(float *)((char *)q + 0xB4);
    a0[2] = *(float *)((char *)q + 0xB8);
}

int InitPendulum(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    void *q = *(void **)((char *)p + 0x7F0);
    if (*(unsigned char *)((char *)q + 0xA0)) {
        if (*(int *)((char *)q + 0x68) < 3) {
            return 1;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", LockChainGeo);

void UnLockChainGeo(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    q[0] = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", GetChainHangRange);


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
