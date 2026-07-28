#include "common.h"





extern void *D_00631AE8;
extern void func_0017B258(int bit_idx);
extern int func_0017B230(int a0);
extern void func_0018CED0();
extern int *D_00631AE4;
extern int D_00633FAC;
extern void actSt25aQueenBefore(int *self);
extern void gflagOff();
extern int func_0012AA80(int key);
extern void stage_KillPlayBgAnimation();
extern void gflagInit();
extern void func_001C3270();
extern void _ACTWait();
INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bFloor);

extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void _ACTWait__p4(int a0) __asm__("_ACTWait");
extern int actInitialize(int a0);

void actSt13bFloorChk(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait__p4(1); Generator_Mask(a0);
 while(func_0017B230(0x76)==0){ _ACTWait__p4(1); }
 _ACTWait__p4(1); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait__p4(0x3C); Generator_Call(a0); _ACTWait__p4(0x3C); Generator_Call(a0); _ACTWait__p4(0x3C); Generator_Call(a0); }

extern void _ACTWait__p4(int a0) __asm__("_ACTWait");

void actSt13bConte02(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait__p4(1); Generator_Mask(a0);
 while(func_0017B230(0x76)==0){ _ACTWait__p4(1); }
 _ACTWait__p4(1); Generator_Call(a0); _ACTWait__p4(0x3C); Generator_Call(a0); _ACTWait__p4(0x3C); Generator_Call(a0); _ACTWait__p4(0x3C); Generator_Call(a0); _ACTWait__p4(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

extern void _ACTWait__p4(int a0) __asm__("_ACTWait");

void actSt13bSekizoChk(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait__p4(1); Generator_Mask(a0);
 while(func_0017B230(0x76)==0){ _ACTWait__p4(1); }
 _ACTWait__p4(0x3C); Generator_Call(a0); _ACTWait__p4(0x3C); Generator_Call(a0); _ACTWait__p4(0x3C); Generator_Call(a0); _ACTWait__p4(0x3C); Generator_Call(a0); _ACTWait__p4(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bSekizo2Chk);

extern void _ACTWait__p4(int a0) __asm__("_ACTWait");

void actSt13bMeetAgain(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait__p4(1); Generator_Mask(a0);
 while(func_0017B230(0x79)==0){ _ACTWait__p4(1); }
 _ACTWait__p4(1); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait__p4(0x3C); Generator_Call(a0); _ACTWait__p4(0x3C); Generator_Call(a0); _ACTWait__p4(0x3C); Generator_Call(a0); }

extern void _ACTWait__p4(int a0) __asm__("_ACTWait");

void actSt13bBoss(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait__p4(1); Generator_Mask(a0);
 while(func_0017B230(0x79)==0){ _ACTWait__p4(1); }
 _ACTWait__p4(1); Generator_Call(a0); _ACTWait__p4(0x3C); Generator_Call(a0); _ACTWait__p4(0x3C); Generator_Call(a0); _ACTWait__p4(0x3C); Generator_Call(a0); _ACTWait__p4(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

extern void _ACTWait__p4(int a0) __asm__("_ACTWait");

void actConte10b(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait__p4(1);
    Generator_Mask(a0);
    while (func_0017B230(0x79) == 0) {
        _ACTWait__p4(1);
    }
    _ACTWait__p4(1);
    Generator_MaskOff(a0);
}

void actSt13bElevDown(int x) {
    volatile int local = x;
}

void actSt13bElevUp(volatile unsigned int self)
{
    volatile int local;
    stage_KillPlayBgAnimation(0x142, 1, 0);
    while (func_0012AA80(0x142) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    func_001C3270();
    _ACTWait(0x78);
    gflagInit(0x18A);
    gflagInit(0x18B);
    _ACTWait(0);
}

void actSt13bElevUpChk(volatile int unused)
{
    gflagOff(D_00631AE4, 0x1D0);
    actSt25aQueenBefore(D_00631AE4);
    gflagOff(D_00631AE4, 0x1D1);
    actSt25aQueenBefore(D_00631AE4);
    D_00633FAC = 1;
    _ACTWait(0);

}

INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bSekizo);

INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bSekizo2);

void actSt13bBossAfter(int x) {
    volatile int local = x;
}

void actSt13bStoneGirl(volatile int unused)
{
    stage_KillPlayBgAnimation(0x143, 1, 0);
    stage_KillPlayBgAnimation(0x144, 1, 0);
    func_0018CED0();
    while (func_0012AA80(0x144) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_00633FAC = 1;
    _ACTWait(0);

}

INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bExit);

void actSt13bElev(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bDoor);

void actBossTest(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bConte02Jimaku);

void actSt13bSekizo2Event(void)
{
    if (D_00631AE8 == 0) {
        return;
    }
    if (func_0017B230(0x45) != 0) {
        return;
    }
    return func_0017B258(0x166);
}

INCLUDE_ASM("asm/nonmatchings/src/st13b", actSt13bMeetAgainChk);

