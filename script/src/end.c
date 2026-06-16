#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actEndDemo01);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actConte14_1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actEndDemo02);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actConte14_2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actEndDemo06);

#include "common.h"
extern void func_001790A8(int a0);
extern void actConte11Jimaku(float f);
extern void func_0017A0F8(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void gflagOff(int a0, int a1);
extern int stage_DispBgAnimation(int a0, int a1);
extern void _ACTWait(int a0);
extern int func_0012A958(int a0);
extern void func_001790E8(int a0);
extern void actSt25aQueenDead(int a0, int a1, int a2, float f0, float f1);
extern int D_00629DE4;
extern int D_00629DE8;
void actConte14_6(volatile int a0) {
    func_001790A8(D_00629DE4);
    actConte11Jimaku(3.0f);
    func_0017A0F8(6);
    stage_KillPlayBgAnimation(0x30B, 1, 0);
    gflagOff(D_00629DE4, 0x1C2);
    while (stage_DispBgAnimation(0x30B, 0x30C) == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x32, 1, 0);
    stage_KillPlayBgAnimation(0x191, 1, 0);
    gflagOff(D_00629DE4, 0x1C2);
    while (func_0012A958(0x30C) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_001790E8(D_00629DE4);
    actSt25aQueenDead(6, D_00629DE4, D_00629DE8, 1.0f, 8.0f);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actEndDemo07);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actConte14_7);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actEndDemo10);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actConte14_10);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actConte14_13);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actStaff1Demo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actStaff2Demo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actStaff3Demo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actEndDemo14);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actConte14_14);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actSt27aEndChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actSt27aEndDemo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actEndDemo03);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actEndDemo04);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actEndDemo05);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actEndDemo11);
