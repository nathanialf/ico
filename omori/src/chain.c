#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", UpdateRootPosition);

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

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", isBottomOfChain);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", isStopChain);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", GetChainClimbOrient);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", CheckChainClimbablePos);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", GetChainClimbCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", SetChainParentGObj);

int GetChainDirCorrectVal(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return *(unsigned char *)((char *)q + 0xC0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", GetRootPositionHandExtra);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", InitPendulum);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", LockChainGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", UnLockChainGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/chain", GetChainHangRange);
