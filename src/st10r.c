#include "common.h"

void actSt10rFloor(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st10r", actSt10rCage);

extern int D_00274EC0[];
extern void _ACTWait(int a0);
extern void func_0017B258(int a0);
extern int func_00262BE8(int a0, long a1);
extern int func_00263160(int a0);
extern int func_00263218(int a0);

void actSt10rTower(volatile int a0) {
    _ACTWait(func_00263218(func_00262BE8(func_00263160((0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1]), (long)0x8054 << 47)));
    func_0017B258(0x5F);
}

void actSt10rExit(int x) {
    volatile int local = x;
}

extern long long D_0061BEB0[];
extern long long D_0061BEC0[];
extern void scpDispOffAllWithKind(int *buf, int a1);

void actSt10rChain(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061BEB0[0]; long long v0b=D_0061BEC0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061BEB0[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061BEC0[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

void actSt10rSekizo(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061BEC0[0]; long long v0b=D_0061BEB0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061BEC0[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061BEB0[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

extern int D_004D2630[];
extern int D_006325B4;

void actSt10rEne(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_006325B4 = 0;
    *(int *)(gobj + 0xC0) = (int)D_004D2630;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct { char pad[0xC0]; void *f_C0; void *f_C4; } St10rBox;
extern int *D_004D2670[];
extern void func_002265F0(volatile int a0);
extern int D_006325B4;

void func_002276F8(volatile int a0) {
    St10rBox *obj = *(St10rBox **)(a0 + 0x164);
    D_006325B4 = 1;
    D_004D2670[1] = (int *)func_002265F0;
    obj->f_C0 = 0;
    obj->f_C4 = (void *)D_004D2670;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_00631AE4;
extern void actSt25aQueenDead(int a0, int a1, int a2, float f12, float f13);
extern int func_0017B230(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);

void actSt10rEnemy1(volatile int a0) {
    while (func_0017B230(0x5F) != 0 || scpSleepEnemyOne(a0, D_00631AE4, 400.0f) == 0) {
        _ACTWait(1);
    }
    actSt25aQueenDead(3, D_00631AE4, 0, 16.0f, 16.0f);
}

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_002277C0);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_00227868);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_002278E0);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_00227940);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_002279B0);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_00227A48);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_00227AE0);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_00227BA8);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_00227C70);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_00227D18);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_00227DC0);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_00227E68);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_00227F10);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_00227FD8);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_002280B8);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_00228198);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_00228260);

INCLUDE_ASM("asm/nonmatchings/src/st10r", func_002282D8);

