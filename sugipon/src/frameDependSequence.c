#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/frameDependSequence", playSE);

extern float D_0062B6B4;
extern void func_001CE340(int a0, int a1, int a2);
extern void playSE(int a0);

void playSERandomID(int a0, int a1, int a2) {
    D_0062B6B4 = 1.0f;
    if (a0) {
        func_001CE340(a0, a1, a2);
    } else {
        playSE(a1);
    }
}

extern void playSERandomID(int a0, int a1, int a2);

void playSEConditionID(int a0, int a1) {
    playSERandomID(a0, a1, 0);
}

extern float D_0062B6B4;
extern void func_001CE340(int a0, int a1, int a2);

void playEff(int a0, int a1, float f) {
    D_0062B6B4 = f;
    func_001CE340(a0, a1, 0);
}

extern void soundSeGroupGet(int a0);

void execEff(int a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    p += a1;
    soundSeGroupGet(p[0x183]);
}

extern void execEff(int a0, int a1);

void ExecFrameDependSequence(int a0) {
    execEff(a0, 0);
}

typedef struct {
    int b[0x13];
} SEPackage;

extern SEPackage D_004BC220;

void executeSEPackageByGObj(void *a0) {
    *(SEPackage *)a0 = D_004BC220;
}

extern int GetFlyLimitHeight(void);
extern int GetFlyLimitClearance(int a0);
extern int func_001CDBB0(int a0);

int executeSEPackageWithNoGObj(int a0) {
    if (a0 <= 0xFFFF) {
        return GetFlyLimitHeight();
    } else if (a0 <= 0x1FFFF) {
        return GetFlyLimitClearance(a0 - 0x10000);
    } else {
        return func_001CDBB0(a0 - 0x20000);
    }
}

int ExecuteSEPackageWithGroupVariation(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    return (int)(*(float *)((char *)p + 0x634)) < a1;
}

int ExecuteSEPackage(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    return p[0x21] == a1;
}
