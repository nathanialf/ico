#include "common.h"
#include "ico/types.h"

extern void playSEConditionID(int a0, int a1);

void RopeFixGeo(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/ropeFix", RopeFixDL);

extern int isysGObjSearchFromObjLayoutID(int a0);
extern int UnLockChainGeo(int a0, int a1);

void InitRopeFixGeo(int a0)
{
    int v0 = isysGObjSearchFromObjLayoutID(0x15);
    if (v0 != 0) {
        return UnLockChainGeo(v0, a0);
    }
}

extern int func_0010F068(int a0);
extern int file_LoadCDFile(int a0);

void func_001E6B28(int a0)
{
    int *s0 = ((GObj *)((char *)a0))->p_15C;
    if (s0[0x74 / 4] != 0) {
        func_0010F068(a0);
        return file_LoadCDFile((int)s0);
    }
}

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
