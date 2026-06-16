#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", actSt04eWater);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", actSt04eWaterMain);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", actSt04eWaterSwitch);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", actSt04eWaterStop);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", actSt04eWaterFlagOn);

void func_00217198(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_002171A8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_00217288);

void func_00217368(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void scpDispOffAllWithKind(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_006148D0[]; extern long long D_006148E0[];
void func_00217378(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_006148D0[0]; long long v0b=D_006148E0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_006148D0[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_006148E0[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

extern void scpDispOffAllWithKind(int *buf, int a1);
extern void _ACTWait(int a0);
extern long long D_006148E0[]; extern long long D_006148D0[];
void func_00217458(volatile int a0){ long long b1[2]; long long b2[2];
 long long v0a=D_006148E0[0]; long long v0b=D_006148D0[0]; int i;
 for(i=0;i<0x32;i++){ switch(i){
  case 0: b1[0]=v0a; b1[1]=D_006148E0[1]; scpDispOffAllWithKind((int*)b1,0); break;
  case 0x1E: b2[0]=v0b; b2[1]=D_006148D0[1]; scpDispOffAllWithKind((int*)b2,0); break;
  } _ACTWait(1); } }

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_00217538);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_002175E0);

#include "common.h"
extern void lt_fade_status(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void func_00217730();
extern void scpDispOnAllWithKind(void);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void scpActivateAllWithKind(void);
extern void AddWayPointTop(int a0, int a1);
extern int D_0062A894;
void func_00217668(volatile int a0) {
    lt_fade_status(0x33);
    actCreateSubThread(func_00217730, 0x15);
    scpDispOnAllWithKind();
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0xE9, 1, 0);
    stage_KillPlayBgAnimation(0xE8, -1, -2);
    while (func_0012A958(0xE9) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x495) + 0x16C) = 1;
    *(int *)(actSt25aQueenDeadChk(0x494) + 0x16C) = 0;
    D_0062A894 = 0;
    lt_fade_status(0x32);
    scpActivateAllWithKind();
    AddWayPointTop(5, 1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_00217730);

extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void AddWayPointTop(int a0, int a1);

void func_002177A8(void) {
    if (func_00178DB0(0xC0) == 0) stage_KillPlayBgAnimation(0xCD, 0, 0); else stage_KillPlayBgAnimation(0xCD, 0, -1);
    if (func_00178DB0(0xC1) == 0) stage_KillPlayBgAnimation(0xCE, 0, 0); else stage_KillPlayBgAnimation(0xCE, 0, -1);
    if (func_00178DB0(0xC2) == 0) stage_KillPlayBgAnimation(0xCF, 0, 0); else stage_KillPlayBgAnimation(0xCF, 0, -1);
    if (func_00178DB0(0xC3) == 0) stage_KillPlayBgAnimation(0xD0, 0, 0); else stage_KillPlayBgAnimation(0xD0, 0, -1);
    if (func_00178DB0(0xC4) == 0) stage_KillPlayBgAnimation(0xD1, 0, 0); else stage_KillPlayBgAnimation(0xD1, 0, -1);
    if (func_00178DB0(0xC5) == 0) stage_KillPlayBgAnimation(0xD2, 0, 0); else stage_KillPlayBgAnimation(0xD2, 0, -1);
    if (func_00178DB0(0xC6) == 0) stage_KillPlayBgAnimation(0xD3, 0, 0); else stage_KillPlayBgAnimation(0xD3, 0, -1);
    if (func_00178DB0(0xA9) == 0) AddWayPointTop(1, 0); else AddWayPointTop(1, 1);
    if (func_00178DB0(0xA3) == 0) stage_KillPlayBgAnimation(0xC3, 0, 0); else stage_KillPlayBgAnimation(0xC3, 0, -1);
    if (func_00178DB0(0xA4) == 0) stage_KillPlayBgAnimation(0xC4, 0, 0); else stage_KillPlayBgAnimation(0xC4, 0, -1);
}

extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void AddWayPointTop(int a0, int a1);

void func_00217990(void) {
    if (func_00178DB0(0xA1) == 0) {
        stage_KillPlayBgAnimation(0xC6, 0, 0);
        stage_KillPlayBgAnimation(0xE5, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xC6, 0, -1);
        stage_KillPlayBgAnimation(0xE5, 0, -1);
    }
    if (func_00178DB0(0xA3) == 0) {
        stage_KillPlayBgAnimation(0xC3, 0, 0);
        AddWayPointTop(3, 0);
    } else {
        stage_KillPlayBgAnimation(0xC3, 0, -1);
        AddWayPointTop(3, 1);
    }
    if (func_00178DB0(0xA4) == 0) {
        stage_KillPlayBgAnimation(0xC4, 0, 0);
        AddWayPointTop(4, 0);
    } else {
        stage_KillPlayBgAnimation(0xC4, 0, -1);
        AddWayPointTop(4, 1);
    }
    if (func_00178DB0(0xC0) == 0) stage_KillPlayBgAnimation(0xCD, 0, 0); else stage_KillPlayBgAnimation(0xCD, 0, -1);
    if (func_00178DB0(0xC1) == 0) stage_KillPlayBgAnimation(0xCE, 0, 0); else stage_KillPlayBgAnimation(0xCE, 0, -1);
    if (func_00178DB0(0xC2) == 0) stage_KillPlayBgAnimation(0xCF, 0, 0); else stage_KillPlayBgAnimation(0xCF, 0, -1);
    if (func_00178DB0(0xC3) == 0) stage_KillPlayBgAnimation(0xD0, 0, 0); else stage_KillPlayBgAnimation(0xD0, 0, -1);
    if (func_00178DB0(0xC4) == 0) stage_KillPlayBgAnimation(0xD1, 0, 0); else stage_KillPlayBgAnimation(0xD1, 0, -1);
    if (func_00178DB0(0xC5) == 0) stage_KillPlayBgAnimation(0xD2, 0, 0); else stage_KillPlayBgAnimation(0xD2, 0, -1);
    if (func_00178DB0(0xC6) == 0) stage_KillPlayBgAnimation(0xD3, 0, 0); else stage_KillPlayBgAnimation(0xD3, 0, -1);
    if (func_00178DB0(0x91) != 0 && func_00178DB0(0x9B) == 0) {
        stage_KillPlayBgAnimation(0xE0, 0, -1);
    }
    if (func_00178DB0(0x91) == 0 || func_00178DB0(0x9B) != 0) {
        stage_KillPlayBgAnimation(0xE0, 0, 0);
    }
    if (func_00178DB0(0xAB) != 0) {
        stage_KillPlayBgAnimation(0xC7, 0, 0xC8);
    } else {
        stage_KillPlayBgAnimation(0xC7, 0, 0);
    }
}

extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_00217C58(void) {
    if (func_00178DB0(0xCD) == 0) {
        AddWayPointTop(5, 0);
    } else {
        AddWayPointTop(5, 1);
    }
    if (func_00178DB0(0xA3) == 0) {
        stage_KillPlayBgAnimation(0xC3, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xC3, 0, -1);
    }
    if (func_00178DB0(0xA4) == 0) {
        stage_KillPlayBgAnimation(0xC4, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xC4, 0, -1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_00217CF0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_00217E18);

#include "common.h"
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void func_00178DD8(int a0);
extern void _ACTWait(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void scpActivateAllWithKind(void);
extern int D_0062BCD0;
extern int D_0062A894;
void func_00217F40(volatile int a0) {
    lt_fade_status(0x33);
    scpDispOnAllWithKind();
    func_00178DD8(0xA0);
    _ACTWait(0x3C);
    scpPlayStart(0x50, (int)&D_0062BCD0, 1, 1, 1);
    while (D_0062BCD0 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0xBA, 1, 0);
    while (func_0012A958(0xBA) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x453) + 0x16C) = 1;
    *(int *)(actSt25aQueenDeadChk(0x454) + 0x16C) = 1;
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}
