#include "common.h"

typedef struct { char pad[0xC0]; int *unkB0; } ActB0Obj;

extern long long D_0061BE50[];
extern long long D_0061BE60[];
extern void _ACTWait(int a0);
extern void scpDispOffAllWithKind(int *buf, int a1);

void actSt10lInit(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_0061BE50[0]; long long v0b=D_0061BE60[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_0061BE50[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_0061BE60[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

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

extern int D_006325B4;
extern int D_00633A44;
extern int _SCPBoySupportGirl(int a0, int a1, int a2);
extern int actSt25aQueenDeadChk(int a0);
extern int func_0012AA80(int a0);
extern void func_0017B288(int a0);
extern void lt_fade_status(int a0);
extern void scpActivateAllWithKind(void);
extern void scpDispOnAllWithKind(void);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void scpTrans(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt10lGondolaUp(volatile int a0) {
    while (_SCPBoySupportGirl(0x5AC, 0x109, 0x113) == 0) { _ACTWait(1); }
    *(int *)(actSt25aQueenDeadChk(0x5AC) + 0x16C) = 0;
    *(int *)(actSt25aQueenDeadChk(0x5AD) + 0x16C) = 1;
    if (func_0017B230(0xDA) == 0 || func_0017B230(0xDB) == 0 ||
        func_0017B230(0xDC) == 0) {
        lt_fade_status(0x33);
        D_006325B4 = 1;
        scpDispOnAllWithKind();
        scpPlayStart(0x34, (int)&D_00633A44, 1, 1, 1);
        stage_KillPlayBgAnimation(0xED, 1, 0);
        while (func_0012AA80(0xED) == 0) { _ACTWait(1); }
        _ACTWait(1);
        if (D_00633A44 != 0) { scpTrans(D_00633A44, 0x50); }
        lt_fade_status(0x32);
        D_006325B4 = 0;
        scpActivateAllWithKind();
    }
    func_0017B258(0xCF);
    func_0017B288(0xDD);
    func_0017B288(0xDE);
    func_0017B288(0xE0);
    func_0017B258(0xD0);
}

INCLUDE_ASM("asm/nonmatchings/src/st10l", actSt10lGondolaDown);

INCLUDE_ASM("asm/nonmatchings/src/st10l", actSt10lEneCam3Chk);

extern int D_004D2510[];

void actSt10lChainMove(volatile int a0) {
    ActB0Obj *obj = *(ActB0Obj **)(a0 + 0x164);
    obj->unkB0 = D_004D2510;
    while (1) {
        _ACTWait(1);
    }
}

typedef struct St10lBox {
    char pad[0xC0];
    void *field_B0;
    void *field_B4;
} St10lBox;

extern int *D_004D2550[];
extern void actSt10lChain(volatile int a0);
extern int D_006325B4;

void func_00225DD0(volatile int a0) {
    St10lBox *obj = *(St10lBox **)(a0 + 0x164);
    D_006325B4 = 1;
    D_004D2550[1] = (int *)actSt10lChain;
    obj->field_B0 = 0;
    obj->field_B4 = (void *)D_004D2550;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern void AddWayPointTop(int a0, int a1);
extern int D_006325B4;
extern int actCreateSubThread(void *fn, int a1);
extern void actSt10lFloor();
extern int actSt25aQueenDeadChk(int a0);
extern int func_0012AA80(int a0);
extern void lt_fade_status(int a0);
extern void scpActivateAllWithKind(void);
extern void scpDispOnAllWithKind(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt10lChain(volatile int a0) {
    lt_fade_status(0x33);
    actCreateSubThread(actSt10lFloor, 0x15);
    scpDispOnAllWithKind();
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0xEC, 1, 0);
    stage_KillPlayBgAnimation(0xEB, -1, -2);
    while (func_0012AA80(0xEC) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x5AB) + 0x16C) = 1;
    *(int *)(actSt25aQueenDeadChk(0x5AA) + 0x16C) = 0;
    D_006325B4 = 0;
    lt_fade_status(0x32);
    scpActivateAllWithKind();
    AddWayPointTop(5, 1);
}

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

