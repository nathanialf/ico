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
INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_free);
INCLUDE_ASM("asm/nonmatchings/src/chain", correct_vector);
INCLUDE_ASM("asm/nonmatchings/src/chain", pendulum_Process);
INCLUDE_ASM("asm/nonmatchings/src/chain", InitChainGeo);
INCLUDE_ASM("asm/nonmatchings/src/chain", chain_set_charachara);
INCLUDE_ASM("asm/nonmatchings/src/chain", ChainGeo);
INCLUDE_ASM("asm/nonmatchings/src/chain", ChainDL);
INCLUDE_ASM("asm/nonmatchings/src/chain", GetPositionOnTheChain);
INCLUDE_ASM("asm/nonmatchings/src/chain", PlumbPointUpdateChain);
INCLUDE_ASM("asm/nonmatchings/src/chain", TestChainUpDown);
INCLUDE_ASM("asm/nonmatchings/src/chain", SetChainRootUpdateMode);
INCLUDE_ASM("asm/nonmatchings/src/chain", HoldChain);
INCLUDE_ASM("asm/nonmatchings/src/chain", ReleaseChain);
INCLUDE_ASM("asm/nonmatchings/src/chain", GetChainPendulum);
INCLUDE_ASM("asm/nonmatchings/src/chain", IncreasePdlChain);
INCLUDE_ASM("asm/nonmatchings/src/chain", DecreasePdlChain);
INCLUDE_ASM("asm/nonmatchings/src/chain", PlumbOrientUpdateChain);
INCLUDE_ASM("asm/nonmatchings/src/chain", isBottomOfChain);
INCLUDE_ASM("asm/nonmatchings/src/chain", isStopChain);
INCLUDE_ASM("asm/nonmatchings/src/chain", GetChainClimbOrient);
INCLUDE_ASM("asm/nonmatchings/src/chain", CheckChainClimbablePos);
INCLUDE_ASM("asm/nonmatchings/src/chain", GetChainClimbCollision);
INCLUDE_ASM("asm/nonmatchings/src/chain", SetChainParentGObj);
INCLUDE_ASM("asm/nonmatchings/src/chain", GetChainDirCorrectVal);
extern float *test_CURRENTROOT(void *a0);

void GetRootPositionHandExtra(void *a0, float *a1) {
    a1[0] = test_CURRENTROOT(a0)[0];
    a1[1] = test_CURRENTROOT(a0)[1];
    a1[2] = test_CURRENTROOT(a0)[2];
    a1[1] -= 50.0f;
}
INCLUDE_ASM("asm/nonmatchings/src/chain", InitPendulum);
INCLUDE_ASM("asm/nonmatchings/src/chain", LockChainGeo);
INCLUDE_ASM("asm/nonmatchings/src/chain", UnLockChainGeo);
INCLUDE_ASM("asm/nonmatchings/src/chain", GetChainHangRange);
INCLUDE_ASM("asm/nonmatchings/src/chain", GetChainLength);
INCLUDE_ASM("asm/nonmatchings/src/chain", EnableChainHang);
INCLUDE_ASM("asm/nonmatchings/src/chain", UnableChainHang);
INCLUDE_ASM("asm/nonmatchings/src/chain", IsAbleChainHang);
INCLUDE_ASM("asm/nonmatchings/src/chain", ChainPositionReset);
INCLUDE_ASM("asm/nonmatchings/src/chain", _GetCorrectOrientOfChain);
INCLUDE_ASM("asm/nonmatchings/src/chain", chain_sub_simulate);
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
INCLUDE_ASM("asm/nonmatchings/src/chain", GetChainNearestNodePosition);
