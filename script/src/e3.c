#include "common.h"

void actE3WarningChk(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x14B)==0){ _ACTWait(1); }
 _ACTWait(0x190); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
void actE3Title(volatile int a0){
 int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x14B)==0){ _ACTWait(1); }
 Generator_Call(a0); _ACTWait(0x78); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0);
}

extern void actInitialize(int a0);
extern void _ACTWait(int a0);

void actE3TitleChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3TitleFrameChk);

void actE3Inst1Chk(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x149)==0){ _ACTWait(1); }
 _ACTWait(0x1E); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

void actE3Capsule(volatile int a0){
 int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x149)==0){ _ACTWait(1); }
 Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0);
}

void actE3CapsuleDemoCancel(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x149)==0){ _ACTWait(1); }
 Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3CapsuleDemo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3St13cInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3CageFall);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3CageFallChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3CageFallDemo);

extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void stage_KillPlayBgAnimation(int,int,int);
extern int func_0012A958(int a0);
extern int D_0062A894;
void actE3CageFallEffect(volatile int a0){
 lt_fade_status(0x33); func_00178DD8(0x14A); D_0062A894=1; _ACTWait(0x78);
 stage_KillPlayBgAnimation(0x320,1,0);
 while(func_0012A958(0x320)==0) _ACTWait(1); _ACTWait(1); lt_fade_status(0x32); D_0062A894=0; }

extern void actInitialize(int a0);
extern void _ACTWait(int a0);
extern int D_0062BBFC;
extern int D_00629DE4;
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
void actE3St09aSekizo(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    D_0062BBFC = 0;
    _ACTWait(1);
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x2000000) == 0) { _ACTWait(1); }
    scpPlayStart(3, &D_0062BBFC, 1, 1, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3St09aSekizoChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3GateChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3GateDemo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3GateJimaku);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3St01bInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3Warning);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3Inst1);
