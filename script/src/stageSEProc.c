#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSEtaimatsu);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE04eriver);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE06ariver);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE10lstrong2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE19ataki);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE02astrong);

extern void func_00178E08(int a0);
extern int actSt25aQueenDeadChk(int a0);
void stageSE02ataki(volatile int a0){ int x=a0; actInitialize(a0); _ACTWait(1);
if(func_00178DB0(0x119)){ *(int*)(actSt25aQueenDeadChk(0x72E) + 0x16C) = 0; *(int*)(actSt25aQueenDeadChk(0x72F) + 0x16C) = 0; func_00178E08(0x119); } else { *(int*)(actSt25aQueenDeadChk(0x730) + 0x16C) = 0; *(int*)(actSt25aQueenDeadChk(0x731) + 0x16C) = 0; } }

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE02atakib);

extern void Generator_Call(int a0);
void stageSE03tsuiro(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x123)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

void stageSE03tnotSuiro(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x123)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

extern void actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
void stageSE04agate(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x123) == 0) { _ACTWait(1); }
    _ACTWait(1); Generator_MaskOff(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE04bstrong);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE04ewind);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE04eriverDown);

extern int D_00629DE8;
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void func_00178DD8(int a0);
void stageSE06astrong(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (func_00178DB0(0x11F) == 0 || scpSleepSpiderGroupOne(D_00629DE8, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    func_00178DD8(0x122);
    func_00178DD8(0x123);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE06abirdIn);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE06abirdOut);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE06ataimatsu);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE08astrong);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/stageSEProc", stageSE08astrong2);

extern void actInitialize(int a0);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void stageSE08anoise3(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x82, 0, 0);
}

extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);

void stageSE08ataimatsu(void) {
    if (func_00178DB0(0x2C) != 0) {
        stage_KillPlayBgAnimation(0x90, 0, 0);
        AddWayPointTop(0x21, 1);
    } else {
        stage_KillPlayBgAnimation(0x8F, 0, 0);
        AddWayPointTop(0x21, 0);
    }
    if (func_00178DB0(0x2D) != 0) {
        stage_KillPlayBgAnimation(0x92, 0, 0);
        AddWayPointTop(0x22, 1);
    } else {
        stage_KillPlayBgAnimation(0x91, 0, 0);
        AddWayPointTop(0x22, 0);
    }
}
