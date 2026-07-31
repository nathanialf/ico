#include "common.h"

typedef struct {
    int b[0x13];
} SEPackage;


extern float D_006333F0;
extern void func_001D0FA8();
INCLUDE_ASM("asm/nonmatchings/src/frameDependSequence", playSE);

void playSERandomID(a0, a1)
int a0, a1;
{
    D_006333F0 = 1.0f;
    if (a0) {
        func_001D0FA8(a0);
    } else {
        playSE(a1);
    }
}


void playSEConditionID(int a0, int a1) {
    playSERandomID(a0, a1, 0);
}

void playEff(int a0, int a1, float f)
{
    D_006333F0 = f;
    func_001D0FA8(a0, a1, 0);
}

extern void soundSeGroupGet(int a0);

void execEff(int a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    p += a1;
    soundSeGroupGet(p[0x187]);
}

extern void execEff(int a0, int a1);

void ExecFrameDependSequence(int a0) {
    execEff(a0, 0);
}

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

int ExecuteSEPackageWithGroupVariation(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    return (int)(*(float *)((char *)p + 0x644)) < a1;
}

int ExecuteSEPackage(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    return p[0x21] == a1;
}

