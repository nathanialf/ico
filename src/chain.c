#include "common.h"



extern int D_00632744;
extern int D_006D0680[];
extern int D_00632D30;
INCLUDE_ASM("asm/nonmatchings/src/chain", UpdateRootPosition);

void StartPendulum(void *dst, float *out) {
    long long *s = (long long *)D_006D0680;
    long long *d = (long long *)dst;
    float val = (float)D_00632D30 / 100.0f;
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
    d[3] = s[3];
    __asm__ __volatile__("" : "+f"(val));
    *out = val;
}

INCLUDE_ASM("asm/nonmatchings/src/chain", collisionCheck);

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term_simple);

void chain_simulate_term_loop(void) {
    D_00632744 = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term_swingready);

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term_swingstart);

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term_moveup);

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term_free);

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term_down);

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_hangstart);

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_term);

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_stop);

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_free);

INCLUDE_ASM("asm/nonmatchings/src/chain", correct_vector);

INCLUDE_ASM("asm/nonmatchings/src/chain", pendulum_Process);

INCLUDE_ASM("asm/nonmatchings/src/chain", InitChainGeo);

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_simulate_climb);

INCLUDE_ASM("asm/nonmatchings/src/chain", chain_set_charachara);

INCLUDE_ASM("asm/nonmatchings/src/chain", ChainGeo);

INCLUDE_ASM("asm/nonmatchings/src/chain", ChainDL);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018E5B0);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018EB70);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018ECC8);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018F640);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018F798);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018F8E8);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_0018FA70);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_00190298);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_001902C8);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_001902D8);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_00190318);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_00190330);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_00190360);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_00190388);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_001903A8);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_001903B8);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_001903E0);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_00190408);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_00190430);

INCLUDE_ASM("asm/nonmatchings/src/chain", func_00190440);

