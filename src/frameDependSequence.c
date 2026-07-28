#include "common.h"

typedef struct {
    int b[0x13];
} SEPackage;


extern float D_006333F0;
extern void func_001D0FA8();
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", playSE);

void playSERandomID(int a0, int a1)
{
    D_006333F0 = 1.0f;
    if (a0) {
        func_001D0FA8(a0);
    } else {
        playSE(a1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", playSEConditionID);

void playEff(int a0, int a1, float f)
{
    D_006333F0 = f;
    func_001D0FA8(a0, a1, 0);
}

INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", execEff);

INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", ExecFrameDependSequence);

extern SEPackage D_004C0F40;

void executeSEPackageByGObj(void *a0) {
    *(SEPackage *)a0 = D_004C0F40;
}

extern int GetFlyLimitClearance(int a0);
extern int GetFlyLimitHeight(void);
extern int func_001D0818(int a0);

int executeSEPackageWithNoGObj(int a0) {
    if (a0 <= 0xFFFF) {
        return GetFlyLimitHeight();
    } else if (a0 <= 0x1FFFF) {
        return GetFlyLimitClearance(a0 - 0x10000);
    } else {
        return func_001D0818(a0 - 0x20000);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", ExecuteSEPackageWithGroupVariation);

int ExecuteSEPackage(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    return p[0x21] == a1;
}

