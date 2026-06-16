#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aEnd);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aSekizo1Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aHane1Up);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aHane2Up);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aRopeChk);

void actSt47aEnemy1(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0); Generator_Mask(actSt25aQueenDeadChk(0x2CA));
 while(func_00178DB0(0x3A)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); Generator_Call(actSt25aQueenDeadChk(0x2CA)); }

extern int actSt25aQueenDeadChk(int a0);
void actSt47aTorch(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0); Generator_Mask(actSt25aQueenDeadChk(0x2CB));
 while(func_00178DB0(0x3C)==0){ _ACTWait(1); }
 Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_Call(actSt25aQueenDeadChk(0x2CB)); }

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aSekizo1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aSekizo2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aSekizo3);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aSekizo4);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aHane1);

extern int actInitialize(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
void actSt47aHane2(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x3A)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); }

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aRope);

void actSt47aBarricade(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x3C)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

void actSt47aExit(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aExit2);

extern int D_00629DE8;
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void func_00178E08(int a0);
extern void func_00178DD8(int a0);
void actSt47aEne(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE8, 0x3000000) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_00178E08(0x165);
    func_00178DD8(0x39);
    func_00178DD8(0x3A);
}

void actSt47aEnemy2(volatile int a0){
 if(D_00629DE8 == 0) _ACTWait(0);
 while(D_00629DE8 == 0 || scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x2D3), 0x4000000)==0) _ACTWait(1);
 _ACTWait(0x258); func_00178DD8(0x3B); func_00178DD8(0x3C); }

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aEnemy3);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aEnemy4);
