#include "common.h"

#include "common.h"
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void lt_fade_status(int a0);
extern void func_0017A040(int a0);
extern void func_00178E08(int a0);
extern void func_00178DD8(int a0);
extern void actConte11(int a0);
extern void func_0017A0D8(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void func_0017A008(int a0);
extern int D_00629DE8;
extern int D_0062A894;
void actSt13b2Generator(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE8, 0x5000000) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_0017A040(0xD57);
    func_00178E08(0x165);
    func_00178DD8(0x45);
    func_00178DD8(0x47);
    _ACTWait(0x3C);
    actConte11(0x12F);
    actConte11(0x130);
    actConte11(0x131);
    func_0017A0D8(0x132);
    stage_KillPlayBgAnimation(0x59, 1, 0);
    while (func_0012A958(0x59) == 0) { _ACTWait(1); }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_0062A894 = 0;
    func_0017A008(0xD57);
}

#include "common.h"
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void scpDispOnAllWithKind(void);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern int func_0012A958(int a0);
extern void AddWayPointTop(int a0, int a1);
extern void scpActivateAllWithKind(void);
extern int D_004CD6E0[];
extern int D_0062A894;
void func_00226C80(volatile int a0) {
    lt_fade_status(0x33);
    func_00178DD8(0x43);
    scpDispOnAllWithKind();
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0x5A, 1, 0);
    soundSeDefPlayWithVolumeRate(0x4AD, 0, (int)D_004CD6E0, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, (int)D_004CD6E0, 1);
    while (func_0012A958(0x5A) == 0) { _ACTWait(1); }
    _ACTWait(1);
    AddWayPointTop(0xB, 1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00226D50);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00226DF8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00226E70);

void func_00226EE8(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x46)==0){ _ACTWait(1); }
 _ACTWait(0x74); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

void func_00226F90(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x46)==0){ _ACTWait(1); }
 _ACTWait(0x64); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
void func_00227038(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x47)==0){ _ACTWait(1); }
 Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

void func_002270D8(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x47)==0){ _ACTWait(1); }
 Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00227178);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_002271F0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00227268);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_002272F8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_002273A0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00227748);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00227860);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00227960);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00227A68);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00227BE0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00227D58);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00227DC0);
