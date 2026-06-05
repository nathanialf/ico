#include "common.h"

extern void playSEConditionID(int a0, int a1);

void RopeFixGeo(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/ropeFix", RopeFixDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/ropeFix", InitRopeFixGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/ropeFix", func_001E6B28);

int func_001E6B70(void) {
    return 0;
}

void func_001E6B78(int a0) {
    playSEConditionID(a0, 0x33);
}

extern void ExecFrameDependSequence(int a0);

void func_001E6B80(int a0) {
    ExecFrameDependSequence(a0);
    playSEConditionID(a0, 0x38);
}

typedef struct { char _0[0x30]; int f30; } RopeC;
typedef struct { char _0[0x7F0]; RopeC *f7F0; } RopeB;
typedef struct { char _0[0x15C]; RopeB *f15C; } RopeA;
extern void func_001AB9F8(RopeA *a0);

void func_001E6BB0(RopeA *a0) {
    RopeC *q = a0->f15C->f7F0;
    if (q->f30++ >= 0x1F) {
        q->f30 = 0;
        func_001AB9F8(a0);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/ropeFix", func_001E6BE0);

extern void func_001E6BE0(int a0, void *a1);
extern void func_0010F048(void *a0);

void func_001E6C48(char *self) {
    func_001E6BE0(*(int *)(*(char **)(self + 0x15C) + 0xC), self);
    func_0010F048(self);
}
