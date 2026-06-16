#include "common.h"

extern void scpDispOffAllWithKind(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_00614980[]; extern long long D_00614990[];
void actSt10lInit(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00614980[0]; long long v0b=D_00614990[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00614980[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00614990[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

extern void scpDispOffAllWithKind(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_00614990[]; extern long long D_00614980[];
void actSt10lFloorLeft(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_00614990[0]; long long v0b=D_00614980[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_00614990[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_00614980[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

extern int D_00629DE8;
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);
void actSt10lFloorRight(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (D_00629DE8 == 0 || func_00178DB0(0x98) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_00178DD8(0x99);
    func_00178DD8(0x9A);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lGondolaUp);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lGondolaDown);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEneCam3Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lChainMove);

#include "common.h"
extern void lt_fade_status(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void actSt10lFloor();
extern void scpDispOnAllWithKind(void);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void scpActivateAllWithKind(void);
extern void AddWayPointTop(int a0, int a1);
extern int D_0062A894;
void actSt10lChain(volatile int a0) {
    lt_fade_status(0x33);
    actCreateSubThread(actSt10lFloor, 0x15);
    scpDispOnAllWithKind();
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0xEB, 1, 0);
    stage_KillPlayBgAnimation(0xEA, -1, -2);
    while (func_0012A958(0xEB) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x5A5) + 0x16C) = 1;
    *(int *)(actSt25aQueenDeadChk(0x5A4) + 0x16C) = 0;
    D_0062A894 = 0;
    lt_fade_status(0x32);
    scpActivateAllWithKind();
    AddWayPointTop(5, 1);
}

extern int func_0025F4F0(int a0);
extern int func_0025EF78(int a0, long a1);
extern int func_0025F5A8(int a0);
extern void _ACTWait(int a0);
extern void func_00178DD8(int a0);
extern int D_00271240[];
void actSt10lFloor(volatile int a0) {
    _ACTWait(func_0025F5A8(func_0025EF78(func_0025F4F0((0x3C - D_00271240[0] * 0xA) / D_00271240[1]), (long)0x804C << 47)));
    func_00178DD8(0xCE);
}

extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);

void actSt10lGondola(void) {
    if (func_00178DB0(0x5F) == 0) {
        AddWayPointTop(0x9, 0);
        AddWayPointTop(0xA, 0);
    } else {
        AddWayPointTop(0x9, 1);
        AddWayPointTop(0xA, 1);
    }
    if (func_00178DB0(0x60) == 0) {
        AddWayPointTop(0xC, 0);
    } else {
        AddWayPointTop(0xC, 1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lSekizo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lBox);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEnemy1_1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEnemy1_2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEnemy2_1);

#include "common.h"
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void scpDispOnAllWithKind(void);
extern void _ACTWait(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void scpActivateAllWithKind(void);
extern void AddWayPointTop(int a0, int a1);
extern int D_0062BD54;
extern int D_0062A894;
void actSt10lEnemy2_2(volatile int a0) {
    lt_fade_status(0x33);
    func_00178DD8(0x60);
    scpDispOnAllWithKind();
    _ACTWait(0x3C);
    scpPlayStart(0x51, (int)&D_0062BD54, 1, 1, 1);
    while (D_0062BD54 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x5C, 1, 0);
    while (func_0012A958(0x5C) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x64A) + 0x16C) = 0;
    *(int *)(actSt25aQueenDeadChk(0x64B) + 0x16C) = 1;
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
    AddWayPointTop(0xC, 1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEnemy2_3);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEnemy3_1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEnemy3_2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEneCam1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st10l", actSt10lEneCam2);
