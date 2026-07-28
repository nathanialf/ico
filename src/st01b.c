#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bInit);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEneChk);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bFloorChk);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bSekizo);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEne);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEnemy1);

extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int func_0017B230(int a0);

void actSt01bEnemy2(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0x25)==0){ _ACTWait(1); }
 _ACTWait(0x32); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); }

void actSt01bEnemy3(volatile int a0){
 int x=a0;
 actInitialize(a0);
 _ACTWait(1);
 Generator_Mask(a0);
 while(func_0017B230(0x25)==0){ _ACTWait(1); }
 _ACTWait(0xA0);
 Generator_MaskOff(a0);
 Generator_Call(a0);
 _ACTWait(0x1E);
 Generator_Call(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEnemy4);

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bEnemy5);

extern int D_00631AE8;
extern void func_0017B258(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);

void actSt01bEnemy6(volatile int a0) {
    if (D_00631AE8 == 0) {
        _ACTWait(0);
    }
    while (scpSleepSpiderGroupOne(D_00631AE8, 0x2000000) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0x27);
}

void actSt01bFloor(int x) {
    volatile int local = x;
}

extern long long D_0061B9B0[];
extern long long D_0061B9C0[];
extern void scpDispOffAllWithKind(int *buf, int a1);

void actSt01bWay(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061B9B0[0]; long long v0b=D_0061B9C0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061B9B0[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061B9C0[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

void actSt01bEnd(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061B9C0[0]; long long v0b=D_0061B9B0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061B9C0[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061B9B0[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

void actSt01bSekizoEvent(int x) {
    volatile int local = x;
}

extern long long D_0061B9E0[];
extern long long D_0061B9F0[];

void actSt01bFloorEvent(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061B9E0[0]; long long v0b=D_0061B9F0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061B9E0[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061B9F0[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

void actSt01bWayOnChk(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061B9F0[0]; long long v0b=D_0061B9E0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061B9F0[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061B9E0[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

INCLUDE_ASM("asm/nonmatchings/src/st01b", actSt01bWayOffChk);

INCLUDE_ASM("asm/nonmatchings/src/st01b", func_00210DF0);

INCLUDE_ASM("asm/nonmatchings/src/st01b", func_00210F20);

INCLUDE_ASM("asm/nonmatchings/src/st01b", func_002110F0);

