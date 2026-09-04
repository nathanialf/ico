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
extern float D_006391C0;
void IncreasePdlChain(char *a0) {
    *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x44) = D_006391C0;
}
extern int D_0063B218;
extern float D_006391C4;
void DecreasePdlChain(char *a0) {
    *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x44) = (float)D_0063B218 * 0.5f * D_006391C4;
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
INCLUDE_ASM("asm/nonmatchings/src/chain", CheckChainClimbablePos);
typedef struct { int a, b, c; } ClimbCol;
void GetChainClimbCollision(ClimbCol *dst, char *a0) {
    *dst = *(ClimbCol *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xA4);
}
void SetChainParentGObj(char *a0, void *a1) {
    *(void **)(*(char **)(*(char **)(a0 + 0x15C) + 0x830)) = a1;
}
extern float D_006391C8;
int GetChainDirCorrectVal(char *a0, int *a1) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    *a1 = (int)(*(float *)(p + 0x70) * 180.0f / D_006391C8);
    return *(unsigned char *)(p + 0x6C);
}
extern float *test_CURRENTROOT(void *a0);

void GetRootPositionHandExtra(void *a0, float *a1) {
    a1[0] = test_CURRENTROOT(a0)[0];
    a1[1] = test_CURRENTROOT(a0)[1];
    a1[2] = test_CURRENTROOT(a0)[2];
    a1[1] -= 50.0f;
}
INCLUDE_ASM("asm/nonmatchings/src/chain", InitPendulum);
void LockChainGeo(char *a0) {
    *(char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xCC) = 1;
}
void UnLockChainGeo(char *a0) {
    *(char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xCC) = 0;
}
float GetChainHangRange(char *a0) {
    return *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xC8);
}
INCLUDE_ASM("asm/nonmatchings/src/chain", GetChainLength);
void EnableChainHang(char *a0) {
    *(char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xCD) = 1;
}
void UnableChainHang(char *a0) {
    *(char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xCD) = 0;
}
int IsAbleChainHang(char *a0) {
    return *(unsigned char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xCD);
}
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
