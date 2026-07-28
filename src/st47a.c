#include "common.h"



extern void *D_00631AE8;
extern void func_0017B258(int bit_idx);
extern int func_0017B230(int a0);
extern void AddWayPointTop();
extern void stage_KillPlayBgAnimation();
INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aInit);

INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aEnd);

INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aSekizo1Chk);

INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHane1Up);

INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHane2Up);

INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aRopeChk);

INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aEnemy1);

INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aTorch);

INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aSekizo1);

INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aSekizo2);

INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aSekizo3);

INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aSekizo4);

INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHane1);

INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHane2);

INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aRope);

INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aBarricade);

void actSt47aExit(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00236C70);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00236D20);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00236D90);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00236E10);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00236F38);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237088);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237230);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237338);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237428);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237518);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002375C8);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237638);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002376F0);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237750);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002377E8);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237860);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237930);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237A00);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237AD8);

void func_00237B78(void)
{
    if (func_0017B230(0x120) == 0) {
        stage_KillPlayBgAnimation(0x80, 0, 0);
        AddWayPointTop(4, 0);
    } else {
        stage_KillPlayBgAnimation(0x80, 0, -1);
        AddWayPointTop(4, 1);
    }
}

void func_00237BD0(void)
{
    if (D_00631AE8 != 0) {
        if (func_0017B230(0x120) != 0) {
            if (func_0017B230(0x123) == 0) {
                func_0017B258(0x166);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237C18);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237D18);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237E98);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238000);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002381C0);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238320);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238480);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002385E0);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238740);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002387B8);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238868);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002388D0);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238950);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002389C8);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238A70);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238B18);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238B88);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238C18);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238D08);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238DD8);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238E50);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00239138);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002393C0);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002394D8);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00239680);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00239710);

void func_00239750(void)
{
    if (func_0017B230(0x2C) != 0) {
        stage_KillPlayBgAnimation(0x91, 0, 0);
        AddWayPointTop(0x21, 1);
    } else {
        stage_KillPlayBgAnimation(0x90, 0, 0);
        AddWayPointTop(0x21, 0);
    }
    if (func_0017B230(0x2D) != 0) {
        stage_KillPlayBgAnimation(0x93, 0, 0);
        AddWayPointTop(0x22, 1);
    } else {
        stage_KillPlayBgAnimation(0x92, 0, 0);
        AddWayPointTop(0x22, 0);
    }
}

void func_002397F8(void)
{
    if (D_00631AE8 == 0) {
        return;
    }
    if (func_0017B230(0x31) != 0) {
        return;
    }
    return func_0017B258(0x166);
}

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00239830);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00239B50);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00239C58);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00239DA8);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00239EB0);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00239FE0);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A180);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A248);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A2F8);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A3B8);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A418);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A478);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A4D8);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A548);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A5B0);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A668);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A700);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A768);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A7E0);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A858);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A8E8);

