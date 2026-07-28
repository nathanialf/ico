#include "common.h"



extern int D_00633A00;
extern int func_0017B230(int a0);
extern int soundSeVolSet();
extern int actSt25aQueenDeadChk();
INCLUDE_ASM("asm/nonmatchings/src/st05d", actSt05dDoor2);

INCLUDE_ASM("asm/nonmatchings/src/st05d", actSt05dDoor2UpChk);

void actSt05dDoor2DownChk(int x) {
    volatile int local = x;
}

void actSt05dEne(int x) {
    volatile int local = x;
}

void actSt05dEnemy1(int x) {
    volatile int local = x;
}

void actSt05dEnemy2(int x) {
    volatile int local = x;
}

void actSt05dDoor2Event(int x) {
    volatile int local = x;
}

void actSt05dDoor2UpEffect(int x) {
    volatile int local = x;
}

void actSt05dDoor2DownEffect(int x) {
    volatile int local = x;
}

void actSt05dEneChk(int x) {
    volatile int local = x;
}

void func_0021F578(int x) {
    volatile int local = x;
}

void func_0021F588(int x) {
    volatile int local = x;
    char *p = actSt25aQueenDeadChk(0x40A);
    *(int *)(p + 0x16C) = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/st05d", func_0021F5B0);

INCLUDE_ASM("asm/nonmatchings/src/st05d", func_0021F5F8);

INCLUDE_ASM("asm/nonmatchings/src/st05d", func_0021F640);

INCLUDE_ASM("asm/nonmatchings/src/st05d", func_0021F688);

INCLUDE_ASM("asm/nonmatchings/src/st05d", func_0021F6D0);

INCLUDE_ASM("asm/nonmatchings/src/st05d", func_0021F718);

INCLUDE_ASM("asm/nonmatchings/src/st05d", func_0021F760);

INCLUDE_ASM("asm/nonmatchings/src/st05d", func_0021F7A8);

void func_0021F7F0(void)
{
    if (D_00633A00 == 0) {
        return;
    }
    if (func_0017B230(0xD1) != 0) {
        return;
    }
    return soundSeVolSet(D_00633A00);
}

INCLUDE_ASM("asm/nonmatchings/src/st05d", func_0021F828);

