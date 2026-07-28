#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aInit);

INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aElvDown);

INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aSekizo);

INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aBrgDown);

INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aElv);

INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aIntro);

INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aBrg);

INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aElvMain);

INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aElvSwitch);

INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aElvUp);

extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int func_0017B230(int a0);

void actSt09aSekizoEvent(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0x97)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

void actSt09aIntroChk(volatile int a0){
 int x=a0;
 actInitialize(a0);
 _ACTWait(1);
 Generator_Mask(a0);
 while(func_0017B230(0x97)==0){ _ACTWait(1); }
 _ACTWait(1);
 Generator_MaskOff(a0);
 Generator_Call(a0);
 _ACTWait(0x3C);
 Generator_Call(a0);
}

void actSt09aBrgMain(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aBrgSwitch);

INCLUDE_ASM("asm/nonmatchings/src/st09a", func_00225308);

INCLUDE_ASM("asm/nonmatchings/src/st09a", func_00225378);

INCLUDE_ASM("asm/nonmatchings/src/st09a", func_00225480);

INCLUDE_ASM("asm/nonmatchings/src/st09a", func_002255E0);

INCLUDE_ASM("asm/nonmatchings/src/st09a", func_00225740);

INCLUDE_ASM("asm/nonmatchings/src/st09a", func_002257B8);

INCLUDE_ASM("asm/nonmatchings/src/st09a", func_00225850);

void func_002258E0(int x) {
    volatile int local = x;
}

