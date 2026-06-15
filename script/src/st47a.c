#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aEnd);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aSekizo1Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aHane1Up);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aHane2Up);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aRopeChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aEnemy1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aTorch);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aSekizo1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aSekizo2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aSekizo3);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aSekizo4);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aHane1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aHane2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aRope);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aBarricade);

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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aEnemy2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aEnemy3);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st47a", actSt47aEnemy4);
