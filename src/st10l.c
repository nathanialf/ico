#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st10l", actSt10lInit);

extern long long D_0061BE50[];
extern long long D_0061BE60[];
extern void _ACTWait(int a0);
extern void scpDispOffAllWithKind(int *buf, int a1);

void actSt10lFloorLeft(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061BE60[0]; long long v0b=D_0061BE50[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061BE60[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061BE50[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

extern int D_00631AE8;
extern void _ACTWait(int a0);
extern int func_0017B230(int a0);
extern void func_0017B258(int a0);

void actSt10lFloorRight(volatile int a0) {
    if (D_00631AE8 == 0) { _ACTWait(0); }
    while (D_00631AE8 == 0 || func_0017B230(0x98) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_0017B258(0x99);
    func_0017B258(0x9A);
}

INCLUDE_ASM("asm/nonmatchings/src/st10l", actSt10lGondolaUp);

INCLUDE_ASM("asm/nonmatchings/src/st10l", actSt10lGondolaDown);

INCLUDE_ASM("asm/nonmatchings/src/st10l", actSt10lEneCam3Chk);

INCLUDE_ASM("asm/nonmatchings/src/st10l", actSt10lChainMove);

INCLUDE_ASM("asm/nonmatchings/src/st10l", actSt10lChain);

extern int D_00274EC0[];
extern int func_00262BE8(int a0, long a1);
extern int func_00263160(int a0);
extern int func_00263218(int a0);

void actSt10lFloor(volatile int a0) {
    _ACTWait(func_00263218(func_00262BE8(func_00263160((0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1]), (long)0x804C << 47)));
    func_0017B258(0xCE);
}

extern void AddWayPointTop(int a0, int a1);

void actSt10lGondola(void) {
    if (func_0017B230(0x5F) == 0) {
        AddWayPointTop(0x9, 0);
        AddWayPointTop(0xA, 0);
    } else {
        AddWayPointTop(0x9, 1);
        AddWayPointTop(0xA, 1);
    }
    if (func_0017B230(0x60) == 0) {
        AddWayPointTop(0xC, 0);
    } else {
        AddWayPointTop(0xC, 1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_00225FE0);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_002260A8);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_002261F8);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_00226300);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_00226478);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_002265F0);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_002266D0);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_002267E8);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_00226958);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_00226AF0);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_00226BA0);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_00226C08);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_00226C70);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_00226D08);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_00226D90);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_00226E18);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_00226EC0);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_00226F28);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_00226FE8);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_002270A8);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_00227160);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_002271E8);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_00227280);

INCLUDE_ASM("asm/nonmatchings/src/st10l", func_002272E8);

